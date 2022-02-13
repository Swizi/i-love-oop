using System;
using System.IO;

namespace Replace
{
    internal class Program
    {
        private static bool IsFileCanBeOpened(string filePath, FileAccess access)
        {
            try
            {
                File.Open(filePath, FileMode.Open, access).Dispose();
                return true;
            }
            catch (IOException)
            {
                return false;
            }
        }

        static int Main(string[] args)
        {
            if (args.Length == 2)
            {
                return 0;
            }

            if (args.Length < 3)
            {
                Console.WriteLine("Not enough arguments. Params should be: <input file name> <output file name> <search string> <replace string>");
                return 1;
            }

            string inputFilePath = args[0];
            string outputFilePath = args[1];
            string searchString = args.Length > 2 ? args[2] : "";
            string replaceString = args.Length > 3 ? args[3] : "";

            if (!IsFileCanBeOpened(inputFilePath, FileAccess.Read))
            {
                Console.WriteLine("Input file can not be opened");
                return 1;
            }

            if (!IsFileCanBeOpened(inputFilePath, FileAccess.Write))
            {
                Console.WriteLine("Output file can not be opened");
                return 1;
            }

            StreamWriter outputStream = new StreamWriter(outputFilePath);
            StreamReader inputStream = new StreamReader(inputFilePath);

            while (!inputStream.EndOfStream)
            {
                string inputLine = inputStream.ReadLine();
                string replacedLine = inputLine.Replace(searchString, replaceString);

                outputStream.WriteLine(replacedLine);
            }
            inputStream.Close();
            outputStream.Close();

            return 0;
        }
    }
}
