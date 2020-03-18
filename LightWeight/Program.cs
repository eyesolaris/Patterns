using System;

namespace LightWeight
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            var treeTypeFactory = new TreeTypeFactory();
            var forest = new Forest(treeTypeFactory);

            forest.Grow(new Point(1, 1), "bereza");
            forest.Grow(new Point(4, 6), "bereza");

            forest.Plant(new Point(4, 2), new Tree(new TreeType("dub", new Texture("dub")), 1, 2.5));

            Console.WriteLine(forest.ToString());
            Console.ReadLine();
        }
    }
}