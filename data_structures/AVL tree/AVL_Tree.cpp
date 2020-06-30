#include "AVL_Tree.h"


//Public functions

/**
* Initializes the tree to empty.
*/
AVL_Tree::AVL_Tree() {
    root = nullptr;
}

/**
* Destructor. Invokes the method deallocateMemory, passing to it the root
* of the tree.
*/
AVL_Tree::~AVL_Tree() {
    deallocateMemory(root);
}

/**
* Determines if an item exists in the tree. This method invokes the private
* method search, passing to it the element to be found and the root
* of the actual tree.
*
* x: element to be found.
*
* Returns true if x is found in the tree, false otherwise.
*/
bool AVL_Tree::search(int x) {
    return search(x, root);
}

/**
* Adds the element x to the tree. This method invokes the private method
* add, passing to it the element to be added to the tree and the root
* of the actual tree.
*
* x: element to be added to the bst.
*/
void AVL_Tree::add(int x) {
    add(x, root, nullptr);
}


/**
* Removes the element x from the tree. This method invokes the private method
* erase, passing to it the element to be removed from the tree and the root
* of the actual tree.
*
* x: element to be removed from the bst.
*/
void AVL_Tree::erase(int x) {
    erase(x, root);
}

/**
* This method return a string representation of the values in the data structure,
* which consist of all the values concatenated and separated by ", ".
* This method invokes the private method to_string.
*/
string AVL_Tree::to_string() {
    string s;
    to_string(root, &s);
    if (s.length() != 0)
        s.resize(s.length() - 1);
    return s;
}

/**
* Returns the height of the tree.
*
* This method invokes the private method getHeight.
*/
int AVL_Tree::getHeight() {
    return getHeight(root);
}

/**
* This method return the number of occurrences of the item x in the data structure.
*
* This method invokes the private method count.
*/
int AVL_Tree::count(int x) {
    int n = 0;
    return count(x, n, root);
}


//Private functions

/**
* This method return a string representation of the values in the data structure,
* which consist of the elements of the subtree whose root is pointed to by p and separated by ", ".
* Uses inorder traversal.
*
* p: root of subtree.
*/
void AVL_Tree::to_string(TreeNode *p, string *s) {
    if (p != nullptr) {
        to_string(p->left, s);
        s->append(std::to_string(p->key));
        s->append(",");
        to_string(p->right, s);
    }
}

/**
* Returns the balance factor of the subtree pointed to by p.
*
* p: root of subtree.
*/
int AVL_Tree::balanceFactor(TreeNode *p) {
    if (p == nullptr)
        return 0;
    else
        return getHeight(p->left) - getHeight(p->right);
}


