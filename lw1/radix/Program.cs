using System;

namespace radix
{
    internal class Program
    {
        const int MAX_10_BASE_DIGIT = 9;
        const int ZERO_ASCII_CODE = 48;

        static private int StringToInt(ref string str, int radix, ref bool wasError)
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
                    newCh = englishAlphabet[newChNum - MAX_10_BASE_DIGIT + 1];
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
            if (args.Length != 3)
            {
                Console.WriteLine("Incorret arguments count. Params should be: <source notation> <destination notation> <value>");
                return 1;
            }

            string source_notation_string = args[0];
            string destination_notation_string = args[1];
            int source_notation = Convert.ToInt32(source_notation_string);
            int destination_notation = Convert.ToInt32(destination_notation_string);
            string value = args[2];
            bool wasError = false;

            int convertedValue = StringToInt(ref value, source_notation, ref wasError);
            if (wasError)
            {
                Console.WriteLine("Incorrect source notation");
                return 1;
            }

            string str = IntToString(ref convertedValue, destination_notation, ref wasError);

            Console.WriteLine(str);
            return 0;
        }
    }
}
