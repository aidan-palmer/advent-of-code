using System;
using System.IO;
using System.Collections.Generic;

class Program
{
    static List<Tuple<long, long>> ranges;

    static void MergeRanges()
    {
        for (int i = 0; i < ranges.Count - 1; i++)
        {
            for (int j = i + 1; j < ranges.Count; j++)
            {
                if (ranges[j].Item1 <= ranges[i].Item2)
                {
                    if (ranges[j].Item2 > ranges[i].Item2)
                    {
                        Tuple<long, long> t = new Tuple<long, long>(ranges[i].Item1, ranges[j].Item2);
                        ranges[i] = t;
                    }
                    ranges.RemoveAt(j);
                    j--;
                }
            }
        }
    }

    static long CountFresh()
    {
        long total = 0;
        foreach (Tuple<long, long> t in ranges)
        {
            total += t.Item2 - t.Item1 + 1;
        }
        return total;
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
                        break;
                    }
                }
                line = sr.ReadLine();
            }
        }
        catch (Exception e)
        {
            throw new Exception(e.Message);
        }
        ranges.Sort((t1, t2) => t1.Item1.CompareTo(t2.Item1));
        MergeRanges();
        Console.WriteLine(CountFresh());
    }
}