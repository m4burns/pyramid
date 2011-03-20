#include <cstdio>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <windows.h>
#include <process.h>
#include "MIDIListener.h"
#include "MIDIWriter.h"
#include "PythonMapper.h"
#include "MapperInterface.h"

// Singleton.
class MapperCtl {
public:
	MapperCtl()
	{
		accessMutex = CreateMutex(NULL, FALSE, NULL);
		dead = false;

		inPorts = MIDIListener::enumerateInputPorts();
		outPorts = MIDIWriter::enumerateOutputPorts();

		printf("Inputs: \n");
		std::multimap<std::string, int>::iterator p = inPorts.begin();
		while(p != inPorts.end())
		{
			printf("\t%d:\t%s\n", p->second, p->first.c_str());
			++p;
		}

		printf("\n");

		printf("Outputs: \n");
		p = outPorts.begin();
		while(p != outPorts.end())
		{
			printf("\t%d:\t%s\n", p->second, p->first.c_str());
			++p;
		}

		printf("\n");

		in_states = new volatile bool[64];
		out_states = new volatile bool[64];
	}

	~MapperCtl()
	{
		printf("\nShutdown received, cleaning up...\n\n");
		for(std::map<int, MIDIListener*>::iterator p = ins.begin(); p != ins.end(); ++p)
			delete p->second;
		for(std::map<int, MIDIWriter*>::iterator p = outs.begin(); p != outs.end(); ++p)
			delete p->second;

		delete[] in_states;
		delete[] out_states;

		CloseHandle(accessMutex);
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
				named_ins[port->second] = buf;
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
				named_outs[port->second] = buf;
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

		printf("OK, entering main loop.\n");
		for(;;)
		{
			WaitForSingleObject(event, INFINITE);
			WaitForSingleObject(accessMutex, INFINITE);

			if(dead)
				break;

			for(std::map<int, MIDIListener*>::iterator p = ins.begin(); p != ins.end(); ++p)
			{
				if(!p->second->hasData())
					continue;

				in_states[p->first] = true;

				std::vector<unsigned char> data = p->second->getData();
				std::pair<std::multimap<int, PythonMapper*>::iterator,
					  std::multimap<int, PythonMapper*>::iterator >
					r = mappers.equal_range(p->first);

				for(std::multimap<int, PythonMapper*>::iterator q = r.first; q != r.second; ++q)
				{
					try {
						dataToMapper(q->first, data, q->second);
					} catch(...) {
						printf("Caught an exception while calling dataToMapper(...). Check your mapper class.");
					}
				}
			}
			ReleaseMutex(accessMutex);
		}
	}

	void dataToMapper(int aport, std::vector<unsigned char> data, PythonMapper* mapper)
	{
		// Actual port to assigned (local) port.
		int lport = mapper->inmap[aport];
		MIDINote m;
		MIDIControlVal cv;
		MIDIWheelVal wv;

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
					cv.channel = (*p & 0xF);
					cv.control = *(p+1);
					cv.value = *(p+2);
					mapper->mapControl(lport, cv);
					break;
				case 0xD:
					cv.channel = (*p & 0xF);
					cv.control = 0;
					cv.value = *(p+1);
					mapper->mapPressure(lport, cv);
					break;
				case 0xE:
					wv.channel = (*p & 0xF);
					wv.value = *(p+1) | (*(p+2) << 7);
					mapper->mapPitchBend(lport, wv);
					break;
				default:
					printf("Unimplemented: %X. Message discarded.\n");
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
		out_states[aport] = true;
	}

	void controlToOutput(int aport, MIDIControlVal cv)
	{
		std::vector<unsigned char> msg;
		msg.push_back( (0xB<<4) | (cv.channel & 0xF) );
		msg.push_back(cv.control);
		msg.push_back(cv.value);
		outs[aport]->sendMessage(msg);
		out_states[aport] = true;
	}

	void kill()
	{
		WaitForSingleObject(accessMutex, INFINITE);
		dead = true;
		ReleaseMutex(accessMutex);
		SetEvent(event);
	}

private:
	static MapperCtl* _this;
	std::map<std::string, int> inPorts;
	std::map<std::string, int> outPorts;
	std::map<int, MIDIListener*> ins;
	std::map<int, MIDIWriter*> outs;
	std::map<int, std::string> named_ins;
	std::map<int, std::string> named_outs;
	volatile bool* in_states;
	volatile bool* out_states;
	std::multimap<int, PythonMapper*> mappers;
	HANDLE event;
	HANDLE accessMutex;
	bool dead;
	friend class MapperInterface;
};

MapperCtl* MapperCtl::_this = NULL;

MapperInterface::MapperInterface()
{
	ctl = MapperCtl::get();
}

std::vector<std::pair<std::string, bool> > MapperInterface::getInputs()
{
	std::vector<std::pair<std::string, bool> > res;

	for(std::map<int, std::string>::iterator p = ctl->named_ins.begin(); p != ctl->named_ins.end(); ++p)
	{
		res.push_back(std::pair<std::string, bool>(p->second, (bool)ctl->in_states[p->first]));
		ctl->in_states[p->first] = false;
	}

	return res;
}

std::vector<std::pair<std::string, bool> > MapperInterface::getOutputs()
{
	std::vector<std::pair<std::string, bool> > res;

	for(std::map<int, std::string>::iterator p = ctl->named_outs.begin(); p != ctl->named_outs.end(); ++p)
	{
		res.push_back(std::pair<std::string, bool>(p->second, (bool)ctl->out_states[p->first]));
		ctl->out_states[p->first] = false;
	}

	return res;
}

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

static HANDLE mapper_thread_handle;

static void mapper_thread(void* userdata)
{
        MapperCtl* mc = MapperCtl::get();

        mc->run();
        delete mc;

	_endthread();
}

void start_mapper()
{
	SetPriorityClass(GetCurrentProcess(), HIGH_PRIORITY_CLASS);
	mapper_thread_handle = (HANDLE)_beginthread(&mapper_thread, 0, NULL);
	SetThreadPriority(mapper_thread_handle, THREAD_PRIORITY_ABOVE_NORMAL);
}

void kill_mapper()
{
	MapperCtl::get()->kill();
	WaitForSingleObject(mapper_thread_handle, INFINITE);
}

