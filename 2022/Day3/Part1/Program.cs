using System;
using System.IO;
using System.Collections.Generic;

class Program
{
    static char Common(string a, string b)
    {
        foreach (char c in a)
        {
            foreach (char d in b)
            {
                if (c == d)
                {
                    return c;
                }
            }
        }
        return '~';
    }

    static int Priority(char c)
    {
        if (c <= 'Z')
        {
            return c - 38;
        }
        return c - 96;
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
                string a = line.Substring(0, line.Length / 2);
                string b = line.Substring(line.Length / 2);
                char c = Common(a, b);
                total += Priority(c);
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