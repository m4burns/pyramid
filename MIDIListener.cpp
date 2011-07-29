#include "MIDIListener.h"
#include "RtMidi.h"

struct callbackContext {
	HANDLE accessMutex;
	HANDLE notifyEvent;
	std::vector<unsigned char> * output;
};

void input_callback(double dt, std::vector<unsigned char> *message, void *userData)
{
	callbackContext* con = (callbackContext*) userData;
	unsigned int nBytes = message->size();
	if(nBytes > 0)
	{
		WaitForSingleObject(con->accessMutex, INFINITE);
		for(std::vector<unsigned char>::iterator p = message->begin(); p != message->end(); ++p)
			con->output->push_back(*p);

		ReleaseMutex(con->accessMutex);
		SetEvent(con->notifyEvent);
	}
}

MIDIListener::MIDIListener(unsigned int port, HANDLE notifyEvent)
{
	con = new callbackContext;
	midi_data = new std::vector<unsigned char>;

	con->output = midi_data;
	con->notifyEvent = notifyEvent;
	con->accessMutex = CreateMutex(NULL, FALSE, NULL);

	in = new RtMidiIn();
	in->openPort(port);
	in->ignoreTypes(false, false, false);
	in->setCallback(&input_callback, con);
}

MIDIListener::~MIDIListener()
{	
	in->closePort();
	CloseHandle(con->accessMutex);

	delete con;
	delete midi_data;
	delete in;
}

bool MIDIListener::hasData()
{
	bool res;
	WaitForSingleObject(con->accessMutex, INFINITE);
	res = midi_data->size() > 0;
	ReleaseMutex(con->accessMutex);
	return res;
}

std::vector<unsigned char> MIDIListener::getData()
{
	std::vector<unsigned char> res;
	WaitForSingleObject(con->accessMutex, INFINITE);
	res = *midi_data;
	midi_data->clear();
	ReleaseMutex(con->accessMutex);
	return res;
}

std::map<std::string, int> MIDIListener::enumerateInputPorts()
{
	std::map<std::string, int> res;

	RtMidiIn* _in = new RtMidiIn();
	unsigned int nPorts = _in->getPortCount();
	for(unsigned int i=0;i<nPorts;++i)
		res[_in->getPortName(i)] = i;
	delete _in;

	return res;
}