TreeNode *AVL_Tree::balance(TreeNode *p) {
    fixHeight(p);
    if (balanceFactor(p) == -2) {
        if (balanceFactor(p->right) > 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (balanceFactor(p) == 2) {
        if (balanceFactor(p->left) < 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p;
}

/**
* Remove the element key in the subtree.
* Returns the result of this operation.
*
* p: root of subtree.
* key: element to be removed from the subtree.
*/
TreeNode *AVL_Tree::erase(int key, TreeNode *p) {
    if (p == nullptr)
        return nullptr;

    if (key < p->key)
        p->left = erase(key, p->left);
    else if (key > p->key)
        p->right = erase(key, p->right);
    else {
        TreeNode *left = p->left, *right = p->right;
        if (right == nullptr) {
            if (left != nullptr)
                left->parent = p->parent;
            if (p->parent == nullptr)
                root = left;
            delete p;
            return left;
        } else {
            TreeNode *min = findMin(right);
            min->right = removeMin(right);
            min->left = left;
            min->parent = p->parent;
            if (p->parent == nullptr)
                root = min;
            delete p;
            return balance(min);
        }
    }
    return balance(p);
}

/**
* Find a root of the smallest element in the subtree.
* Returns the root of minimum element of subtree.
*
* p: root of subtree.
*/
TreeNode *AVL_Tree::findMin(TreeNode *p) {
    TreeNode *current = p;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

/**
* Removing the minimum element from the subtree.
* The minimal node itself is not deleted.
* Balancing this subtree.
* Returns the pointer to the right node
*
* p: root of subtree.
*/
TreeNode *AVL_Tree::removeMin(TreeNode *p) {
    if (p->left == nullptr)
        return p->right;
    p->left = removeMin(p->left);
    return balance(p);
}

/**
* Right turn around p.
* Returns the new root of subtree.

* p: root of subtree.
*/
TreeNode *AVL_Tree::rotateRight(TreeNode *) {
    TreeNode *parent = p->parent;
    TreeNode *q = p->left;
    p->left = q->right;
    if (q->right != nullptr)
        q->right->parent = p;
    q->right = p;
    q->parent = parent;
    p->parent = q;
    fixHeight(p);
    fixHeight(q);
    if (parent == nullptr)
        root = q;
    else {
        if (parent->left->key == p->key)
            parent->left = q;
        else
            parent->right = q;
    }
    return q;
}

/**
* Left turn around p.
* Returns the new root of subtree.

* p: root of subtree.
*/
TreeNode *AVL_Tree::rotateLeft(TreeNode *) {
    TreeNode *parent = p->parent;
    TreeNode *q = p->right;
    p->right = q->left;
    if (q->left != nullptr)
        q->left->parent = p;
    q->left = p;
    q->parent = parent;
    p->parent = q;
    fixHeight(p);
    fixHeight(q);
    if (parent == nullptr)
        root = q;
    else {
        if (parent->left->key == p->key)
            parent->left = q;
        else
            parent->right = q;
    }
    return q;
}

/**
* Adds x to the subtree pointed to by p. The search for the location to
* insert the new node is conducted recursively, using the avl tree property:
* keys in the left subtree of a node are smaller than or equal to the key
* in the node, while the keys in the right subtree of the node are greater.
* Balancing this subtree.
*
* x: element to be added to the subtree.
* p: root of subtree.
* parent: parent of the root of subtree.
*/
void AVL_Tree::add(int x, TreeNode *&p, TreeNode *parent) {
    if (p == nullptr) {
        p = new TreeNode;
        p->key = x;
        p->left = p->right = nullptr;
        p->parent = parent;
        p->height = 1;
    } else {
        if (x <= p->key) add(x, p->left, p);
        else add(x, p->right, p);
        balance(p);
    }
}

/**
* Finds if x is present in the subtree whose root is pointed to by p. The
* search is conducted recursively, using the avl tree property: keys in the left
* subtree of a node are smaller than or equal to the key in the node, while
* the keys in the right subtree of the node are greater.
*
* x: element to be found.
* p: root of subtree.
*
* Returns true if x is found in this subtree, false otherwise.
*/
bool AVL_Tree::search(int x, TreeNode *p) {
    if (p == nullptr) return false;
    else if (x == p->key) return true;
    else if (x < p->key) return search(x, p->left);
    else return search(x, p->right);
}

/**
* Returns the height of the subtree pointed to by p.
*
* p: root of subtree.
*/
int AVL_Tree::getHeight(TreeNode *p) {
    if (p == nullptr)
        return 0;
    else
        return p->height;
}

/**
* The function restores the correct value of the height
* of the subtree pointed to by p, provided that the values of
* this field in the right and left nodes are corrective.
*
* p: root of subtree.
*/
void AVL_Tree::fixHeight(TreeNode *p) {
    p->height = max(getHeight(p->left), getHeight(p->right)) + 1;
}

/**
* This method return the number of occurrences of the item x in the data structure.
*
* p: root of subtree.
*/
int AVL_Tree::count(int x, int n, TreeNode *p) {
    if (p == NULL) return n;
    else {
        if (x == p->key) {
            n++;
            return count(x, n, p->left);
        }
        if (x > p->key)
            return count(x, n, p->right);
        else
            return count(x, n, p->left);
    }
}

/**
* Recursively deallocates the memory of the subtree pointed to by p.
*
* p: root of subtree.
*/
void AVL_Tree::deallocateMemory(TreeNode *&p) {
    if (p != nullptr) {
        deallocateMemory(p->left);
        deallocateMemory(p->right);
        delete p;
        p = nullptr;
    }
}


void AVL_Tree::display() {
    int maxHeight;
    if (root != nullptr) {
        maxHeight = root->height;
        for (int i = maxHeight; i > 0; --i) {
            printTreeNode(root, i);
            cout << endl;
        }
    }
    cout << endl;
}

void AVL_Tree::printTreeNode(TreeNode *p, int height) {
    if (p == nullptr)
        return;
    if (p->height > height) {
        printTreeNode(p->left, height);
        printTreeNode(p->right, height);
    } else if (p->height == height) {
        cout << p->key << "(height = " << p->height << ", heightLeft = " << getHeight(p->left) << ", heightRight = "
             << getHeight(p->right);
        if (p->parent != nullptr)
            cout << ", parent = " << p->parent->key << ") ";
        else
            cout << ") ";
        return;
    }
}
