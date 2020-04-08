#pragma once
class BinaryTree
{
public:
	BinaryTree();
	~BinaryTree();
public:
	bool IsEmpty() { return (nullptr == m_Root); }
public:
	void InOrder(NODE* root);
	void PreOrder(NODE* root);
	void PostOrder(NODE* root);
	void LevelOrder(NODE* root);
public:
	int CountNode(NODE* root);
	int CountLeaf(NODE* root);
	int CalcHeight(NODE* root);
public:
	NODE* SetRoot(DATA data, NODE* left, NODE* right);
	NODE* CreateNode(DATA data, NODE* left, NODE* right);
private:
	void ClearAll(NODE* root);
private:
	NODE* m_Root = nullptr;
};

