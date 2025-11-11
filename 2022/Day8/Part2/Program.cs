using System;
using System.IO;
using System.Collections.Generic;

class Program
{
    static int ScenicScore(List<List<int>> grid, int x, int y)
    {
        int z = grid[x][y];
        int up = 0;
        // Up
        for (int i = x - 1; i >= 0; i--)
        {
            if (grid[i][y] < z)
            {
                up++;
            } else
            {
                up++;
                break;
            }
        }
        int down = 0;
        // Down
        for (int i = x + 1; i < grid.Count; i++)
        {
            if (grid[i][y] < z)
            {
                down++;
            } else
            {
                down++;
                break;
            }
        }
        int left = 0;
        // Left
        for (int j = y - 1; j >= 0; j--)
        {
            if (grid[x][j] < z)
            {
                left++;
            }
            else
            {
                left++;
                break;
            }
        }
        int right = 0;
        // Right
        for (int j = y + 1; j < grid[x].Count; j++)
        {
            if (grid[x][j] < z)
            {
                right++;
            } else
            {
                right++;
                break;
            }
        }
        return up * down * left * right;
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
        int max = -1;
        for (int i = 1; i < grid.Count - 1; i++)
        {
            for (int j = 1; j < grid[i].Count - 1; j++)
            {
                int ss = ScenicScore(grid, i, j);
                if (ss > max)
                {
                    max = ss;
                }
            }
        }
        Console.WriteLine(max);
    }
}