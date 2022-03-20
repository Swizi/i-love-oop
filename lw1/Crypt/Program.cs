using System;
using System.Collections;
using System.IO;

namespace Crypt
{
    internal class Program
    {
        const string COMMAND_CRYPT = "CRYPT";
        const string COMMAND_DECRYPT = "DECRYPT";

        struct Args
        {
            public string command;
            public string inputFilePath;
            public string outputFilePath;
            public byte key;
            public bool isValid;
        }

        private static Args ParseArgs( string[] args )
        {
            Args parsedArgs = new Args();
            parsedArgs.isValid = true;

            if ( args.Length != 4 )
            {
                Console.WriteLine( "Incorrect params count. Params should be: <command> <input file> <output file> <key>" );
                parsedArgs.isValid = false;
                return parsedArgs;
            }

            string command = args[ 0 ].ToUpper();

            if ( command != COMMAND_CRYPT && command != COMMAND_DECRYPT )
            {
                Console.WriteLine( "Incorrect <command> param. <command> should be: crypt or decrypt" );
                parsedArgs.isValid = false;
                return parsedArgs;
            }

            if ( !File.Exists( args[ 1 ] ) )
            {
                Console.WriteLine( "Input file is not exists or can not be opened" );
                parsedArgs.isValid = false;
                return parsedArgs;
            }

            // Проверить доступ outputFile, inputFile

            try
            {
                byte test = Convert.ToByte( args[ 3 ] );
            }
            catch ( Exception )
            {
                Console.WriteLine( "Incorrect <key> value. <key> should be number in 0...255 range" );
                parsedArgs.isValid = false;
                return parsedArgs;
            }

            parsedArgs.command = command;
            parsedArgs.inputFilePath = args[ 1 ];
            parsedArgs.outputFilePath = args[ 2 ];
            parsedArgs.key = Convert.ToByte( args[ 3 ] );

            return parsedArgs;
        }

        private static byte ConvertBitArrayToByte( BitArray bits )
        {
            byte[] bytes = new byte[ 1 ];
            bits.CopyTo( bytes, 0 );
            return bytes[ 0 ];
        }

        private static BitArray XORBitArray( BitArray bitArray, byte key )
        {
            BitArray keyBitArray = new BitArray( new byte[] { key } );
            bitArray.Xor( keyBitArray );

            return bitArray;
        }

        private static byte EncryptByte( byte inputByte, byte key, string command )
        {
            BitArray inputBitArray = new BitArray( new byte[] { inputByte } );
            BitArray xoredBitArray = XORBitArray( inputBitArray, key );
            BitArray mixedBitArray = MixBitArray( xoredBitArray, command );

            return ConvertBitArrayToByte( mixedBitArray );
        }

        private static BitArray MixBitArray( BitArray inputBitArray, string command )
        {
            BitArray bitArrayCopy = new BitArray( inputBitArray );

            if ( command == COMMAND_CRYPT )
            {
                inputBitArray[ 0 ] = bitArrayCopy[ 5 ];
                inputBitArray[ 1 ] = bitArrayCopy[ 6 ];
                inputBitArray[ 2 ] = bitArrayCopy[ 0 ];
                inputBitArray[ 3 ] = bitArrayCopy[ 1 ];
                inputBitArray[ 4 ] = bitArrayCopy[ 2 ];
                inputBitArray[ 5 ] = bitArrayCopy[ 7 ];
                inputBitArray[ 6 ] = bitArrayCopy[ 3 ];
                inputBitArray[ 7 ] = bitArrayCopy[ 4 ];
            }

            if ( command == COMMAND_DECRYPT )
            {
                inputBitArray[ 0 ] = bitArrayCopy[ 2 ];
                inputBitArray[ 1 ] = bitArrayCopy[ 3 ];
                inputBitArray[ 2 ] = bitArrayCopy[ 4 ];
                inputBitArray[ 3 ] = bitArrayCopy[ 6 ];
                inputBitArray[ 4 ] = bitArrayCopy[ 7 ];
                inputBitArray[ 5 ] = bitArrayCopy[ 0 ];
                inputBitArray[ 6 ] = bitArrayCopy[ 1 ];
                inputBitArray[ 7 ] = bitArrayCopy[ 5 ];
            }

            return inputBitArray;
        }

        private static void EncryptFileToFile( string inputFilePath, string outputFilePath, byte key, string command )
        {
            using ( FileStream inputStream = new FileStream( inputFilePath, FileMode.Open ) )
            {
                // Нужен ли is_open?
                using ( FileStream outputStream = new FileStream( outputFilePath, FileMode.Create ) )
                {
                    int intByte = inputStream.ReadByte();
                    // убрать int?
                    while ( intByte != -1 )
                    {
                        byte readByte = Convert.ToByte( intByte );
                        byte outByte = EncryptByte( readByte, key, command );
                        outputStream.WriteByte( outByte );

                        intByte = inputStream.ReadByte();
                    }
                }
            }
        }
        static int Main( string[] args )
        {
            Args parsedArgs = ParseArgs( args );

            if ( !parsedArgs.isValid )
            {
                return 1;
            }

            string command = parsedArgs.command;
            string inputFilePath = parsedArgs.inputFilePath;
            string outputFilePath = parsedArgs.outputFilePath;
            byte key = parsedArgs.key;

            EncryptFileToFile( inputFilePath, outputFilePath, key, command );

            return 0;
        }
    }
}
