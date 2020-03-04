using System;
using System.Collections.Generic;
using System.Text;

namespace Builder
{
    public interface ICakeBuilder
    {
        void AddPastry(string layerName);
        void AddCream(string creamName);
        void AddBeauty(string beautyName);
        void SetName(string name);

        Cake Cake { get; }
    }

    public class SimpleCakeBuilder : ICakeBuilder
    {
        public SimpleCakeBuilder()
        {
            Cake = new Cake();
        }

        public void AddCream(string creamName)
        {
            Cake.AddLayer(new CreamLayer(creamName));
        }

        public void AddBeauty(string beautyName)
        {
            Cake.AddLayer(new BeautyLayer(beautyName));
        }

        public void AddPastry(string layerName)
        {
            Cake.AddLayer(new OrdinaryPastry(layerName));
        }

        public void SetName(string name)
        {
            Cake.Name = name;
        }

        public Cake Cake { get; }
    }

    public sealed class FruitCakeBuilder : ICakeBuilder
    {
        public FruitCakeBuilder()
        {
            Cake = new Cake();
        }

        public Cake Cake { get; }

        public void AddCream(string creamName)
        {
            Cake.AddLayer(new CreamLayer(creamName));
        }

        public void AddBeauty(string beautyName)
        {
            Cake.AddLayer(new BeautyLayer(beautyName));
        }

        public void AddPastry(string layerName)
        {
            Cake.AddLayer(new FruitPastry(layerName, "груша"));
        }

        public void SetName(string name)
        {
            Cake.Name = name;
        }
    }

    public abstract class Layer
    {
        protected Layer(string name)
        {
            Name = name;
        }

        public string Name { get; private set; }
    }

    public sealed class OrdinaryPastry : Layer
    {
        public OrdinaryPastry(string name)
            : base(name)
        {
        }

        public override string ToString()
        {
            return $"тесто { Name }";
        }
    }

    public sealed class FruitPastry : Layer
    {
        public FruitPastry(string name, string fruitName)
            : base(name)
        {
            FruitName = fruitName;
        }

        public string FruitName { get; private set; }

        public override string ToString()
        {
            return $"тесто { Name } с фруктом \"{ FruitName }\"";
        }
    }

    public sealed class CreamLayer : Layer
    {
        public CreamLayer(string name)
            : base(name)
        {
        }

        public override string ToString()
        {
            return "слой крема " + Name;
        }
    }

    public sealed class BeautyLayer : Layer
    {
        public BeautyLayer(string name)
            : base(name)
        {
        }

        public override string ToString()
        {
            return "украшение " + Name;
        }
    }

    public class ChocolateDirector
    {
        private ICakeBuilder builder;

        public ChocolateDirector(ICakeBuilder builder)
        {
            this.builder = builder;
        }

        public Cake Build()
        {
            builder.SetName("Шоколадный принц");
            builder.AddPastry("шоколадное");
            builder.AddCream("молочный");
            builder.AddPastry("шоколадное");
            builder.AddCream("шоколадный");
            builder.AddBeauty("звёздочки");
            return builder.Cake;
        }
    }

    public class HoneyDirector
    {
        private ICakeBuilder builder;

        public HoneyDirector(ICakeBuilder builder)
        {
            this.builder = builder;
        }

        public Cake Build()
        {
            builder.SetName("Медовый торт");
            builder.AddPastry("медовое");
            builder.AddCream("медовый");
            builder.AddPastry("шоколадное");
            builder.AddCream("медовый");
            builder.AddBeauty("шоколадные соты");
            return builder.Cake;
        }
    }

    public class Cake
    {
        private List<Layer> layers = new List<Layer>();

        public Cake()
        {
        }

        public string Name { get; set; }

        public void AddLayer(Layer layer)
        {
            layers.Add(layer);
        }

        public override string ToString()
        {
            StringBuilder sb = new StringBuilder();
            sb.Append($"Торт \"{ Name }\":\n");
            foreach (var l in layers)
            {
                sb.Append(l.ToString());
                sb.Append('\n');
            }
            return sb.ToString();
        }
    }

    class Program
    {
        static void Main(string[] args)
        {
            Console.WriteLine("Шоколадный директор, простой торт");
            ICakeBuilder builder = new SimpleCakeBuilder();
            ChocolateDirector director = new ChocolateDirector(builder);
            Cake cake = director.Build();
            Console.WriteLine(cake);
            Console.WriteLine();
            Console.WriteLine("Шоколадный директор, фруктовый торт");
            builder = new FruitCakeBuilder();
            director = new ChocolateDirector(builder);
            cake = director.Build();
            Console.WriteLine(cake);
            Console.WriteLine();
            Console.WriteLine("Медовый директор, простой торт");
            builder = new SimpleCakeBuilder();
            HoneyDirector hDir = new HoneyDirector(builder);
            cake = hDir.Build();
            Console.WriteLine(cake);
            Console.WriteLine();
            Console.WriteLine("Медовый директор, фруктовый торт");
            builder = new FruitCakeBuilder();
            hDir = new HoneyDirector(builder);
            cake = hDir.Build();
            Console.WriteLine(cake);
            Console.WriteLine();
        }
    }
}
