template <typename T>
struct TreeNode
{
    TreeNode<T>* left;
    TreeNode<T>* right;
    T key;
    bool deleted;

    // Constructors:
    TreeNode();
    explicit TreeNode(T k);

    // Accessor for the key:
    [[nodiscard]] T getKey() const;
};

template <typename T>
TreeNode<T>::TreeNode() : key(0), deleted(false), left(nullptr), right(nullptr) {}

template <typename T>
TreeNode<T>::TreeNode(T k) : key(k), deleted(false), left(nullptr), right(nullptr) {}

// Getter for key
template <typename T>
T TreeNode<T>::getKey() const { return key; }
