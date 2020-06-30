#pragma once
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

/**
* Binary search tree node.
*/
struct TreeNode
{
	int key;			//element stored in this node
	int height;         //height of the subtree pointed to by this node
	TreeNode *left;		//link to left child
	TreeNode *right;	//link to right child
	TreeNode *parent;	//link to parent
};

/**
* Class implementing an AVL tree.
*/
class AVL_Tree
{
public:
	AVL_Tree();
	~AVL_Tree();
	bool search(int);
	void add(int);
	void erase(int);
	string to_string();
	int count(int);
	int getHeight();

	void display();
	void printTreeNode(TreeNode*, int);
private:
	TreeNode* root;
	TreeNode* rotateRight(TreeNode*);
	TreeNode* rotateLeft(TreeNode*);
	int getHeight(TreeNode*);
	void fixHeight(TreeNode*);
	int balanceFactor(TreeNode*);
	TreeNode * balance(TreeNode*);
	TreeNode * findMin(TreeNode*);
	TreeNode * removeMin(TreeNode*);
	bool search(int, TreeNode*);
	void add(int, TreeNode* &, TreeNode*);
	TreeNode * erase(int, TreeNode*);
	void to_string(TreeNode*, string*);
	int count(int, int, TreeNode*);
	void deallocateMemory(TreeNode* &);
};

