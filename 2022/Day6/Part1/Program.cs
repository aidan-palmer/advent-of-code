using System;
using System.IO;
using System.Collections.Generic;

class Program
{
    static bool Unique(string s)
    {
        for (int i = 0; i < s.Length - 1; i++)
        {
            for (int j = i + 1; j < s.Length; j++)
            {
                if (s[i] == s[j])
                {
                    return false;
                }
            }
        }
        return true;
    }

    static int Marker(string s)
    {
        for (int i = 0; i < s.Length - 3; i++)
        {
            string sub = s.Substring(i, 4);
            if (Unique(sub))
            {
                return i + 4;
            }
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
        int result = 0;
        try
        {
            StreamReader sr = new StreamReader(args[0]);
            line = sr.ReadLine();
            while (line != null)
            {
                result = Marker(line);
                line = sr.ReadLine();
            }
        }
        catch (Exception e)
        {
            throw new Exception(e.Message);
        }
        Console.WriteLine(result);
    }
}