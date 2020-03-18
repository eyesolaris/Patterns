using Adapter.Messenger;
using Adapter.Messenger.Interface;

namespace Adapter.SmtpMessenger
{
    public class SmtpMessengerAdapter : IMessenger
    {
        private readonly SmtpClient _smtpClient;
        private readonly string _subjectMessage;

        public SmtpMessengerAdapter(string nameCompany)
        {
            _subjectMessage = $"Message by {nameCompany}";
            _smtpClient = new SmtpClient();
        }

        public void Send(Message message)
        {
            _smtpClient.SendMessage(new SmtpMessage(message.To, message.Text, _subjectMessage));
        }
    }
}