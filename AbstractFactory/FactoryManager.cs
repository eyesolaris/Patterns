using System;
using AbstractFactory.Factory;
using AbstractFactory.Factory.Interface;

namespace AbstractFactory
{
    public class FactoryManager
    {
        private readonly AsusGadgetFactory _asusGadgetFactory = new AsusGadgetFactory();
        private readonly HuaweiGadgetFactory _huaweiGadgetFactory = new HuaweiGadgetFactory();

        public IGadgetFactory GetFactory(Company company)
        {
            return company switch
            {
                Company.Asus => (IGadgetFactory) _asusGadgetFactory,
                Company.Huawei => _huaweiGadgetFactory,
                _ => throw new ArgumentNullException(nameof(company))
            };
        }
    }
}