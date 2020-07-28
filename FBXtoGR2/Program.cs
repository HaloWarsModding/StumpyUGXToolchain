using Firaxis.Framework.Export;

class Program
{
    static void Main(string[] args)
    {
        GrannyExporterFBX.ExportFBXFile(args[0], args[1], null);
    }
}
