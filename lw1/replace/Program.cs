using System;
using System.IO;

namespace replace
{
    internal class Program
    {
        static private string FindAndReplace( string sourceString, string searchString, string replaceString )
        {
            string resultString = sourceString;
            int occurenceIndex = sourceString.IndexOf( searchString );

            while ( occurenceIndex != -1 )
            {
                resultString = resultString.Remove( occurenceIndex, searchString.Length );
                resultString = resultString.Insert( occurenceIndex, replaceString );

                occurenceIndex = resultString.IndexOf( searchString );
            }

            return resultString;
        }
        static int Main( string[] args )
        {
            if ( args.Length == 2 )
            {
                return 0;
            }

            if ( args.Length < 3 )
            {
                Console.WriteLine( "Неверное количество аргументов" );
                return 1;
            }

            string inputFilePath = args[ 0 ];
            string outputFilePath = args[ 1 ];
            string searchString = args.Length > 2 ? args[ 2 ] : "";
            string replaceString = args.Length > 3 ? args[ 3 ] : "";

            if ( File.Exists( inputFilePath ) )
            {
                StreamWriter outputStream = new StreamWriter( outputFilePath );
                StreamReader inputStream = new StreamReader( inputFilePath );

                while ( !inputStream.EndOfStream )
                {
                    string inputLine = inputStream.ReadLine();
                    string replacedLine = FindAndReplace( inputLine, searchString, replaceString );

                    outputStream.WriteLine( replacedLine );
                }
                inputStream.Close();
                outputStream.Close();
            }
            else
            {
                Console.WriteLine( "Файл с данными не существует" );
                return 1;
            }

            return 0;
        }
    }
}
