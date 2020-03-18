using System.Collections.Generic;

namespace LightWeight
{
    public class TreeTypeFactory
    {
        private readonly IDictionary<string, TreeType> _treeTypes;

        public TreeTypeFactory()
        {
            _treeTypes = new Dictionary<string, TreeType>();
        }

        public TreeType GetByName(string name)
        {
            if (_treeTypes.TryGetValue(name, out var treeType)) return treeType;

            _treeTypes[name] = new TreeType(name, new Texture(name));

            return _treeTypes[name];
        }
    }
}