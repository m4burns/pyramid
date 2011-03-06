#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <windows.h>
#include "MIDIListener.h"
#include "MIDIWriter.h"
#include "PythonMapper.h"

// Singleton.
class MapperCtl {
public:
	MapperCtl()
	{
		deadMutex = CreateMutex(NULL, FALSE, NULL);
		dead = false;

		inPorts = MIDIListener::enumerateInputPorts();
		outPorts = MIDIWriter::enumerateOutputPorts();

		printf("Inputs: \n");
		std::multimap<std::string, int>::iterator p = inPorts.begin();
		while(p != inPorts.end())
		{
			printf("\t%s => %d\n", p->first.c_str(), p->second);
			++p;
		}

		printf("\n");

		printf("Outputs: \n");
		p = outPorts.begin();
		while(p != outPorts.end())
		{
			printf("\t%s => %d\n", p->first.c_str(), p->second);
			++p;
		}

		printf("\n");
	}

	~MapperCtl()
	{
		printf("\nShutdown received, cleaning up...\n\n");
		for(std::map<int, MIDIListener*>::iterator p = ins.begin(); p != ins.end(); ++p)
			delete p->second;
		for(std::map<int, MIDIWriter*>::iterator p = outs.begin(); p != outs.end(); ++p)
			delete p->second;

		CloseHandle(deadMutex);
		CloseHandle(event);

		_this = NULL;
	}

	static MapperCtl* get()
	{
		if(!_this)
			_this = new MapperCtl();

		return _this;
	}

	bool registerMapper(PythonMapper* mapper, std::string ps)
	{
		std::istringstream is(ps);
		std::string buf;
		char c = 0;
		int pnum = 0;
		int mode = 0;
		int ord = mappers.size()+1;
		bool bound = false;
		while(!is.eof())
		{
			is >> buf;
			pnum = atoi(buf.c_str());

			is >> buf;
			if(buf == "=>")
				mode = 1;
			else if(buf == "<=")
				mode = 0;
			else {
				printf("Warning: Mapper %d: Invalid mode: %s\n", ord, buf.c_str());
				is >> buf;
				break;
			}

			buf = "";
			while(c != '\'')
				is.get(c);

			while((c != ',') && !is.eof())
			{
				is.get(c);
				if(c != ',')
					buf += c;
			}

			buf = buf.substr(0, buf.find("'",0));

			if(mode == 0) {
				std::map<std::string, int>::iterator port = inPorts.find(buf);
				if(port == inPorts.end()) {
					printf("Warning: Mapper %d: Invalid input port: '%s'\n", ord, buf.c_str());
					continue;
				}
				ins[port->second] = NULL;
				mapper->inmap[port->second] = pnum;
				mappers.insert(std::pair<int, PythonMapper*>(port->second, mapper));
				bound = true;
			} else {
				std::map<std::string, int>::iterator port = outPorts.find(buf);
				if(port == outPorts.end()) {
					printf("Warning: Mapper %d: Invalid output port: '%s'\n", ord, buf.c_str());
					continue;
				}
				outs[port->second] = NULL;
				mapper->outmap[pnum] = port->second;
				printf("outmap[%d] = %d\n", pnum, port->second);
			}
		}
		if(!bound)
			printf("Warning: Mapper %d not bound to any inputs.\n", ord);
	}

	void run()
	{
		printf("Opening MIDI inputs and outputs... ");
		event = CreateEvent(0, FALSE, FALSE, 0);
		for(std::map<int, MIDIListener*>::iterator p = ins.begin(); p != ins.end(); ++p)
			p->second = new MIDIListener(p->first, event);
		for(std::map<int, MIDIWriter*>::iterator p = outs.begin(); p != outs.end(); ++p)
			p->second = new MIDIWriter(p->first);

		printf("OK, entering main loop.");
		while(!die())
		{
			WaitForSingleObject(event, INFINITE);
			for(std::map<int, MIDIListener*>::iterator p = ins.begin(); p != ins.end(); ++p)
			{
				if(!p->second->hasData())
					continue;

				std::vector<unsigned char> data = p->second->getData();
				std::pair<std::multimap<int, PythonMapper*>::iterator,
					  std::multimap<int, PythonMapper*>::iterator >
					r = mappers.equal_range(p->first);

				for(std::multimap<int, PythonMapper*>::iterator q = r.first; q != r.second; ++q)
					dataToMapper(q->first, data, q->second);
			}
		}
	}

