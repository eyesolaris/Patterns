using System;
using System.Collections.Generic;

namespace Composer
{
    public interface IThing
    {
        uint Weight { get; }
    }

    public sealed class Phone : IThing
    {
        public Phone(uint weight)
        {
            Weight = weight;
        }

        public uint Weight { get; private set; }
    }

    public sealed class Box : IThing
    {
        public Box(uint weight)
        {
            selfWeight = weight;
        }

        public void Add(IThing thing)
        {
            innerThings.Add(thing);
        }

        public void Remove(IThing thing)
        {
            innerThings.Remove(thing);
        }



        private List<IThing> innerThings = new List<IThing>();

        private uint selfWeight;

        public uint Weight
        {
            get
            {
                uint weight = selfWeight;
                innerThings.ForEach(thing => weight += thing.Weight);
                return weight;
            }
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Box box = new Box(100);
            box.Add(new Phone(400));
            Box otherBox = new Box(50);
            otherBox.Add(new Phone(500));
            otherBox.Add(new Phone(600));
            otherBox.Add(new Box(10));
            box.Add(otherBox);
            uint weight = box.Weight;
            Console.WriteLine("Вес коробки: {0}", weight);
        }
    }
}
