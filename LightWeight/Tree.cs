namespace LightWeight
{
    public class Tree
    {
        public Tree(TreeType treeType, int age, double height)
        {
            TreeType = treeType;
            Age = age;
            Height = height;
        }

        public TreeType TreeType { get; }

        public int Age { get; }

        public double Height { get; }

        public override string ToString()
        {
            return $"Age = {Age}, Height = {Height}, TreeType: [{TreeType}]";
        }
    }
}