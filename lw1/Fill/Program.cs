using System;
using System.Collections.Generic;
using System.IO;

namespace Fill
{
    internal class Program
    {
        const int MAX_IMAGE_WIDTH = 100;
        const int MAX_IMAGE_HEIGHT = 100;

        struct Args
        {
            public string inputFilePath;
            public string outputFilePath;
            public bool isValid;
        }

        struct CellPosition
        {
            public int rowIndex;
            public int columnIndex;
            public bool isValid()
            {
                return rowIndex != -1 && columnIndex != -1;
            }
        }

        static int Main( string[] args )
        {
            Args parsedArgs = ParseArgs( args );

            if ( !parsedArgs.isValid )
            {
                return 1;
            }

            string inputFilePath = parsedArgs.inputFilePath;
            string outputFilePath = parsedArgs.outputFilePath;

            char[][] image = GetImageFromFile( inputFilePath );

            FillImage( image );

            PrintImageToFile( image, outputFilePath );

            return 0;
        }

        private static Args ParseArgs( string[] stringArgs )
        {
            Args args = new Args();
            args.isValid = true;

            if ( stringArgs.Length != 2 )
            {
                Console.WriteLine( "Incorrect arguments count. Params should be: <input file name> <output file name>" );
                args.isValid = false;
                return args;
            }

            args.inputFilePath = stringArgs[ 0 ];
            args.outputFilePath = stringArgs[ 1 ];

            if ( !File.Exists( args.inputFilePath ) )
            {
                Console.WriteLine( "Input file is not exists" );
                args.isValid = false;
                return args;
            }

            return args;
        }

        private static void InitializeRow( List<char[]> image, int rowLength )
        {
            char[] row = new char[ rowLength ];
            for ( int columnIndex = 0; columnIndex < rowLength; columnIndex++ )
            {
                row[ columnIndex ] = ' ';
            }
            image.Add( row );
        }

        private static char[][] GetImageFromFile( string inputFilePath )
        {
            List<char[]> image = new List<char[]>();
            int rowIndex = -1;

            using ( StreamReader inputStream = new StreamReader( inputFilePath ) )
            {
                while ( !inputStream.EndOfStream )
                {
                    rowIndex++;
                    string inputLine = inputStream.ReadLine();
                    int rowLength = inputLine.Length;
                    if ( rowIndex >= MAX_IMAGE_HEIGHT )
                    {
                        break;
                    }

                    if ( inputLine.Length >= MAX_IMAGE_WIDTH )
                    {
                        rowLength = MAX_IMAGE_WIDTH;
                    }

                    InitializeRow( image, rowLength );

                    for ( int columnIndex = 0; columnIndex < rowLength; columnIndex++ )
                    {
                        image[ rowIndex ][ columnIndex ] = inputLine[ columnIndex ];
                    }
                }
            }

            return image.ToArray();
        }

        private static Queue<CellPosition> FindStartCells( char[][] image )
        {
            Queue<CellPosition> startCellPositions = new Queue<CellPosition>();

            for ( int rowIndex = 0; rowIndex < image.Length; rowIndex++ )
            {
                for ( int columnIndex = 0; columnIndex < image[ rowIndex ].Length; columnIndex++ )
                {
                    if ( image[ rowIndex ][ columnIndex ] == 'O' )
                    {
                        CellPosition foundStartPosition = new CellPosition();
                        foundStartPosition.rowIndex = rowIndex;
                        foundStartPosition.columnIndex = columnIndex;
                        startCellPositions.Enqueue( foundStartPosition );
                    }
                }
            }

            return startCellPositions;
        }

        private static void CheckCell( int rowIndex, int columnIndex, char[][] image, Queue<CellPosition> fillQueue )
        {
            if ( rowIndex >= 0 && rowIndex < image.Length && columnIndex >= 0 && columnIndex < image[ rowIndex ].Length && image[ rowIndex ][ columnIndex ] == ' ' )
            {
                CellPosition newCellPosition = new CellPosition();
                newCellPosition.rowIndex = rowIndex;
                newCellPosition.columnIndex = columnIndex;
                image[ newCellPosition.rowIndex ][ newCellPosition.columnIndex ] = '.';
                fillQueue.Enqueue( newCellPosition );
            }
        }

        private static void FillAroundCell( char[][] image, CellPosition startCellPosition )
        {
            Queue<CellPosition> fillQueue = new Queue<CellPosition>();
            fillQueue.Enqueue( startCellPosition );

            while ( fillQueue.Count > 0 )
            {
                CellPosition cellPosition = fillQueue.Dequeue();

                // 1 2              3
                // 4 'cellPosition' 5
                // 6 7              8

                // 1
                CheckCell( cellPosition.rowIndex - 1, cellPosition.columnIndex - 1, image, fillQueue );
                // 2
                CheckCell( cellPosition.rowIndex - 1, cellPosition.columnIndex, image, fillQueue );
                // 3
                CheckCell( cellPosition.rowIndex - 1, cellPosition.columnIndex + 1, image, fillQueue );
                // 4
                CheckCell( cellPosition.rowIndex, cellPosition.columnIndex - 1, image, fillQueue );
                // 5
                CheckCell( cellPosition.rowIndex, cellPosition.columnIndex + 1, image, fillQueue );
                // 6
                CheckCell( cellPosition.rowIndex + 1, cellPosition.columnIndex - 1, image, fillQueue );
                // 7
                CheckCell( cellPosition.rowIndex + 1, cellPosition.columnIndex, image, fillQueue );
                // 8
                CheckCell( cellPosition.rowIndex + 1, cellPosition.columnIndex + 1, image, fillQueue );
            }
        }

        private static void FillImage( char[][] image )
        {
            Queue<CellPosition> startCellPositions = FindStartCells( image );

            while ( startCellPositions.Count > 0 )
            {
                CellPosition startCellPosition = startCellPositions.Dequeue();
                FillAroundCell( image, startCellPosition );
            }
        }

        private static void PrintImageToFile( char[][] image, string outputFilePath )
        {
            using ( StreamWriter outputStream = new StreamWriter( outputFilePath ) )
            {
                for ( int rowIndex = 0; rowIndex < image.Length; rowIndex++ )
                {
                    for ( int columnIndex = 0; columnIndex < image[ rowIndex ].Length; columnIndex++ )
                    {
                        outputStream.Write( image[ rowIndex ][ columnIndex ] );
                    }
                    outputStream.WriteLine();
                }
            }
        }
    }
}
