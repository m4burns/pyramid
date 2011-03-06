#include "MIDIWriter.h"
#include "RtMidi.h"

MIDIWriter::MIDIWriter(unsigned int port)
{
	out = new RtMidiOut();
	out->openPort(port);
}

MIDIWriter::~MIDIWriter()
{
	delete out;
}

void MIDIWriter::sendMessage(std::vector<unsigned char> message)
{
	out->sendMessage(&message);
}

std::map<std::string, int> MIDIWriter::enumerateOutputPorts()
{
	std::map<std::string, int> res;

	RtMidiOut* _out = new RtMidiOut();
	unsigned int nPorts = _out->getPortCount();
	for(unsigned int i=0;i<nPorts;++i)
		res[_out->getPortName(i)] = i;
	delete _out;

	return res;
}

