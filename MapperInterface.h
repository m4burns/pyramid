#ifndef _MAPPERINTERFACE_H_
#define _MAPPERINTERFACE_H_

#include <vector>
#include <string>

class MapperCtl;

class MapperInterface {
public:
	MapperInterface();

	std::vector<std::string> getInputs();
	std::vector<std::string> getOutputs();

	std::vector<bool> getActiveIns();
	std::vector<bool> getActiveOuts();

private:
	MapperCtl* ctl;
};

#endif

