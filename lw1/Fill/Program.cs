using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace Fill
{
    internal class Program
    {
        const int MAX_IMAGE_LENGTH = 100;

        struct Args
        {
            public string inputFilePath;
            public string outputFilePath;
        }

        struct CellPosition
        {
            public int rowIndex;
            public int columnIndex;
        }

        private static Args? ParseArgs( string[] stringArgs )
        {
            if ( stringArgs.Length != 2 )
            {
                Console.WriteLine( "Incorrect arguments count. Params should be: <input file name> <output file name>" );
                return null;
            }

            Args args = new Args();

            args.inputFilePath = stringArgs[ 0 ];
            args.outputFilePath = stringArgs[ 1 ];

            if ( !File.Exists( args.inputFilePath ) )
            {
                Console.WriteLine( "Input file is not exists" );
                return null;
            }

            return args;
        }

        private static void InitializeRow( ref char[][] image, int rowLength, int rowIndex )
        {

            char[] row = new char[ rowLength ];
            for ( int columnIndex = 0; columnIndex < rowLength; columnIndex++ )
            {
                row[ columnIndex ] = ' ';
            }
            image[ rowIndex ] = row;
        }

        private static char[][] GetImageFromFile( string inputFilePath )
        {
            int rowsCount = 0;

            using ( StreamReader inputStream = new StreamReader( inputFilePath ) )
            {
                while ( !inputStream.EndOfStream )
                {
                    rowsCount++;
                    string inputLine = inputStream.ReadLine();
                }
            }

            if ( rowsCount > MAX_IMAGE_LENGTH )
            {
                rowsCount = MAX_IMAGE_LENGTH;
            }

            char[][] image = new char[ rowsCount ][];
            int rowIndex = -1;

            using ( StreamReader inputStream = new StreamReader( inputFilePath ) )
            {
                while ( !inputStream.EndOfStream )
                {
                    rowIndex++;
                    string inputLine = inputStream.ReadLine();
                    int rowLength = inputLine.Length;
                    if ( inputLine.Length > MAX_IMAGE_LENGTH )
                    {
                        rowLength = MAX_IMAGE_LENGTH;
                    }

                    InitializeRow( ref image, rowLength, rowIndex );

                    for ( int columnIndex = 0; columnIndex < rowLength; columnIndex++ )
                    {
                        image[ rowIndex ][ columnIndex ] = inputLine[ columnIndex ];
                    }
                }
            }

            return image;
        }

        private static CellPosition FindStartCell( ref char[][] image, CellPosition lastStartCellPosition )
        {
            CellPosition startCellPosition = new CellPosition();
            startCellPosition.rowIndex = -1;
            startCellPosition.columnIndex = -1;
            bool isFoundStartCell = false;
            int lastStartCellPositionRowIndex = lastStartCellPosition.rowIndex;

            if ( lastStartCellPosition.rowIndex == -1 && lastStartCellPosition.columnIndex == -1 )
            {
                lastStartCellPositionRowIndex = 0;
            }

            for ( int rowIndex = lastStartCellPositionRowIndex; rowIndex < image.Length; rowIndex++ )
            {
                for ( int columnIndex = 0; columnIndex < image[ rowIndex ].Length; columnIndex++ )
                {
                    if ( image[ rowIndex ][ columnIndex ] == 'O' && lastStartCellPosition.rowIndex != rowIndex && lastStartCellPosition.columnIndex != columnIndex )
                    {
                        startCellPosition.rowIndex = rowIndex;
                        startCellPosition.columnIndex = columnIndex;

                        isFoundStartCell = true;
                    }

                    if ( isFoundStartCell )
                    {
                        break;
                    }
                }

                if ( isFoundStartCell )
                {
                    break;
                }
            }

            return startCellPosition;
        }

        private static void FillAroundCell( ref char[][] image, CellPosition startCellPosition )
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
                if ( cellPosition.rowIndex - 1 >= 0 && cellPosition.columnIndex - 1 >= 0 && image[ cellPosition.rowIndex - 1 ][ cellPosition.columnIndex - 1 ] == ' ' )
                {
                    CellPosition newCellPosition = new CellPosition();
                    newCellPosition.rowIndex = cellPosition.rowIndex - 1;
                    newCellPosition.columnIndex = cellPosition.columnIndex - 1;
                    image[ newCellPosition.rowIndex ][ newCellPosition.columnIndex ] = '.';
                    fillQueue.Enqueue( newCellPosition );
                }

                // 2
                if ( cellPosition.rowIndex - 1 >= 0 && image[ cellPosition.rowIndex - 1 ][ cellPosition.columnIndex ] == ' ' )
                {
                    CellPosition newCellPosition = new CellPosition();
                    newCellPosition.rowIndex = cellPosition.rowIndex - 1;
                    newCellPosition.columnIndex = cellPosition.columnIndex;
                    image[ newCellPosition.rowIndex ][ newCellPosition.columnIndex ] = '.';
                    fillQueue.Enqueue( newCellPosition );
                }

                // 3
                if ( cellPosition.rowIndex - 1 >= 0 && cellPosition.columnIndex + 1 < image[ cellPosition.rowIndex - 1 ].Length && image[ cellPosition.rowIndex - 1 ][ cellPosition.columnIndex + 1 ] == ' ' )
                {
                    CellPosition newCellPosition = new CellPosition();
                    newCellPosition.rowIndex = cellPosition.rowIndex - 1;
                    newCellPosition.columnIndex = cellPosition.columnIndex + 1;
                    image[ newCellPosition.rowIndex ][ newCellPosition.columnIndex ] = '.';
                    fillQueue.Enqueue( newCellPosition );
                }

                // 4
                if ( cellPosition.columnIndex - 1 >= 0 && image[ cellPosition.rowIndex ][ cellPosition.columnIndex - 1 ] == ' ' )
                {
                    CellPosition newCellPosition = new CellPosition();
                    newCellPosition.rowIndex = cellPosition.rowIndex;
                    newCellPosition.columnIndex = cellPosition.columnIndex - 1;
                    image[ newCellPosition.rowIndex ][ newCellPosition.columnIndex ] = '.';
                    fillQueue.Enqueue( newCellPosition );
                }

                // 5
                if ( cellPosition.columnIndex + 1 < image[ cellPosition.rowIndex ].Length && image[ cellPosition.rowIndex ][ cellPosition.columnIndex + 1 ] == ' ' )
                {
                    CellPosition newCellPosition = new CellPosition();
                    newCellPosition.rowIndex = cellPosition.rowIndex;
                    newCellPosition.columnIndex = cellPosition.columnIndex + 1;
                    image[ newCellPosition.rowIndex ][ newCellPosition.columnIndex ] = '.';
                    fillQueue.Enqueue( newCellPosition );
                }

                // 6
                if ( cellPosition.rowIndex + 1 < image.Length && cellPosition.columnIndex - 1 >= 0 && image[ cellPosition.rowIndex + 1 ][ cellPosition.columnIndex - 1 ] == ' ' )
                {
                    CellPosition newCellPosition = new CellPosition();
                    newCellPosition.rowIndex = cellPosition.rowIndex + 1;
                    newCellPosition.columnIndex = cellPosition.columnIndex - 1;
                    image[ newCellPosition.rowIndex ][ newCellPosition.columnIndex ] = '.';
                    fillQueue.Enqueue( newCellPosition );
                }

                // 7
                if ( cellPosition.rowIndex + 1 < image.Length && image[ cellPosition.rowIndex + 1 ][ cellPosition.columnIndex ] == ' ' )
                {
                    CellPosition newCellPosition = new CellPosition();
                    newCellPosition.rowIndex = cellPosition.rowIndex + 1;
                    newCellPosition.columnIndex = cellPosition.columnIndex;
                    image[ newCellPosition.rowIndex ][ newCellPosition.columnIndex ] = '.';
                    fillQueue.Enqueue( newCellPosition );
                }

                // 8
                if ( cellPosition.rowIndex + 1 < image.Length && cellPosition.columnIndex + 1 < image[ cellPosition.rowIndex + 1 ].Length && image[ cellPosition.rowIndex + 1 ][ cellPosition.columnIndex + 1 ] == ' ' )
                {
                    CellPosition newCellPosition = new CellPosition();
                    newCellPosition.rowIndex = cellPosition.rowIndex + 1;
                    newCellPosition.columnIndex = cellPosition.columnIndex + 1;
                    image[ newCellPosition.rowIndex ][ newCellPosition.columnIndex ] = '.';
                    fillQueue.Enqueue( newCellPosition );
                }
            }
        }

        private static void FillImage( ref char[][] image )
        {
            CellPosition lastStartCellPosition = new CellPosition();
            lastStartCellPosition.rowIndex = -1;
            lastStartCellPosition.columnIndex = -1;
            CellPosition startCellPosition = FindStartCell( ref image, lastStartCellPosition );

            while ( startCellPosition.rowIndex != -1 && startCellPosition.columnIndex != -1 )
            {
                FillAroundCell( ref image, startCellPosition );
                lastStartCellPosition = startCellPosition;
                startCellPosition = FindStartCell( ref image, lastStartCellPosition );
            }
        }

        private static void PrintImage( char[][] image, string outputFilePath )
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

        static int Main( string[] args )
        {
            Args? parsedArgs = ParseArgs( args );

            if ( parsedArgs == null )
            {
                return 1;
            }

            string inputFilePath = parsedArgs.Value.inputFilePath;
            string outputFilePath = parsedArgs.Value.outputFilePath;

            char[][] image = GetImageFromFile( inputFilePath );

            FillImage( ref image );

            PrintImage( image, outputFilePath );

            return 0;
        }
    }
}
