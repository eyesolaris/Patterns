using System;
using System.Threading;

namespace TemplateMethod_CS
{
    // Класс общего алгоритма разработки коммерческого продукта
    public abstract class Development
    {
        // Шаги, представляющие собой этапы жизненного цикла
        protected abstract void StartDevelopment();
        protected abstract void CreateConcept();
        protected abstract void CreateTechnicalSolution();
        protected abstract void CreateAPrototype();
        protected abstract void TestPrototype();
        protected abstract void StartManufacturing();

        // Создание партии продукта
        protected abstract void CreateConsignment(int number);

        public void Develop()
        {
            StartDevelopment();
            CreateConcept();
            CreateTechnicalSolution();
            CreateAPrototype();
            TestPrototype();
            StartManufacturing();
            for (int i = 0; i < 3; i++)
            {
                CreateConsignment(i);
            }
        }
    }

    // Класс алгоритма разработки ПО
    public class SoftwareDevelopment : Development
    {
        protected override void StartDevelopment()
        {
            Console.WriteLine("Начинаем разработку нового ПО...");
            Thread.Sleep(1000);
        }
        protected override void CreateConcept()
        {
            Console.WriteLine("Создаём концепцию нового ПО");
            Thread.Sleep(1000);
        }

        protected override void CreateTechnicalSolution()
        {
            Console.WriteLine("Разрабатываем архитектуру ПО");
            Thread.Sleep(1000);
        }

        protected override void CreateAPrototype()
        {
            Console.WriteLine("Создаём прототип ПО");
            Thread.Sleep(1000);
        }

        protected override void TestPrototype()
        {
            Console.WriteLine("Тестируем ПО");
            Thread.Sleep(1000);
        }

        protected override void StartManufacturing()
        {
            Console.WriteLine("Собираем релизную сборку ПО");
            Console.Write("Компиляция");
            for (int i = 0; i < 10; i++)
            {
                Console.Write('.');
                Thread.Sleep(500);
            }
            Console.WriteLine();
            Console.WriteLine("Начинаем распространение цифровых копий");
        }

        protected override void CreateConsignment(int number)
        {
            // Метод намеренно пустой, поскольку при разработке ПО не нужно создавать партии продукта.
            // Производство ПО - всего лишь копирование информации, которое ничего не стоит
        }
    }

    // Класс алгоритма разработки бытового прибора
    public class ApplianceDevelopment : Development
    {
        protected override void StartDevelopment()
        {
            Console.WriteLine("Начинаем разработку нового бытового прибора...");
            Thread.Sleep(1000);
        }

        protected override void CreateConcept()
        {
            Console.WriteLine("Создаём концепцию нового бытового прибора");
            Thread.Sleep(1000);
        }

        protected override void CreateTechnicalSolution()
        {
            Console.WriteLine("Проектируем бытовой прибор");
            Thread.Sleep(1000);
        }

        protected override void CreateAPrototype()
        {
            Console.WriteLine("Создаём прототип бытового прибора");
            Thread.Sleep(1000);
        }

        protected override void TestPrototype()
        {
            Console.WriteLine("Тестируем прототип бытового прибора");
            Thread.Sleep(1000);
        }

        protected override void StartManufacturing()
        {
            Console.WriteLine("Запускаем бытовой прибор в серийное производство");
            Thread.Sleep(1000);
        }

        protected override void CreateConsignment(int number)
        {
            Thread.Sleep(1000);
            Console.WriteLine("Произведена партия " + number);
        }
    }

    // Классы очень схожи, но всё же различаются в деталях
    class Program
    {
        static void Main(string[] args)
        {
            Development dev = new ApplianceDevelopment();
            dev.Develop();
            Console.WriteLine();
            dev = new SoftwareDevelopment();
            dev.Develop();
            Console.WriteLine();
            Console.WriteLine("Нажмите любую клавишу. . .");
            Console.ReadKey();
        }
    }
}
