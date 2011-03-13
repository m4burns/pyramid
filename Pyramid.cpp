#include "Pyramid.h"
#include <cstdlib>
#include <cstdio>
#include <Python.h>
#include <windows.h>

extern "C" void init_pyramid(void);
extern void start_mapper();
extern void kill_mapper();

Pyramid::Pyramid(char* script)
{
	freopen("pyramid.log", "w", stdout);
	Py_SetProgramName(".\\pyramid");
	Py_Initialize();
	init_pyramid();

	PyRun_SimpleString(
	"import sys\n"
	"sys.path.append('./')\n"
	"import pyramid\n");

	PyObject* fp = PyFile_FromString(script, "r");
	if(!fp)
	{
		printf("Could not load mapping script '%s' for reading.\n", script);
		Py_Finalize();
		exit(1);
	}
	FILE* sfp = PyFile_AsFile(fp);
	PyRun_AnyFileEx(sfp, script, 1);
}

Pyramid::~Pyramid()
{
	Py_Finalize();
}

void Pyramid::start()
{
	start_mapper();
}

void Pyramid::stop()
{
	kill_mapper();
}

