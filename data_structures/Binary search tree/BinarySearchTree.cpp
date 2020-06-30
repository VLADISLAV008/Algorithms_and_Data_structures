/********************************************************
*  Week 6 homework:                                     *
* Exercise 4: Recursion and Binary Trees			    *
*********************************************************/

#include <iostream>
#include "BinarySearchTree.h"
#include <algorithm>
#include <string>

using namespace std;

//Public functions

/*
* Initializes the bst to empty.
*/
BinarySearchTree::BinarySearchTree() {
    root = NULL;
}

/*
* Determines whether the bst is empty
*
* Returns true if the bst is empty, false otherwise
*/
bool BinarySearchTree::isEmpty() {
    return root == NULL;
}

/*
* Prints the bst elements using inorder traversal. This method invokes the
* private method inorderDisplay, passing to it the root of the actual tree.
*/
void BinarySearchTree::preorderDisplay() {
    inorderDisplay(root);
    cout << endl;
}

/*
* Prints the bst elements using backorder traversal. This method invokes the
* private method backorderDisplay, passing to it the root of the actual tree.
*/
void BinarySearchTree::postorderDisplay() {
    backorderDisplay(root);
    cout << endl;
}

/*
* Determines if an item exists in the bst. This method invokes the private
* method search, passing to it the element to be found and the root
* of the actual tree.
*
* x: element to be found.
*
* Returns true if x is found in the bst, false otherwise.
*/
bool BinarySearchTree::search(int x) {
    return search(x, root);
}

/*
* Adds the element x to the bst. This method invokes the private method
* add, passing to it the element to be added to the bst and the root
* of the actual tree.
*
* x: element to be added to the bst.
*/
void BinarySearchTree::add(int x) {
    add(x, root);
}

/*
* Finds the smallest value in the bst. This method invokes the overloaded
* method getMinimum, passing to it the root of the tree.
*
* Returns the smallest value in the bst.
*/
int BinarySearchTree::getMinimum() {
    return getMinimum(root)->info;
}


/*
* This method return a string representation of the values in the data structure,
* which consist of all the values concatenated and separated by ", ".
* This method invokes the private method to_string.
*/
string BinarySearchTree::to_string() {
    s.clear();
    to_string(root);
    s.resize(s.length() - 1);
    return s;
}

/*
* This method return the number of occurrences of the item x in the data structure.
*
* This method invokes the private method count.
*/
int BinarySearchTree::count(int x) {
    int n = 0;
    return count(x, n, root);
}

/*
* This method return the height of the tree.
*
* This method invokes the private method getHeight.
*/
int BinarySearchTree::getHeight() {
    int height = 0;
    return getHeight(height, root) - 1;
}

/*
* Destructor. Invokes the method deallocateMemory, passing to it the root
* of the tree.
*/
BinarySearchTree::~BinarySearchTree() {
    deallocateMemory(root);
}

//Private functions

/*
* Prints the elements of the subtree whose root is pointed to by p. Uses
* inorder traversal.
*
* p: root of subtree.
*/
void BinarySearchTree::inorderDisplay(TreeNode *p) {
    if (p != NULL) {
        inorderDisplay(p->left);
        cout << p->info << " ";
        inorderDisplay(p->right);
    }
}

/*
* Prints the elements of the subtree whose root is pointed to by p. Uses
* backorder traversal.
*
* p: root of subtree.
*/
void BinarySearchTree::backorderDisplay(TreeNode *p) {
    if (p != NULL) {
        backorderDisplay(p->right);
        cout << p->info << " ";
        backorderDisplay(p->left);
    }
}

/*
* Adds x to the subtree pointed to by p. The search for the location to
* insert the new node is conducted recursively, using the bst property:
* keys in the left subtree of a node are smaller than or equal to the key
* in the node, while the keys in the right subtree of the node are greater.
*
* x: element to be added to the subtree.
* p: root of subtree.
*/
void BinarySearchTree::add(int x, TreeNode *&p) {
    if (p == NULL) {
        p = new TreeNode;
        p->info = x;
        p->left = p->right = NULL;
    } else {
        if (x <= p->info) add(x, p->left);
        else add(x, p->right);
    }
}

/*
* Finds if x is present in the subtree whose root is pointed to by p. The
* search is conducted recursively, using the bst property: keys in the left
* subtree of a node are smaller than or equal to the key in the node, while
* the keys in the right subtree of the node are greater.
*
* x: element to be found.
* p: root of subtree.
*
* Returns true if x is found in this subtree, false otherwise.
*/
bool BinarySearchTree::search(int x, TreeNode *p) {
    if (p == NULL) return false;
    else if (x == p->info) return true;
    else if (x < p->info) return search(x, p->left);
    else return search(x, p->right);
}

/*
* Recursively finds the smallest value in the subtree pointed to by p.
* The method uses this property of BSTs: the smallest value is stored in
* the leftmost node.
*
* p: root of subtree.
*
* Returns smallest value in the subtree pointed to by p.
*/
TreeNode *BinarySearchTree::getMinimum(TreeNode *p) {
    if (p->left == NULL) return p;
    else return getMinimum(p->left);
}

/*
* This method return a string representation of the values in the data structure,
* which consist of the elements of the subtree whose root is pointed to by p and separated by ", ".
* Uses inorder traversal.
*
* p: root of subtree.
*/
void BinarySearchTree::to_string(TreeNode *p) {
    if (p != NULL) {
        to_string(p->left);
        s.append(std::to_string(p->info));
        s.append(",");
        to_string(p->right);
    }
}


/*
* This method return the number of occurrences of the item x in the data structure.
*
* p: root of subtree.
*/
int BinarySearchTree::count(int x, int n, TreeNode *p) {
    if (p == NULL) return n;
    else {
        if (x == p->info) n++;
        return n + count(x, 0, p->left) + count(x, 0, p->right);
    }
}

/*
* This method return the height of the tree + 1.
*/
int BinarySearchTree::getHeight(int height, TreeNode *p) {
    if (p == NULL) return 0;
    else {
        return 1 + max(getHeight(height, p->left), getHeight(height, p->right));
    }
}

/*
* Recursively deallocates the memory of the subtree pointed to by p.
*
* p: root of subtree.
*/
void BinarySearchTree::deallocateMemory(TreeNode *&p) {
    if (p != NULL) {
        deallocateMemory(p->left);
        deallocateMemory(p->right);
        delete p;

        p = NULL;
    }
}