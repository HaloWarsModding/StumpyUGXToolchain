#include <iostream>
#include <fbxsdk.h>
#include "common.h"

int main(int argc, char *argv[])
{
	std::string filePath("I:\\BlenderUGXToolchain\\Fbx7.4toFbx6.1\\bin\\Handgun_Packed7.fbx");

	FbxManager* lSdkManager = NULL;
	FbxScene* lScene = NULL;

	InitializeSdkObjects(lSdkManager, lScene);

	bool lResult = LoadScene(lSdkManager, lScene, filePath.c_str());
	if (lResult)
	{
		std::string newFilePath = filePath + std::string("_6.0converted.fbx");

		// Retrieve the writer ID according to the description of file format.
		int lFormat = lSdkManager->GetIOPluginRegistry()->FindWriterIDByDescription("FBX 6.0 binary (*.fbx)");
		FbxExporter* lExporter = FbxExporter::Create(lSdkManager, "");

		// Initialize the exporter.
		lResult = lExporter->Initialize(newFilePath.c_str(), lFormat, lSdkManager->GetIOSettings());

		if (!lResult) return -1;
		else 
		{
			// Export the scene.
			lResult = lExporter->Export(lScene);
			if (!lResult)
			{
				return -2;
			}
		}
		// Destroy the exporter.
		lExporter->Destroy();
	}
	else return -3;

	DestroySdkObjects(lSdkManager, lResult);
	return 0;
}
