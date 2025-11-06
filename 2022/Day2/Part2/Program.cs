using System;
using System.IO;
using System.Collections.Generic;

class Program
{
    static int Score(char x, char y)
    {
        if (x == 'A')
        {
            if (y == 'X')
            {
                return 3;
            } else if (y == 'Y')
            {
                return 4;
            } else
            {
                return 8;
            }
        } else if (x == 'B')
        {
            if (y == 'X')
            {
                return 1;
            } else if (y == 'Y')
            {
                return 5;
            } else
            {
                return 9;
            }
        } else
        { // C
            if (y == 'X')
            {
                return 2;
            } else if (y == 'Y')
            {
                return 6;
            } else
            {
                return 7;
            }
        }
    }

    public static void Main(string[] args)
    {
        if (args.Length < 1)
        {
            throw new ArgumentException("Error: provide a text file as an argument.");
        }
        string line;
        int total = 0;
        try
        {
            StreamReader sr = new StreamReader(args[0]);
            line = sr.ReadLine();
            while (line != null)
            {
                total += Score(line[0], line[2]);
                line = sr.ReadLine();
            }
        }
        catch (Exception e)
        {
            throw new Exception(e.Message);
        }
        Console.WriteLine(total);
    }
}