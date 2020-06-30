/********************************************************
*  Week 6 homework:                                     *
* Exercise 4: Recursion and Binary Trees			    *
*********************************************************/
#pragma once
#include <string>
using namespace std;

/*
* Binary search tree node.
*/
struct TreeNode
{
	int info;			//element stored in this node
	TreeNode *left;		//link to left child
	TreeNode *right;	//link to right child
};
/*
* Class implementing a binary search tree.
*/
class BinarySearchTree
{
public:
	BinarySearchTree();
	bool isEmpty();
	void preorderDisplay();
	void postorderDisplay();
	bool search(int);
	void add(int);
	int getMinimum();
	string to_string();
	int count(int);
	int getHeight();
	~BinarySearchTree();
private:
	TreeNode* root;
	string s;
	void inorderDisplay(TreeNode*);
	void backorderDisplay(TreeNode*);
	bool search(int, TreeNode*);
	void add(int, TreeNode* &);
	TreeNode* getMinimum(TreeNode*);
	void to_string(TreeNode*);
	int count(int, int, TreeNode*);
	int getHeight(int, TreeNode*);
	void deallocateMemory(TreeNode* &);
};
