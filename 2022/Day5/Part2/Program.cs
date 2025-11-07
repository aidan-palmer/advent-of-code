using System;
using System.IO;
using System.Collections.Generic;
using System.Text.RegularExpressions;
using System.Globalization;

class Program
{
    static int Size(string s)
    {
        List<int> nums = ParseMove(s);
        return nums[^1];
    }

    static List<int> ParseMove(string s)
    {
        MatchCollection matches = Regex.Matches(s, @"\d+");
        List<int> moves = new List<int>();
        foreach (Match m in matches)
        {
            moves.Add(int.Parse(m.Value));
        }
        return moves;
    }

    static bool IsCap(char c)
    {
        return c >= 'A' && c <= 'Z';
    }

    public static void Main(string[] args)
    {
        if (args.Length < 1)
        {
            throw new ArgumentException("Error: provide a text file as an argument.");
        }
        string line;
        List<string> lines = new List<string>();
        List<List<int>> moves = new List<List<int>>();
        try
        {
            StreamReader sr = new StreamReader(args[0]);
            line = sr.ReadLine();
            bool first = true;
            while (line != null)
            {
                if (line.Length == 0)
                {
                    first = false;
                }
                else if (first)
                {
                    lines.Add(line);
                }
                else
                {
                    moves.Add(ParseMove(line));
                }
                line = sr.ReadLine();
            }
        }
        catch (Exception e)
        {
            throw new Exception(e.Message);
        }
        int n = Size(lines[^1]);
        Stack<char>[] crates = new Stack<char>[n];
        for (int i = 0; i < n; i++)
        {
            crates[i] = new Stack<char>();
        }
        for (int i = lines.Count - 2; i >= 0; i--)
        {
            for (int j = 0; j < lines[i].Length; j++)
            {
                if (IsCap(lines[i][j]))
                {
                    int idx = lines[^1][j] - '0' - 1;
                    crates[idx].Push(lines[i][j]);
                }
            }
        }
        foreach (List<int> m in moves)
        {
            List<char> lc = new List<char>();
            for (int i = 0; i < m[0]; i++)
            {
                lc.Add(crates[m[1] - 1].Pop());
            }
            for (int j = lc.Count - 1; j >= 0; j--)
            {
                crates[m[2] - 1].Push(lc[j]);
            }
        }
        for (int i = 0; i < n; i++)
        {
            Console.Write(crates[i].Peek());
        }
        Console.WriteLine("");
    }
}