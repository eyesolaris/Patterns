namespace LightWeight
{
    public class Texture
    {
        public Texture(string name)
        {
            Name = $"texture-{name}";
        }

        public string Name { get; }

        public override string ToString()
        {
            return $"Name = {Name}";
        }
    }
}