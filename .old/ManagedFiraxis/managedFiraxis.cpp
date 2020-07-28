#include <string>
#include <iostream>
#include "managedFiraxis.h"
#using <Firaxis.Framework.dll>
using namespace Firaxis::Framework::Export;

void FBXtoGR2::Convert(std::string inPath, std::string outPath)
{
	std::cout << inPath << '\n' << outPath << '\n';
	std::cout << GrannyExporterFBX::ExportFBXFile(gcnew System::String(inPath.c_str()), gcnew System::String(inPath.c_str()), nullptr);
}