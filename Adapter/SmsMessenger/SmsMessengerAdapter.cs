using System.Collections.Generic;
using Adapter.Messenger;
using Adapter.Messenger.Interface;

namespace Adapter.SmsMessenger
{
    public class SmsMessengerAdapter : IMessenger
    {
        private readonly IEnumerator<int> _channelEnumerator;
        private readonly SmsClient _smsClient;

        public SmsMessengerAdapter(IEnumerable<int> channels)
        {
            _smsClient = new SmsClient();
            _channelEnumerator = channels.GetEnumerator();
            _channelEnumerator.MoveNext();
        }

        public void Send(Message message)
        {
            _smsClient.SendSms(new SmsMessage(message.To, message.Text, GetChannel()));
        }

        private int GetChannel()
        {
            var channel = _channelEnumerator.Current;

            if (_channelEnumerator.MoveNext())
                return channel;

            _channelEnumerator.Reset();
            _channelEnumerator.MoveNext();

            return channel;
        }
    }
}