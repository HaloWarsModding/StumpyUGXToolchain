#include <iostream>
#include <fbxsdk.h>
#include "common.h"

int main(int argc, char *argv[])
{
	std::string filePath("I:\\BlenderUGXToolchain\\Fbx7.4toFbx6.0\\bin\\untitled11.fbx");

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

		if (!lResult) goto END;
		else 
		{
			// Export the scene.
			lResult = lExporter->Export(lScene);
			if (!lResult)
			{
				goto END;
			}
		}
		// Destroy the exporter.
		lExporter->Destroy();
	}
	else goto END;

	DestroySdkObjects(lSdkManager, lResult);

	END:

	while (1) {}
	return 0;
}
