using AbstractFactory.Factory.Interface;
using AbstractFactory.Gadget.Interface;
using AbstractFactory.Gadget.Phone;
using AbstractFactory.Gadget.Tablet;

namespace AbstractFactory.Factory
{
    public class HuaweiGadgetFactory : IGadgetFactory
    {
        public IPhone CreatePhone()
        {
            return new HuaweiPhone();
        }

        public ITablet CreateTablet()
        {
            return new HuaweiTablet();
        }
    }
}