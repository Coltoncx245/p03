template <typename Entry>
struct TreeNode
{
    // data members
    TreeNode<Entry>* left;
    TreeNode<Entry>* right;
    int key;  // The key is now private as specified in the UML
    bool deleted;

    // Constructors:
    TreeNode();
    explicit TreeNode(int k);  // Constructor that takes an int for the key

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
