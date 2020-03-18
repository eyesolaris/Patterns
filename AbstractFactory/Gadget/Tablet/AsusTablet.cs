using AbstractFactory.Gadget.Interface;

namespace AbstractFactory.Gadget.Tablet
{
    public class AsusTablet : ITablet
    {
        public string GetNameTablet()
        {
            return "Tablet by Asus";
        }
    }
}