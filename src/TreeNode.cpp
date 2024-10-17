enum Balance_factor { left_higher, equal_height, right_higher };

template <class Entry>
struct TreeNode
{
    // data members:
    Entry data;
    TreeNode<Entry> *left;
    TreeNode<Entry> *right;
    bool deleted = false;
    int key{};

    // constructors:
    TreeNode();
    explicit TreeNode(const Entry &x);

    // virtual methods:
    virtual void set_balance(Balance_factor b);
    [[nodiscard]] virtual Balance_factor get_balance() const;
};

template <class Entry>
TreeNode<Entry>::TreeNode(){left, right = NULL;}

template <class Entry>
TreeNode<Entry>::TreeNode(const Entry &x)
{
    data = x;
    left, right = NULL;
}

// Dummy functions
template <class Entry>
void TreeNode<Entry>::set_balance(Balance_factor b){}

template <class Entry>
Balance_factor TreeNode<Entry>::get_balance() const{return equal_height;}
