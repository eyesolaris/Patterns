using System;

namespace Adapter.SmtpMessenger
{
    public class SmtpClient
    {
        public void SendMessage(SmtpMessage smtpMessage)
        {
            Console.WriteLine($"Отправлено сообщение с темой: {smtpMessage.Subject}. На почту {smtpMessage.To}. С текстом: \"{smtpMessage.Text}\".");
        }
    }
}