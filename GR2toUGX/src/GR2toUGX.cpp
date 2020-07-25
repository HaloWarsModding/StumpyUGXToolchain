#include <iostream>
#include "ECF/UGX/UGXFile.h"
#include "granny.h"

int main(int argc, char* argv[])
{
	//argv[0] = this exe path.
	//argv[1] = input fbx path.
	//argv[2] = final file path.
	//argv[3] = output type.

	if (argc < 4) return -1;
	std::string fileName = argv[1];
	std::string finalFilePath = argv[2];

	if (argv[3] == "m") 
	{
		UGXFile f = UGXFile::FromGR2(fileName);
		if (f.status == "OK")
		{
			f.Save(finalFilePath + ".ugx");
		}
		else return -2;
	}

	if (argv[3] == "a")
	{
		CreateUAXs(finalFilePath + ".uax");
	}

	return 0;
}