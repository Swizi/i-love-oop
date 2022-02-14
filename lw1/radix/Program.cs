using System;

namespace Radix
{
    internal class Program
    {
        const int MAX_10_BASE_DIGIT = 9;
        const int ZERO_ASCII_CODE = 48;

        struct Args
        {
            public string sourceNotation;
            public string destinationNotation;
            public string value;
        }

        private static Args? ParseArgs(string[] stringArgs )
        {
            Args args = new Args();

            if (stringArgs.Length != 3)
            {
                Console.WriteLine( "Incorret arguments count. Params should be: <source notation> <destination notation> <value>" );
                return null;
            }

            args.sourceNotation = stringArgs[ 0 ];
            args.destinationNotation = stringArgs[ 1 ];
            args.value = stringArgs[ 2 ];

            return args;
        }

        private static int StringToInt(ref string str, int radix, ref bool wasError)
        {
            wasError = false;

            int startAlphabetChar = 'A';
            bool isNegative = false;
            int currNum = 0;

            for (int i = 0; i < str.Length; i++)
            {
                int chNum = str[i];
                int currDigitNum = 0;

                if (i == 0 && (str[i] == '-'))
                {
                    isNegative = true;
                }

                if (i == 0 && (str[i] == '+') || (str[i] == '-'))
                {
                    continue;
                }

                if (!char.IsDigit(str[i]))
                {
                    currDigitNum = MAX_10_BASE_DIGIT + 1 + chNum - startAlphabetChar;
                }
                else
                {
                    Int32.TryParse(Convert.ToString(str[i]), out currDigitNum);
                }

                if (radix <= currDigitNum)
                {
                    wasError = true;
                }

                currNum += currDigitNum * Convert.ToInt32(Math.Pow(radix, str.Length - 1 - i));
            }

            if (isNegative)
            {
                currNum *= -1;
            }

            return currNum;
        }

        static private string IntToString(ref int num, int radix, ref bool wasError)
        {
            char[] englishAlphabet = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
            string str = "";
            int dividedNum = Math.Abs(num);
            int newChNum = 0;
            char newCh = '0';
            wasError = false;

            do
            {
                newChNum = dividedNum % radix;

                if (newChNum <= MAX_10_BASE_DIGIT)
                {
                    newCh = (char)(newChNum + ZERO_ASCII_CODE);
                }
                else
                {
                    newCh = englishAlphabet[newChNum - MAX_10_BASE_DIGIT - 1];
                }

                str += newCh;
                dividedNum /= radix;
            } while (dividedNum != 0);

            if (num < 0)
            {
                str += '-';
            }

            char[] charArr = str.ToCharArray();
            Array.Reverse(charArr);

            return new string(charArr);
        }

        static int Main(string[] args)
        {
            Args? parsedArgs = ParseArgs( args );
            if (parsedArgs == null)
            {
                return 1;
            }
            string sourceNotationString = parsedArgs.Value.sourceNotation;
            string destinationNotationString = parsedArgs.Value.destinationNotation;
            int sourceNotation = Convert.ToInt32(sourceNotationString);
            int destinationNotation = Convert.ToInt32(destinationNotationString);
            string value = parsedArgs.Value.value;
            bool wasError = false;

            int convertedValue = StringToInt(ref value, sourceNotation, ref wasError);
            if (wasError)
            {
                Console.WriteLine("Incorrect source notation");
                return 1;
            }

            string str = IntToString(ref convertedValue, destinationNotation, ref wasError);

            Console.WriteLine(str);
            return 0;
        }
    }
}
