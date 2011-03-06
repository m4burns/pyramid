#include <cstdlib>
#include <cstdio>
#include <Python.h>

extern "C" void init_pyramid(void);
extern int mapper_main();

int main(int argc, char** argv)
{
	Py_SetProgramName(argv[0]);
	Py_Initialize();
	init_pyramid();
	PyRun_SimpleString(
	"import sys\n"
	"sys.path.append('./')\n"
	"import pyramid\n");

	FILE* fp = fopen(argv[1], "r");
	if(!fp)
	{
		printf("Could not load mapping script '%s' for reading.\n", argv[1]);
		Py_Finalize();
		exit(1);
	}

	PyRun_AnyFile(fp, argv[1]);
	fclose(fp);

	printf("About to run mapper_main().\n");

	return mapper_main();
}

