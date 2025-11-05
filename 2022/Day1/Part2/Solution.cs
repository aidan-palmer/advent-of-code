using System;
using System.IO;
using System.Collections.Generic;

class Solution
{
    public static void Main(string[] args)
    {
        if (args.Length < 1)
        {
            throw new ArgumentException("Error: provide a text file as an argument.");
        }
        String line;
        int sum = 0;
        List<int> sums = new List<int>();
        try
        {
            StreamReader sr = new StreamReader(args[0]);
            line = sr.ReadLine();
            while (line != null)
            {
                if (line.Length == 0)
                {
                    sums.Add(sum);
                    sum = 0;
                }
                else
                {
                    sum += int.Parse(line);
                }
                line = sr.ReadLine();
            }
            sums.Add(sum);
        }
        catch (Exception e)
        {
            throw new Exception(e.Message);
        }
        sums.Sort();
        int total = 0;
        int n = sums.Count;
        for (int i = n - 1; i >= n - 3; i--)
        {
            total += sums[i];
        }
        Console.WriteLine(total);
    }
}