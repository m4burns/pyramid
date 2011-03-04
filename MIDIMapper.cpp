#ifndef _MIDIMAPPER_H_
#define _MIDIMAPPER_H_

#include "RtMidi.h"
#include <string>

struct MIDINote {
	unsigned char channel;
	unsigned char note;
	unsigned char velocity;
};

class MIDIMapper {
public:
	MIDIMapper();
	virtual ~MIDIMapper();
	virtual bool openPorts(std::string inputPort, std::string outputPort);
	virtual bool openPorts(int inputPort, int outputPort);

	virtual void mapNote(MIDINote note) = 0;
	virtual void mapPitchBend(...);

	virtual void run();

private:
	// rtmidi handles.
};
