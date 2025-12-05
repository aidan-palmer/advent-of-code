using System;
using System.IO;
using System.Collections.Generic;

class Program
{
    static List<Tuple<long, long>> ranges;

    static bool IsFresh(long id)
    {
        foreach (Tuple<long, long> t in ranges)
        {
            if (id >= t.Item1 && id <= t.Item2)
            {
                return true;
            }
        }
        return false;
    }

    public static void Main(string[] args)
    {
        if (args.Length < 1)
        {
            throw new ArgumentException("Error: provide a text file as an argument.");
        }
        string line;
        bool first = true;
        ranges = new List<Tuple<long, long>>();
        List<long> ids = new List<long>();
        try
        {
            StreamReader sr = new StreamReader(args[0]);
            line = sr.ReadLine();
            while (line != null)
            {
                if (line.Length == 0)
                {
                    first = false;
                } else
                {
                    if (first)
                    {
                        int dash = line.IndexOf('-');
                        long x = long.Parse(line.Substring(0, dash));
                        long y = long.Parse(line.Substring(dash + 1));
                        Tuple<long, long> t = new Tuple<long, long>(x, y);
                        ranges.Add(t);
                    } else
                    {
                        ids.Add(long.Parse(line));
                    }
                }
                line = sr.ReadLine();
            }
        }
        catch (Exception e)
        {
            throw new Exception(e.Message);
        }
        long total = 0;
        foreach (long i in ids)
        {
            if (IsFresh(i))
            {
                total++;
            }
        }
        Console.WriteLine(total);
    }
}