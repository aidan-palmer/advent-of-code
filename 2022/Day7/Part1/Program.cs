using System;
using System.IO;
using System.Collections.Generic;
using System.Text.RegularExpressions;

class Program
{
    class Node
    {
        public string dir;
        public List<int> files;
        public List<Node> children;
        public Node(string s)
        {
            dir = s;
            files = new List<int>();
            children = new List<Node>();
        }
        public void Clear()
        {
            dir = "";
            files.Clear();
            children.Clear();
        }
    }

    static void AddNode(Node root, Node n, string parent)
    {
        if (root.dir == parent)
        {
            root.children.Add(n);
            return;
        }
        foreach (Node child in root.children)
        {
            AddNode(child, n, parent);
        }
    }

    static void PrintNodes(Node root)
    {
        Console.WriteLine(root.dir);
        foreach (int i in root.files)
        {
            Console.WriteLine(i);
        }
        foreach (Node child in root.children)
        {
            PrintNodes(child);
        }
    }

    static bool IsCmd(string s)
    {
        return s[0] == '$';
    }

    static int ParseSize(string s)
    {
        MatchCollection matches = Regex.Matches(s, @"\d+");
        foreach (Match m in matches)
        {
            return int.Parse(m.Value);
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
        Stack<string> currDir = new Stack<string>();
        Stack<string> prevDir = new Stack<string>();
        Node root = new Node("/");
        currDir.Push("/");
        try
        {
            StreamReader sr = new StreamReader(args[0]);
            line = sr.ReadLine();
            Node node = new Node("/");
            while (line != null)
            {
                if (IsCmd(line))
                {
                    string cmd = line.Substring(2, 2);
                    if (cmd == "cd")
                    {
                        string dir = line.Substring(5);
                        if (dir == "..")
                        {
                            prevDir.Pop();
                            currDir.Pop();
                        }
                        else
                        {
                            prevDir.Push(currDir.Peek());
                            currDir.Push(dir);
                        }
                    }
                    else
                    {
                        AddNode(root, node, prevDir.Peek());
                        node.Clear();
                        node = new Node(currDir.Peek());
                    }
                }
                else
                {
                    if (line.Substring(0, 3) != "dir")
                    {
                        int size = ParseSize(line);
                        node.files.Add(size);
                    }
                }
                line = sr.ReadLine();
            }
            if (node.files.Count > 0)
            {
                AddNode(root, node, prevDir.Peek());
            }
        }
        catch (Exception e)
        {
            throw new Exception(e.Message);
        }
        PrintNodes(root);
    }
}