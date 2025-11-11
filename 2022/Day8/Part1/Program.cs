using System;
using System.IO;
using System.Collections.Generic;

class Program
{
    static bool Visible(List<List<int>> grid, int x, int y)
    {
        int z = grid[x][y];
        bool vis = true;
        // Up
        for (int i = x - 1; i >= 0; i--)
        {
            if (grid[i][y] >= z)
            {
                vis = false;
                break;
            }
        }
        if (vis) return true;
        vis = true;
        // Down
        for (int i = x + 1; i < grid.Count; i++)
        {
            if (grid[i][y] >= z)
            {
                vis = false;
                break;
            }
        }
        if (vis) return true;
        vis = true;
        // Left
        for (int j = y - 1; j >= 0; j--)
        {
            if (grid[x][j] >= z)
            {
                vis = false;
                break;
            }
        }
        if (vis) return true;
        vis = true;
        // Right
        for (int j = y + 1; j < grid[x].Count; j++)
        {
            if (grid[x][j] >= z)
            {
                vis = false;
                break;
            }
        }
        return vis;
    }
    
    public static void Main(string[] args)
    {
        if (args.Length < 1)
        {
            throw new ArgumentException("Error: provide a text file as an argument.");
        }
        string line;
        List<List<int>> grid = new List<List<int>>();
        try
        {
            StreamReader sr = new StreamReader(args[0]);
            line = sr.ReadLine();
            while (line != null)
            {
                List<int> nums = new List<int>();
                foreach (char c in line)
                {
                    nums.Add(c - '0');
                }
                grid.Add(nums);
                line = sr.ReadLine();
            }
        }
        catch (Exception e)
        {
            throw new Exception(e.Message);
        }
        int total = grid.Count * 2 + ((grid[0].Count - 2) * 2);
        for (int i = 1; i < grid.Count - 1; i++)
        {
            for (int j = 1; j < grid[i].Count - 1; j++)
            {
                if (Visible(grid, i, j))
                {
                    total++;
                }
            }
        }
        Console.WriteLine(total);
    }
}