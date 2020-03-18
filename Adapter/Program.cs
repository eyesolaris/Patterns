using System;
using System.Collections.Generic;
using Adapter.Messenger;
using Adapter.Messenger.Interface;
using Adapter.SmsMessenger;
using Adapter.SmtpMessenger;

namespace Adapter
{
    internal class Program
    {
        private static void Main(string[] args)
        {
            var message = new Message("MyFriend", "Hello, my friend!");
            var messengers = new List<IMessenger>
            {
                new SmtpMessengerAdapter("MyCompany"),
                new SmsMessengerAdapter(new List<int> {1, 2, 3, 4})
            };

            SendByAllMessengers(message, messengers);

            Console.ReadLine();
        }

        private static void SendByAllMessengers(Message message, IEnumerable<IMessenger> messengers)
        {
            foreach (var messenger in messengers)
            {
                messenger.Send(message);
            }
        }
    }
}