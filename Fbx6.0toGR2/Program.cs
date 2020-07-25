using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Firaxis.Framework.Granny;
using Firaxis.Framework.Converters;
using Firaxis.Framework.Export;

class Program
{
    static void Main(string[] args)
    {
        string path = "I:\\BlenderUGXToolchain\\Fbx7.4toFbx6.0\\bin\\Handgun_Packed7.fbx_6.0converted.fbx";
        GrannyExporterFBX.ExportFBXFile(path, path + ".gr2", null);
    }
}
