﻿using System;
using System.IO;

namespace Invert
{
    internal class Program
    {
        const int MATRIX_DIMENSION = 3;

        struct Args
        {
            public double[][] matrix;
        }

        private static Args? ParseArgs( string[] stringArgs )
        {
            Args args = new Args();

            if ( stringArgs.Length != 1 )
            {
                Console.WriteLine( "Incorret arguments count. Params should be: <matrix file>" );
                return null;
            }

            // Переделать на List?
            args.matrix = new double[][] { new double[] { -1, -1, -1 }, new double[] { -1, -1, -1 }, new double[] { -1, -1, -1 } };

            string matrixFilePath = stringArgs[ 0 ];

            if ( !File.Exists( matrixFilePath ) )
            {
                Console.WriteLine( "Input file is not exists" );
                return null;
            }

            using ( StreamReader inputStream = new StreamReader( matrixFilePath ) )
            {
                string line = "";
                int linesCount = 0;

                while ( ( line = inputStream.ReadLine() ) != null )
                {
                    linesCount++;
                    if ( linesCount > MATRIX_DIMENSION )
                    {
                        Console.WriteLine( "Incorrect matrix vertical dimension. Matrix should be 3x3" );
                        return null;
                    }
                    string[] lineValues = line.Split( ' ' );
                    if ( lineValues.Length != MATRIX_DIMENSION )
                    {
                        Console.WriteLine( "Incorrect matrix horizontal dimension at " + linesCount + " line. Matrix should be 3x3" );
                        return null;
                    }

                    for ( int columnIndex = 0; columnIndex < 3; columnIndex++ )
                    {
                        bool correct = double.TryParse( lineValues[ columnIndex ], out args.matrix[ linesCount - 1 ][ columnIndex ] );
                        if ( !correct )
                        {
                            Console.WriteLine( "Incorrect matrix value at x=" + ( linesCount - 1 ) + " y=" + columnIndex + ". Matrix value should be number" );
                            return null;
                        }
                    }
                }
            }

            return args;
        }

        private static double GetMatrixDetermination( double[][] matrix, double dimension )
        {
            double det = 0;
            if ( dimension == 2 )
            {
                det = matrix[ 0 ][ 0 ] * matrix[ 1 ][ 1 ] - matrix[ 0 ][ 1 ] * matrix[ 1 ][ 0 ];
            }
            if ( dimension == 3 )
            {
                double[][] firstMatrix = new double[][] { new double[] { matrix[ 1 ][ 1 ], matrix[ 1 ][ 2 ] }, new double[] { matrix[ 2 ][ 1 ], matrix[ 2 ][ 2 ] } };
                double[][] secondMatrix = new double[][] { new double[] { matrix[ 1 ][ 0 ], matrix[ 1 ][ 2 ] }, new double[] { matrix[ 2 ][ 0 ], matrix[ 2 ][ 2 ] } };
                double[][] thirdMatrix = new double[][] { new double[] { matrix[ 1 ][ 0 ], matrix[ 1 ][ 1 ] }, new double[] { matrix[ 2 ][ 0 ], matrix[ 2 ][ 1 ] } };

                det = matrix[ 0 ][ 0 ] * GetMatrixDetermination( firstMatrix, 2 ) - matrix[ 0 ][ 1 ] * GetMatrixDetermination( secondMatrix, 2 ) + matrix[ 0 ][ 2 ] * GetMatrixDetermination( thirdMatrix, 2 );
            }

            return det;
        }

