using System;
using System.IO;

namespace Replace
{
    internal class Program
    {
        struct Args
        {
            public string inputFilePath;
            public string outputFilePath;
            public string searchString;
            public string replaceString;
        }

        private static Args? ParseArgs( string[] stringArgs )
        {
            Args args = new Args();

            if ( stringArgs.Length < 3 )
            {
                Console.WriteLine( "Not enough arguments. Params should be: <input file name> <output file name> <search string> <replace string>" );
                return null;
            }

            args.inputFilePath = stringArgs[ 0 ];
            args.outputFilePath = stringArgs[ 1 ];
            args.searchString = stringArgs[ 2 ];
            args.replaceString = stringArgs.Length == 4 ? stringArgs[ 3 ] : "";

            return args;
        }

        private static bool IsFileCanBeOpened( string filePath, FileAccess access )
        {
            try
            {
                File.Open( filePath, FileMode.Open, access ).Dispose();
                return true;
            }
            catch ( IOException )
            {
                return false;
            }
        }

        static int Main( string[] args )
        {
            if ( args.Length == 2 )
            {
                return 0;
            }

            Args? parsedArgs = ParseArgs( args );

            if ( parsedArgs == null )
            {
                return 1;
            }

            string inputFilePath = parsedArgs.Value.inputFilePath;
            string outputFilePath = parsedArgs.Value.outputFilePath;
            string searchString = parsedArgs.Value.searchString;
            string replaceString = parsedArgs.Value.replaceString;

            if ( !IsFileCanBeOpened( inputFilePath, FileAccess.Read ) )
            {
                Console.WriteLine( "Input file can not be opened" );
                return 1;
            }

            if ( !IsFileCanBeOpened( outputFilePath, FileAccess.Write ) )
            {
                Console.WriteLine( "Output file can not be opened" );
                return 1;
            }

            StreamWriter outputStream = new StreamWriter( outputFilePath );
            StreamReader inputStream = new StreamReader( inputFilePath );

            while ( !inputStream.EndOfStream )
            {
                string inputLine = inputStream.ReadLine();
                string replacedLine = inputLine.Replace( searchString, replaceString );

                outputStream.WriteLine( replacedLine );
            }
            inputStream.Close();
            outputStream.Close();

            return 0;
        }
    }
}
