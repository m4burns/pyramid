/*midi callback:
	there are bytes?
		unlock the mutex

main:
	initialize python
	load bindings
	provide functions to open rtmidi ins / outs (keep track of them in a vector)

	lock the mutex

	while not killed
		for all midi messages in queue:
			call python class on message

		lock the mutex

	clean up rtmidi
	clean up python vm
done*/

#include <windows.h>
#include <stdio.h>
#include "RtMidi.h"
#include <vector>

struct callbackContext {
	HANDLE event;
	std::vector<unsigned char> * output;
};

void in_callback(double dt, std::vector<unsigned char> *message, void *userData)
{
	callbackContext* con = (callbackContext*) userData;
	unsigned int nBytes = message->size();
	if(nBytes > 0)
	{
		printf("Called MIDI callback.\n");
		*(con->output) = *(message);
		SetEvent(con->event);
	}
}

int main()
{
	callbackContext c;
	c.event = CreateEvent(0, FALSE, FALSE, 0);
	c.output = new std::vector<unsigned char>;

	RtMidiIn *midiin = new RtMidiIn();

	printf("MIDI In Ports:\n");
	unsigned int nPorts = midiin->getPortCount();
	for(int i=0;i<nPorts;++i)
		printf("\t%d: %s\n", i, midiin->getPortName(i).c_str());

	midiin->openPort(1);
	midiin->ignoreTypes(false, false, false);
	midiin->setCallback( &in_callback, &c.event );

	printf("Waiting for MIDI messages...\n");

	while(true)
	{
		WaitForSingleObject(c.event, INFINITE);
		printf("Received a MIDI message in main:\n");
		for(std::vector<unsigned char>::iterator p = c.output->begin();p != c.output->end();++p)
			printf("%X ", *p);
		printf("\n");
	}

	return 0;
}
