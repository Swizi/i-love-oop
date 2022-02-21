using System;
using System.Collections.Generic;

namespace Radix
{
    internal class Program
    {
        const int MIN_RADIX = 2;
        const int MAX_RADIX = 36;
        const int MAX_INT_DIGIT = 9;
        const int ZERO_ASCII_CODE = 48;

        const string englishAlphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

        struct Args
        {
            public string sourceNotation;
            public string destinationNotation;
            public string value;
        }

        private static Args? ParseArgs( string[] stringArgs )
        {
            Args args = new Args();

            if ( stringArgs.Length != 3 )
            {
                Console.WriteLine( "Incorret arguments count. Params should be: <source notation> <destination notation> <value>" );
                return null;
            }

            args.sourceNotation = stringArgs[ 0 ];
            args.destinationNotation = stringArgs[ 1 ];
            args.value = stringArgs[ 2 ];

            return args;
        }

        private static int StringToInt( string str, int radix, ref bool wasError )
        {
            wasError = false;

            const int startAlphabetChar = 'A';
            string uppercaseStr = str.ToUpper();
            bool isNegative = false;
            int currNum = 0;

            for ( int i = 0; i < uppercaseStr.Length; i++ )
            {
                int chNum = uppercaseStr[ i ];
                int currDigitNum = 0;

                if ( i == 0 && ( uppercaseStr[ i ] == '-' ) )
                {
                    isNegative = true;
                }

                if ( i == 0 && ( uppercaseStr[ i ] == '+' ) || ( uppercaseStr[ i ] == '-' ) )
                {
                    continue;
                }

                if ( !char.IsDigit( uppercaseStr[ i ] ) )
                {
                    currDigitNum = MAX_INT_DIGIT + 1 + chNum - startAlphabetChar;
                }
                else
                {
                    currDigitNum = chNum - ZERO_ASCII_CODE;
                }

                if ( radix <= currDigitNum )
                {
                    wasError = true;
                    return -1;
                }

                if ( currNum >= ( int.MaxValue - currDigitNum ) / radix )
                {
                    wasError = true;
                    return -1;
                }

                currNum = ( currNum * radix ) + currDigitNum;
            }

            if ( isNegative )
            {
                currNum *= -1;
            }

            return currNum;
        }

        static private string IntToString( int num, int radix, ref bool wasError )
        {
            if ( radix < MIN_RADIX || radix > MAX_RADIX )
            {
                wasError = true;
                return "-1";
            }
            List<char> stringChars = new List<char>();
            int unsignedNum = Math.Abs( num );
            wasError = false;

            do
            {
                int chNum = unsignedNum % radix;
                char ch = '0';

                if ( chNum <= MAX_INT_DIGIT )
                {
                    ch = (char)( chNum + ZERO_ASCII_CODE );
                }
                else
                {
                    ch = englishAlphabet[ chNum - MAX_INT_DIGIT - 1 ];
                }

                stringChars.Add( ch );
                unsignedNum /= radix;
            } while ( unsignedNum != 0 );

            if ( num < 0 )
            {
                stringChars.Add( '-' );
            }

            stringChars.Reverse();

            return new string( stringChars.ToArray() );
        }

        static int Main( string[] args )
        {
            Args? parsedArgs = ParseArgs( args );
            if ( parsedArgs == null )
            {
                return 1;
            }
            string sourceNotationString = parsedArgs.Value.sourceNotation;
            string destinationNotationString = parsedArgs.Value.destinationNotation;
            string value = parsedArgs.Value.value;

            try
            {
                int test = Convert.ToInt32( sourceNotationString );
            }
            catch ( OverflowException )
            {
                Console.WriteLine( "Source notation is too large" );
                return 1;
            }
            try
            {
                int test = Convert.ToInt32( destinationNotationString );
            }
            catch ( OverflowException )
            {
                Console.WriteLine( "Destination notation is too large" );
                return 1;
            }
            int sourceNotation = Convert.ToInt32( sourceNotationString );
            int destinationNotation = Convert.ToInt32( destinationNotationString );
            bool wasError = false;

            int convertedValue = StringToInt( value, sourceNotation, ref wasError );
            if ( wasError )
            {
                Console.WriteLine( "Can`t convert source value" );
                return 1;
            }

            string str = IntToString( convertedValue, destinationNotation, ref wasError );
            if ( wasError )
            {
                Console.WriteLine( "Incorrect destination notation" );
                return 1;
            }

            Console.WriteLine( str );
            return 0;
        }
    }
}
