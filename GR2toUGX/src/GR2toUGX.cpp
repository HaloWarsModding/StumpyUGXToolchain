#include <iostream>
#include "ECF/UGX/UGXFile.h"
#include "granny.h"

int main(int argc, char* argv[])
{
	//argv[0] = this exe path.
	//argv[1] = input fbx path.
	//argv[2] = final file path.
	//argv[3] = output type.

	std::cout << argv[0] << '\n';
	std::cout << argv[1] << '\n';
	std::cout << argv[2] << '\n';
	std::cout << argv[3] << '\n';

	std::string fileName = "";
	std::string finalFilePath = "";
	if (argc < 4)
	{
		std::cout << "Not enough args." << '\n';
		goto END;
	}

	fileName = argv[1];
	finalFilePath = argv[2];

	if (std::string(argv[3]) == "m")
	{
		UGXFile f = UGXFile::FromGR2(fileName);
		if (f.status == "OK")
		{
			f.Save(finalFilePath + ".ugx");
			std::cout << "Saved." << '\n';
		}
		else
		{
			std::cout << f.status << '\n';
			goto END;
		}
	}

	if (std::string(argv[3]) == "a")
	{
		CreateUAXs(finalFilePath + ".uax");
	}


	END:
	std::cout << "Done." << '\n';
	return 0;
}