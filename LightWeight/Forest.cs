using System.Collections.Generic;
using System.Text;

namespace LightWeight
{
    public class Forest
    {
        private readonly IDictionary<Point, Tree> _trees;
        private readonly TreeTypeFactory _treeTypeFactory;

        public Forest(TreeTypeFactory treeTypeFactory)
        {
            _trees = new Dictionary<Point, Tree>();
            _treeTypeFactory = treeTypeFactory;
        }

        public void Grow(Point point, string name)
        {
            var treeType = _treeTypeFactory.GetByName(name);
            Plant(point, new Tree(treeType, 0, 0));
        }

        public void Plant(Point point, Tree tree)
        {
            _trees[point] = tree;
        }

        public override string ToString()
        {
            var stringBuilder = new StringBuilder();
            foreach (var tree in _trees.Values) stringBuilder.AppendLine(tree.ToString());
            return stringBuilder.ToString();
        }
    }
}