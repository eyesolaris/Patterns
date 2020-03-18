using AbstractFactory.Gadget.Interface;

namespace AbstractFactory.Gadget.Phone
{
    public class AsusPhone : IPhone
    {
        public string GetNamePhone()
        {
            return "Phone by Asus";
        }
    }
}