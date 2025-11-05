using System;
using System.IO;

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
                return 6;
            } else
            {
                return 0;
            }
        } else if (x == 'B')
        {
            if (y == 'X')
            {
                return 0;
            } else if (y == 'Y')
            {
                return 3;
            } else
            {
                return 6;
            }
        } else
        {
            if (y == 'X')
            {
                return 6;
            } else if (y == 'Y')
            {
                return 0;
            } else
            {
                return 3;
            }
        }
    }
    
    static int ShapeScore(char x)
    {
        switch (x)
        {
            case 'X':
                return 1;
            case 'Y':
                return 2;
            case 'Z':
                return 3;
        }
        return -1;
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
                total += ShapeScore(line[2]);
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