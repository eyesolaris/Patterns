using System;
using System.Collections.Generic;

public interface IObject
{
    string Method(object data);
}

static class ObjectRepository
{
    private static Dictionary<string, IObject> ObjectRepo = new Dictionary<string, IObject>();

    public static void Add(string path, IObject obj)
    {
        if (ObjectRepo.ContainsKey(path))
        {
            ObjectRepo[path] = obj;
        }
        else
        {
            ObjectRepo.Add(path, obj);
        }
    }

    public static bool Remove(string id)
    {
        return ObjectRepo.Remove(id);
    }

    public static IObject Get(string path)
    {
        ObjectRepo.TryGetValue(path, out IObject val);
        return val;
    }
}

public class Object : IObject
{
    public string Method(object data)
    {
        string str = "hash: " + GetHashCode() + "\n";
        if (data != null)
        {
            return str + data.ToString();
        }
        return str;
    }
}

public class ProxyObj : IObject
{
    public ProxyObj(string path)
    {
        Path = path;
    }


    public string Path { get; private set; }

    public string Method(object data)
    {
        var obj = ObjectRepository.Get(Path);
        if (obj != null)
        {
            return obj.Method(data);
        }
        throw new InvalidOperationException("Объект не найден");
    }
}

namespace Proxy
{
    class Program
    {
        static void Main(string[] args)
        {
            ObjectRepository.Add("object1", new Object());
            ObjectRepository.Add("dir/obj", new Object());
            IObject proxy = new ProxyObj("object1");
            Console.WriteLine(proxy.Method(15));
            proxy = new ProxyObj("dir/obj");
            Console.WriteLine(proxy.Method(15));
        }
    }
}
