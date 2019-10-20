using System;
using System.Collections.Generic;

namespace ConsoleApp1
{
    class Program
    {
        //Given a list of folders, remove all sub-folders in those folders and return in any order the folders after removing.
        //If a folder[i] is located within another folder[j], it is called a sub-folder of it.
        //The format of a path is one or more concatenated strings of the form: / followed by one 
        //or more lowercase English letters. For example, /leetcode and /leetcode/problems are 
        //valid paths while an empty string and / are not.
        //Input: folder = ["/a","/a/b","/c/d","/c/d/e","/c/f"]
        //Output: ["/a","/c/d","/c/f"]
        //Explanation: Folders "/a/b/" is a subfolder of "/a" and "/c/d/e" is inside of folder "/c/d" in our filesystem.
        //Input: folder = ["/a", "/a/b/c", "/a/b/d"]
        //Output: ["/a"]
        //Explanation: Folders "/a/b/c" and "/a/b/d/" will be removed because they are subfolders of "/a".
        public IList<string> RemoveSubfolders(string[] folder)
        {
            List<string> result = new List<string>();
            Array.Sort(folder, (item1,item2) => item1.Length-item2.Length);
            foreach(string dir in folder)
            {
                if(result.Count==0)
                {
                    result.Add(dir);
                }
                else
                {
                    bool ok = true;
                    foreach (string r in result)
                    {
                        if(dir.StartsWith(r+"/"))
                        {
                            ok = false;
                            break;
                        }
                    }
                    if(ok)
                    {
                        result.Add(dir);
                    }
                }
            }
            return result;
        }
        static void Main(string[] args)
        {
            //CheckStraightLine();
            Console.WriteLine("Hello World!");
        }
    }
}
