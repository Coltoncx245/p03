template <typename Entry>
struct TreeNode
{
    TreeNode<Entry>* left;
    TreeNode<Entry>* right;
    int key;
    bool deleted;

    // Constructors:
    TreeNode();
    explicit TreeNode(int k);

    // Accessor for the key:
    [[nodiscard]] int getKey() const;
};

template <typename Entry>
TreeNode<Entry>::TreeNode() : key(0), deleted(false), left(nullptr), right(nullptr) {}

template <typename Entry>
TreeNode<Entry>::TreeNode(int k) : key(k), deleted(false), left(nullptr), right(nullptr) {}

// Getter for key
template <typename Entry>
int TreeNode<Entry>::getKey() const { return key; }
