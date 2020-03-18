using Adapter.Messenger;

namespace Adapter.SmsMessenger
{
    public class SmsMessage : Message
    {
        public SmsMessage(string to, string text, int channel) : base(to, text)
        {
            Channel = channel;
        }

        public int Channel { get; }
    }
}