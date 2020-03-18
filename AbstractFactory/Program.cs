using System;

namespace AbstractFactory
{
    public class Program
    {
        private static FactoryManager FactoryManager { get; } = new FactoryManager();

        private static void Main(string[] args)
        {
            ShowGadgetsBy(Company.Asus);
            ShowGadgetsBy(Company.Huawei);
            Console.ReadLine();
        }

        private static void ShowGadgetsBy(Company company)
        {
            var factory = FactoryManager.GetFactory(company);
            Console.WriteLine($"Gadgets by {company}");
            Console.WriteLine(factory.CreatePhone().GetNamePhone());
            Console.WriteLine(factory.CreateTablet().GetNameTablet());
            Console.WriteLine();
        }
    }
}