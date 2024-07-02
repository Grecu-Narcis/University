using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

using Lab_2;

namespace Lab_2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            List<int> ints = new List<int> { 5, 2, 8, 1, 9 };

            SortingModule<int>.Sort(ints, "merge", true);

            foreach(int i in ints)
                Console.WriteLine(i);           
        }
    }
}
