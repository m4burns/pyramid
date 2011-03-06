#ifndef _MIDI_WRITER_H_
#define _MIDI_WRITER_H_

#include <vector>
#include <map>
#include <string>

class RtMidiOut;

class MIDIWriter {
public:
	MIDIWriter(unsigned int port);
	~MIDIWriter();
	void sendMessage(std::vector<unsigned char> message);

	static std::map<std::string, int> enumerateOutputPorts();

private:
	RtMidiOut* out;
};

#endif

