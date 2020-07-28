#include <Windows.h>
#include <ShlObj_core.h>
#include <direct.h>
#include <iostream>
#include "fbxsdk.h"
#include "src/fbxcommon.h"
#include "granny.h"
#include "ECF/UGX/UGXFile.h"

int main(int argc, char* argv[])
{
	bool exportUGX = false;
	bool exportGR2 = false;
	enum ExportType { Animation, Mesh, Null } exportType = Null;

	for (int i = 3; i < argc; i++)
	{
		if (std::string(argv[i]) == "exUGX") exportUGX = true;
		if (std::string(argv[i]) == "exGR2") exportGR2 = true;
		if (std::string(argv[i]) == "a") exportType = Animation;
		if (std::string(argv[i]) == "m") exportType = Mesh;
	}

	std::string log = "";

	//file locations
	std::string inputDir(argv[1]);
	std::string outputDir(argv[2]);

	//get fbx's local folder
	std::string localDir = std::string(argv[1]).substr(0, std::string(argv[1]).length() - 4);
	std::cout << localDir << '\n';

	//check if local folder exists
	DWORD ftyp = GetFileAttributesA(localDir.c_str());
	if (ftyp == INVALID_FILE_ATTRIBUTES) _mkdir(localDir.c_str());

#pragma region FBX7 to FBX6
	FbxManager* lSdkManager = NULL;
	FbxScene* lScene = NULL;

	InitializeSdkObjects(lSdkManager, lScene);

	bool lResult = LoadScene(lSdkManager, lScene, inputDir.c_str());
	if (lResult)
	{
		// Retrieve the writer ID according to the description of file format.
		int lFormat = lSdkManager->GetIOPluginRegistry()->FindWriterIDByDescription("FBX 6.0 binary (*.fbx)");
		FbxExporter* lExporter = FbxExporter::Create(lSdkManager, "");

		// Initialize the exporter.
		lResult = lExporter->Initialize((localDir + std::string("temp.fbx")).c_str(), lFormat, lSdkManager->GetIOSettings());
		if (!lResult) log = "Error at FBX7 to FBX6!";
		else 
		{
			// Export the scene.
			lResult = lExporter->Export(lScene);
			if (!lResult) log = "Error at FBX7 to FBX6!";
		}

		// Destroy the exporter.
		lExporter->Destroy();
	}
	else log = "Error at FBX7 to FBX6!";

	DestroySdkObjects(lSdkManager, lResult);
#pragma endregion
#pragma region FBX6 to GR2
	std::string fbxtogr2exePath = std::string(argv[0]).substr(0, std::string(argv[0]).size() - std::string(argv[0]).find_last_of('\\'));

	std::string systemCall(fbxtogr2exePath + "\\FBXtoGR2.exe " + localDir + "temp.fbx" + " " + localDir + "temp.gr2");
	std::cout << fbxtogr2exePath + "\\FBXtoGR2.exe " << '\n';
	std::system(systemCall.c_str());

	if (exportGR2)
	{
		CopyFileA(std::string(localDir + "temp.gr2").c_str(), std::string(outputDir + ".gr2").c_str(), false);
	}

#pragma endregion
#pragma region GR2 Preprocess

	granny_file* gf = GrannyReadEntireFile(std::string(localDir + "temp.gr2").c_str());
	if (gf == NULL) log = "Could not find GR2!";
	granny_file_info* gfi = GrannyGetFileInfo(gf);
	if (gfi == NULL) log = "Could not get GFI!";

	granny_real32 DesiredUnitsPerMeter = 1.0f;
	granny_real32 DesiredOrigin[] = { 0, 0, 0 };
	granny_real32 DesiredRight[] = { -1,  0, 0 };
	granny_real32 DesiredUp[] = { 0,  0, 1 };
	granny_real32 DesiredBack[] = { 0, -1, 0 };

	granny_real32 Affine3[3];
	granny_real32 Linear3x3[9];
	granny_real32 InverseLinear3x3[9];

	GrannyComputeBasisConversion(
		gfi,
		DesiredUnitsPerMeter,
		DesiredOrigin,
		DesiredRight,
		DesiredUp,
		DesiredBack,
		Affine3, 
		Linear3x3, 
		InverseLinear3x3);

	GrannyTransformFile(
		gfi, 
		Affine3, 
		Linear3x3, 
		InverseLinear3x3, 
		1e-5f, 1e-5f, 
		GrannyRenormalizeNormals | GrannyReorderTriangleIndices);

#pragma endregion
#pragma region GR2 to UGX

	if (exportType == Mesh)
	{
		UGXFile ugxF = UGXFile::FromGR2("C:\\Users\\Jake\\AppData\\Local\\StumpyUGXToolchain\\temp.xml", gfi);
		if (ugxF.status == "OK") ugxF.Save(outputDir);
		else std::cout << ugxF.status << '\n';
	}

	if (exportType == Animation)
	{
		CreateUAXs(outputDir, gfi);
	}

#pragma endregion
#pragma endregion

	if (log != "") std::cout << '\n' << log << '\n' << '\n';

	std::cout << inputDir << '\n' << outputDir << '\n';





	return 0;
}