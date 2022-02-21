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

        private static Args? ParseProgramArgs( string[] stringArgs )
        {
            if ( stringArgs.Length < 3 )
            {
                Console.WriteLine( "Not enough arguments. Params should be: <input file name> <output file name> <search string> <replace string>" );
                return null;
            }

            Args args = new Args();

            args.inputFilePath = stringArgs[ 0 ];
            args.outputFilePath = stringArgs[ 1 ];
            args.searchString = stringArgs[ 2 ];
            args.replaceString = stringArgs.Length == 4 ? stringArgs[ 3 ] : "";

            return args;
        }

        private static void ReplaceString(Args args)
        {
            string inputFilePath = args.inputFilePath;
            string outputFilePath = args.outputFilePath;
            string searchString = args.searchString;
            string replaceString = args.replaceString;

            using ( StreamReader inputStream = new StreamReader( inputFilePath ) )
            {
                using ( StreamWriter outputStream = new StreamWriter( outputFilePath ) )
                {
                    while ( !inputStream.EndOfStream )
                    {
                        string inputLine = inputStream.ReadLine();
                        string replacedLine = inputLine;
                        if ( searchString.Length != 0 )
                        {
                            replacedLine = inputLine.Replace( searchString, replaceString );
                        }

                        outputStream.WriteLine( replacedLine );
                    }
                }
            }
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

            Args? parsedArgs = ParseProgramArgs( args );

            if ( parsedArgs == null )
            {
                return 1;
            }

            if ( !IsFileCanBeOpened( parsedArgs.Value.inputFilePath, FileAccess.Read ) )
            {
                Console.WriteLine( "Input file can not be opened" );
                return 1;
            }

            if ( !IsFileCanBeOpened( parsedArgs.Value.outputFilePath, FileAccess.Write ) )
            {
                Console.WriteLine( "Output file can not be opened" );
                return 1;
            }

            ReplaceString( parsedArgs.Value );

            return 0;
        }
    }
}
