#include "FileParser_t.h"

int main(int argc, char *argv[])
{
	FileParser_t fp;	

	for(int i = 1; i < argc; ++i)
	{
		fp.RunParser(argv[i]);
	}

	return 0;
}
