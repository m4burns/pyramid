#include <cstdlib>
#include <cstdio>
#include <Python.h>

extern "C" void init_pyramid(void);
extern int mapper_main();

int main(int argc, char** argv)
{
	freopen("pyramid.log", "w", stdout);
	Py_SetProgramName(argv[0]);
	Py_Initialize();
	init_pyramid();

	PyRun_SimpleString(
	"import sys\n"
	"sys.path.append('./')\n"
	"import pyramid\n");

	PyObject* fp = PyFile_FromString(argv[1], "r");
	if(!fp)
	{
		printf("Could not load mapping script '%s' for reading.\n", argv[1]);
		Py_Finalize();
		exit(1);
	}
	FILE* sfp = PyFile_AsFile(fp);
	PyRun_AnyFileEx(sfp, argv[1], 1);
	return mapper_main();
}

