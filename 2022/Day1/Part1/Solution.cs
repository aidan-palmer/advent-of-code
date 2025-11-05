using System;
using System.IO;
//using System.Exception;

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
        int max = -1;
        try
        {
            StreamReader sr = new StreamReader(args[0]);
            line = sr.ReadLine();
            while (line != null)
            {
                if (line.Length == 0)
                {
                    if (sum > max)
                    {
                        max = sum;
                    }
                    sum = 0;
                }
                else
                {
                    sum += int.Parse(line);
                }
                line = sr.ReadLine();
            }
        }
        catch (Exception e)
        {
            throw new Exception(e.Message);
        }
        Console.WriteLine(max);
    }
}