#include "Pyramid.h"
#include <cstdlib>
#include <cstdio>
#include <Python.h>
#include <windows.h>

extern "C" void init_pyramid(void);
extern void start_mapper();
extern void kill_mapper();

Pyramid::Pyramid(const char* script)
{
	freopen("pyramid.log", "w", stdout);
	freopen("pyramid.log", "a", stderr);
	Py_SetProgramName(".\\pyramid");
	Py_Initialize();
	init_pyramid();

	PyRun_SimpleString(
	"import sys\n"
	"sys.path.append('./')\n"
	"sys.stderr = open('python_errors.log', 'w', 0)\n"
	"sys.stdout = open('pyramid.log', 'a', 0)\n"
	"import pyramid\n");

	char* fn_local = new char[strlen(script)+1];
	strcpy(fn_local, script);

	PyObject* fp = PyFile_FromString(fn_local, "r");
	if(!fp)
	{
		printf("Could not load mapping script '%s' for reading.\n", script);
		Py_Finalize();
		exit(1);
	}
	FILE* sfp = PyFile_AsFile(fp);

	PyRun_AnyFileEx(sfp, script, 1);

	delete[] fn_local;
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

