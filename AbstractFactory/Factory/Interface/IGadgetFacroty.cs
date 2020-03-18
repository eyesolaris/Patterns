using AbstractFactory.Gadget.Interface;

namespace AbstractFactory.Factory.Interface
{
    public interface IGadgetFactory
    {
        IPhone CreatePhone();

        ITablet CreateTablet();
    }
}