        private static double[][] GetMatrix3x3Minor( double[][] matrix )
        {
            // Добавить в параметры dimension
            // Добавить функцию, которая получает nMatrix
            double[][] firstMatrix = new double[][] { new double[] { matrix[ 1 ][ 1 ], matrix[ 1 ][ 2 ] }, new double[] { matrix[ 2 ][ 1 ], matrix[ 2 ][ 2 ] } };
            double[][] secondMatrix = new double[][] { new double[] { matrix[ 1 ][ 0 ], matrix[ 1 ][ 2 ] }, new double[] { matrix[ 2 ][ 0 ], matrix[ 2 ][ 2 ] } };
            double[][] thirdMatrix = new double[][] { new double[] { matrix[ 1 ][ 0 ], matrix[ 1 ][ 1 ] }, new double[] { matrix[ 2 ][ 0 ], matrix[ 2 ][ 1 ] } };
            double[][] fourthMatrix = new double[][] { new double[] { matrix[ 0 ][ 1 ], matrix[ 0 ][ 2 ] }, new double[] { matrix[ 2 ][ 1 ], matrix[ 2 ][ 2 ] } };
            double[][] fifthMatrix = new double[][] { new double[] { matrix[ 0 ][ 0 ], matrix[ 0 ][ 2 ] }, new double[] { matrix[ 2 ][ 0 ], matrix[ 2 ][ 2 ] } };
            double[][] sixthMatrix = new double[][] { new double[] { matrix[ 0 ][ 0 ], matrix[ 0 ][ 1 ] }, new double[] { matrix[ 2 ][ 0 ], matrix[ 2 ][ 1 ] } };
            double[][] seventhMatrix = new double[][] { new double[] { matrix[ 0 ][ 1 ], matrix[ 0 ][ 2 ] }, new double[] { matrix[ 1 ][ 1 ], matrix[ 1 ][ 2 ] } };
            double[][] eightsMatrix = new double[][] { new double[] { matrix[ 0 ][ 0 ], matrix[ 0 ][ 2 ] }, new double[] { matrix[ 1 ][ 0 ], matrix[ 1 ][ 2 ] } };
            double[][] ninthMatrix = new double[][] { new double[] { matrix[ 0 ][ 0 ], matrix[ 0 ][ 1 ] }, new double[] { matrix[ 1 ][ 0 ], matrix[ 1 ][ 1 ] } };

            double firstMatrixDet = GetMatrixDetermination( firstMatrix, 2 );
            double secondMatrixDet = GetMatrixDetermination( secondMatrix, 2 );
            double thirdMatrixDet = GetMatrixDetermination( thirdMatrix, 2 );
            double fourthMatrixDet = GetMatrixDetermination( fourthMatrix, 2 );
            double fifthMatrixDet = GetMatrixDetermination( fifthMatrix, 2 );
            double sixthMatrixDet = GetMatrixDetermination( sixthMatrix, 2 );
            double seventhMatrixDet = GetMatrixDetermination( seventhMatrix, 2 );
            double eightsMatrixDet = GetMatrixDetermination( eightsMatrix, 2 );
            double ninthMatrixDet = GetMatrixDetermination( ninthMatrix, 2 );

            return new double[][] { new double[] { firstMatrixDet, secondMatrixDet, thirdMatrixDet },
                new double[] { fourthMatrixDet, fifthMatrixDet, sixthMatrixDet },
                new double[] { seventhMatrixDet, eightsMatrixDet, ninthMatrixDet } 
            };
        }

        private static double[][] GetMatrix3x3Cofactor( double[][] matrix )
        {
            matrix[ 0 ][ 1 ] *= -1;
            matrix[ 1 ][ 0 ] *= -1;
            matrix[ 1 ][ 2 ] *= -1;
            matrix[ 2 ][ 1 ] *= -1;
            return matrix;
        }

        private static double[][] GetTransposedMatrix( double[][] matrix )
        {
            double[][] transposedMatrix = { new double[] { -1, -1, -1 }, new double[] { -1, -1, -1 }, new double[] { -1, -1, -1 } };

            for ( int rowIndex = 0; rowIndex < 3; rowIndex++ )
            {
                for ( int columnIndex = 0; columnIndex < 3; columnIndex++ )
                {
                    transposedMatrix[ columnIndex ][ rowIndex ] = matrix[ rowIndex ][ columnIndex ];
                    // Это тоже transposedMatrix[ columnIndex ][ rowIndex ] = matrix[ rowIndex ][ columnIndex ];
                }
            }

            return transposedMatrix;
        }

        private static double[][] MultiplyMatrix( double[][] matrix, double multiplier )
        {
            for ( int rowIndex = 0; rowIndex < 3; rowIndex++ )
            {
                for ( int columnIndex = 0; columnIndex < 3; columnIndex++ )
                {
                    matrix[ rowIndex ][ columnIndex ] *= multiplier;
                }
            }

            return matrix;
        }

        private static double[][] GetInversedMatrix( double[][] matrix, ref bool wasError )
        {
            double det = GetMatrixDetermination( matrix, 3 );
            if ( det == 0 )
            {
                wasError = true;
                return null;
            }
            double[][] transposedMatrix = GetTransposedMatrix( GetMatrix3x3Cofactor( GetMatrix3x3Minor( matrix ) ) );

            return MultiplyMatrix( transposedMatrix, 1 / det );
        }

        private static void PrintMatrix( double[][] matrix )
        {
            // Передавать по константной ссылке
            for ( int rowIndex = 0; rowIndex < 3; rowIndex++ )
            {
                for ( int columnIndex = 0; columnIndex < 3; columnIndex++ )
                {
                    Console.Write( "{0:F3}", matrix[ rowIndex ][ columnIndex ] );
                    if ( columnIndex < 2 )
                    {
                        Console.Write( " " );
                    }
                }
                Console.WriteLine();
            }
        }

        static int Main( string[] args )
        {
            Args? parsedArgs = ParseArgs( args );

            if ( parsedArgs == null )
            {
                return 1;
            }

            bool wasError = false;
            double[][] inversedMatrix = GetInversedMatrix( parsedArgs.Value.matrix, ref wasError );

            if ( wasError )
            {
                Console.WriteLine( "Can`t calculate inversed matrix for input matrix" );
                return 1;
            }

            PrintMatrix( inversedMatrix );

            return 0;
        }
    }
}
