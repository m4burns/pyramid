#ifndef _MIDI_LISTENER_H_
#define _MIDI_LISTENER_H_

#include <windows.h>
#include <vector>
#include <string>
#include <map>

class RtMidiIn;
struct callbackContext;

class MIDIListener {
public:
	MIDIListener(unsigned int port, HANDLE notifyEvent);
	~MIDIListener();
	bool hasData();
	std::vector<unsigned char> getData();

	static std::map<std::string, int> enumerateInputPorts();

private:
	callbackContext* con;
	std::vector<unsigned char>* midi_data;
	RtMidiIn* in;
};

#endif

