using System;
using System.IO;
using System.Collections.Generic;

class Program
{
    static bool FullyContains(int a, int b, int c, int d)
    {
        return (c >= a && d <= b) || (a >= c && b <= d);
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
                string[] pair = line.Split(',');
                string[] a = pair[0].Split('-');
                string[] b = pair[1].Split('-');
                int w = int.Parse(a[0]);
                int x = int.Parse(a[1]);
                int y = int.Parse(b[0]);
                int z = int.Parse(b[1]);
                if (FullyContains(w, x, y, z))
                {
                    total++;
                }
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