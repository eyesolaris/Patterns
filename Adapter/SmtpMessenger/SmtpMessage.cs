using Adapter.Messenger;

namespace Adapter.SmtpMessenger
{
    public class SmtpMessage : Message
    {
        public SmtpMessage(string to, string text, string subject) : base(to, text)
        {
            Subject = subject;
        }

        public string Subject { get; }
    }
}