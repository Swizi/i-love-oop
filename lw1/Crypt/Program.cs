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
                Console.WriteLine( "Input file is not exists" );
                parsedArgs.isValid = false;
                return parsedArgs;
            }

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

        private static byte ConvertToByte( BitArray bits )
        {
            byte[] bytes = new byte[ 1 ];
            bits.CopyTo( bytes, 0 );
            return bytes[ 0 ];
        }

        private static byte XORByte( byte inputByte, byte key )
        {
            BitArray XORBitArray = new BitArray( new byte[] { inputByte } );
            BitArray keyBitArray = new BitArray( new byte[] { key } );
            XORBitArray.Xor( keyBitArray );

            return ConvertToByte( XORBitArray );
        }

        private static byte MixByte( byte inputByte, string command )
        {
            BitArray inputBitArray = new BitArray( new byte[] { inputByte } );
            BitArray bitArrayCopy = new BitArray( new byte[] { inputByte } );

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

            return ConvertToByte( inputBitArray );
        }

        private static void CryptFromFileToFile( string inputFilePath, string outputFilePath, byte key )
        {
            using ( FileStream inputStream = new FileStream( inputFilePath, FileMode.Open ) )
            {
                using ( FileStream outputStream = new FileStream( outputFilePath, FileMode.Create ) )
                {
                    int intByte = inputStream.ReadByte();
                    while ( intByte != -1 )
                    {
                        byte readByte = Convert.ToByte( intByte );
                        byte xoredByte = XORByte( readByte, key );
                        byte mixedByte = MixByte( xoredByte, COMMAND_CRYPT );

                        outputStream.WriteByte( mixedByte );

                        intByte = inputStream.ReadByte();
                    }
                }
            }
        }

        private static void DecryptFromFileToFile( string inputFilePath, string outputFilePath, byte key )
        {
            using ( FileStream inputStream = new FileStream( inputFilePath, FileMode.Open ) )
            {
                using ( FileStream outputStream = new FileStream( outputFilePath, FileMode.Create ) )
                {
                    int intByte = inputStream.ReadByte();
                    while ( intByte != -1 )
                    {
                        byte readByte = Convert.ToByte( intByte );
                        byte mixedByte = MixByte( readByte, COMMAND_DECRYPT );
                        byte xoredByte = XORByte( mixedByte, key );

                        outputStream.WriteByte( xoredByte );

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

            if ( command == COMMAND_CRYPT )
            {
                CryptFromFileToFile( inputFilePath, outputFilePath, key );
            }

            if ( command == COMMAND_DECRYPT )
            {
                DecryptFromFileToFile( inputFilePath, outputFilePath, key );
            }

            return 0;
        }
    }
}
