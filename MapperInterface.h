#ifndef _MAPPERINTERFACE_H_
#define _MAPPERINTERFACE_H_

#include <vector>
#include <string>

class MapperCtl;

class MapperInterface {
public:
	MapperInterface();

	std::vector<std::pair<std::string, bool> > getInputs();
	std::vector<std::pair<std::string, bool> > getOutputs();

private:
	MapperCtl* ctl;
};

#endif

