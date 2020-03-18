namespace LightWeight
{
    public class TreeType
    {
        public TreeType(string name, Texture texture)
        {
            Name = name;
            Texture = texture;
        }

        public Texture Texture { get; }

        public string Name { get; }

        public override string ToString()
        {
            return $"Name = {Name}, Texture: [{Texture}], Hash = {GetHashCode()}";
        }
    }
}