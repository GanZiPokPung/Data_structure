#pragma once
class BinarySearchTree
{
public:
	BinarySearchTree();
	~BinarySearchTree();
public:
	bool IsEmpty() { return (nullptr == m_Root); }
	NODE* GetRoot() { return m_Root; }
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
	NODE* Search(NODE* n, int key);
	void Search_BST(int key);
	bool Insert(NODE* r, NODE* n);
	void Insert_BST(int key);
	void Delete(NODE* p, NODE* n);
	void Delete_BST(int key);

private:
	void ClearAll(NODE* root);
private:
	NODE* m_Root = nullptr;
};

