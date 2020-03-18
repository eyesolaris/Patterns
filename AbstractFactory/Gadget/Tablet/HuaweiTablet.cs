using AbstractFactory.Gadget.Interface;

namespace AbstractFactory.Gadget.Tablet
{
    public class HuaweiTablet : ITablet
    {
        public string GetNameTablet()
        {
            return "Tablet by Huawei";
        }
    }
}