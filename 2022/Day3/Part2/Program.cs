using System;
using System.IO;
using System.Collections.Generic;

class Program
{
    static char Common(string a, string b, string c)
    {
        foreach (char x in a)
        {
            foreach (char y in b)
            {
                foreach (char z in c)
                {
                    if (x == y && y == z)
                    {
                        return x;
                    }
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
        List<string> bags = new List<string>();
        try
        {
            StreamReader sr = new StreamReader(args[0]);
            line = sr.ReadLine();
            while (line != null)
            {
                bags.Add(line);
                line = sr.ReadLine();
            }
        }
        catch (Exception e)
        {
            throw new Exception(e.Message);
        }
        for (int i = 0; i < bags.Count - 2; i += 3)
        {
            char c = Common(bags[i], bags[i + 1], bags[i + 2]);
            total += Priority(c);
        }
        Console.WriteLine(total);
    }
}