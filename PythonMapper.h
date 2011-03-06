#ifndef _PYTHONMAPPER_H_
#define _PYTHONMAPPER_H_

#include <map>

struct MIDINote {
	unsigned char channel;
	unsigned char note;
	unsigned char velocity;
	int state;
};

struct MIDIControlVal {
	unsigned char channel;
	unsigned char control;
	unsigned char value;
};

class PythonMapper {
public:
	PythonMapper();
	virtual ~PythonMapper();
	virtual bool selectPorts(std::string portsConfig);

	virtual void mapNote(int port, MIDINote note) = 0;
	virtual void mapControl(int port, MIDIControlVal cv) = 0;

	virtual void sendNote(int port, MIDINote note);
	virtual void sendControl(int port, MIDIControlVal cv);

protected:
	std::map<int, int> inmap; // actual -> local
	std::map<int, int> outmap; // local -> actual
	friend class MapperCtl;
};

#endif