	void dataToMapper(int aport, std::vector<unsigned char> data, PythonMapper* mapper)
	{
		// Actual port to assigned (local) port.
		int lport = mapper->inmap[aport];

		// Translate and send messages to mapper.
		for(std::vector<unsigned char>::iterator p = data.begin(); p != data.end(); ++p)
		{
			if(!(*p & 0x80))
				continue;
			switch(*p >> 4)
			{
				case 0x8:
				case 0x9:
				case 0xA:
					MIDINote m;
					m.channel = (*p & 0xF);
					m.note = *(p+1);
					m.velocity = *(p+2);
					// Recognize the fake note on.
					if(((*p >> 4) == 0x9) && (*(p+2) == 0x0))
						m.state = 0;
					else
						m.state = ((*p >> 4) - 0x8);
					mapper->mapNote(lport, m);
					break;
				case 0xB:
					MIDIControlVal cv;
					cv.channel = (*p & 0xF);
					cv.control = *(p+1);
					cv.value = *(p+2);
					mapper->mapControl(lport, cv);
					break;
				default:
					printf("Unimplemented: %X.\n", *p);
			}
		}
	}

	void noteToOutput(int aport, MIDINote m)
	{
		std::vector<unsigned char> msg;
		msg.push_back( ((0x8 + m.state) << 4) | (m.channel & 0xF) );
		msg.push_back(m.note);
		msg.push_back(m.velocity);
		outs[aport]->sendMessage(msg);
	}

	void controlToOutput(int aport, MIDIControlVal cv)
	{
		std::vector<unsigned char> msg;
		msg.push_back( (0xB<<4) | (cv.channel & 0xF) );
		msg.push_back(cv.control);
		msg.push_back(cv.value);
		outs[aport]->sendMessage(msg);
	}

	bool die()
	{
		bool r;
		WaitForSingleObject(deadMutex, INFINITE);
		r = dead;
		ReleaseMutex(deadMutex);
		return r;
	}

	void kill()
	{
		WaitForSingleObject(deadMutex, INFINITE);
		dead = true;
		ReleaseMutex(deadMutex);
		SetEvent(event);
	}

private:
	static MapperCtl* _this;
	std::map<std::string, int> inPorts;
	std::map<std::string, int> outPorts;
	std::map<int, MIDIListener*> ins;
	std::map<int, MIDIWriter*> outs;
	std::multimap<int, PythonMapper*> mappers;
	HANDLE event;
	HANDLE deadMutex;
	bool dead;
};

MapperCtl* MapperCtl::_this = NULL;

PythonMapper::PythonMapper() { }

PythonMapper::~PythonMapper() { }

bool PythonMapper::selectPorts(std::string portsConfig)
{
	MapperCtl::get()->registerMapper(this, portsConfig);
	return true;
}

void PythonMapper::sendNote(int port, MIDINote note)
{
	if(outmap.find(port) != outmap.end())
		MapperCtl::get()->noteToOutput(outmap[port], note);
}

void PythonMapper::sendControl(int port, MIDIControlVal cv)
{
	if(outmap.find(port) != outmap.end())
		MapperCtl::get()->controlToOutput(outmap[port], cv);
}

int mapper_main()
{
	MapperCtl* mc = MapperCtl::get();

	mc->run();
	delete mc;

	return 0;
}

void kill_mapper()
{
	MapperCtl::get()->kill();
}

