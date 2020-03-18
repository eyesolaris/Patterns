using System;

namespace Adapter.SmsMessenger
{
    public class SmsClient
    {
        public void SendSms(SmsMessage smsMessage)
        {
            Console.WriteLine(
                $"Отправили SMS для {smsMessage.To}. С текстом: \"{smsMessage.Text}\". Через {smsMessage.Channel} канал, Gsm шлюза.");
        }
    }
}