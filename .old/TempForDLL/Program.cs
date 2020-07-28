using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using Firaxis.Framework.Export;

namespace FBX6toGR2
{
    [ComVisible(true)]
    [ClassInterface(ClassInterfaceType.AutoDual)]
    [Guid("485B98AF-53D4-4148-B2BD-CC3912340ADF")]
    public class FBX6toGR2Class
    {
        public void Convert(string inPath, string outPath)
        {
            GrannyExporterFBX.ExportFBXFile(inPath, outPath, null);
        }
    }
}