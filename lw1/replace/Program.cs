using System;
using System.IO;

namespace replace
{
    internal class Program
    {
        static void Main( string[] args )
        {
            string inputFilePath = args[ 0 ];
            string outputFilePath = args[ 1 ];
            string searchString = args.Length > 2 ? args[2] : "";
            string replaceString = args.Length > 3 ? args[ 3 ]: "";

            StreamWriter outputStream = new StreamWriter( outputFilePath );
            if (File.Exists(inputFilePath))
            {
                StreamReader inputStream = new StreamReader( inputFilePath );
                while ( !inputStream.EndOfStream )
                {
                    string inputLine = inputStream.ReadLine();
                    string replacedLine = inputLine.Replace( searchString, replaceString );

                    outputStream.WriteLine( replacedLine );
                }
                inputStream.Close();
            } else
            {
                outputStream.WriteLine( "Файл с данными не существует" );
            }
            outputStream.Close();
        }
    }
}
