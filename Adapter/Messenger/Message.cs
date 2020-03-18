namespace Adapter.Messenger
{
    public class Message
    {
        public Message(string to, string text)
        {
            To = to;
            Text = text;
        }

        public string To { get; }

        public string Text { get; }
    }
}