using AbstractFactory.Factory.Interface;
using AbstractFactory.Gadget.Interface;
using AbstractFactory.Gadget.Phone;
using AbstractFactory.Gadget.Tablet;

namespace AbstractFactory.Factory
{
    public class AsusGadgetFactory : IGadgetFactory
    {
        public IPhone CreatePhone()
        {
            return new AsusPhone();
        }

        public ITablet CreateTablet()
        {
            return new AsusTablet();
        }
    }
}