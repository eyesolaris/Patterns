using AbstractFactory.Gadget.Interface;

namespace AbstractFactory.Gadget.Phone
{
    public class HuaweiPhone : IPhone
    {
        public string GetNamePhone()
        {
            return "Phone by Huawei";
        }
    }
}