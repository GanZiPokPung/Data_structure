#pragma once
class AVL_Tree
{
public:
	AVL_Tree();
	~AVL_Tree();
public:
	bool IsEmpty() { return (nullptr == m_Root); }
	NODE* GetRoot() { return m_Root; }
public:
	int CalcHeight(NODE* root);
	int Diff(NODE* root);
public:
	NODE* Search(NODE* n, int key);
	void Search_AVL(int key);
	bool Insert(NODE*& r, NODE* n);
	void Insert_AVL(int key);
	NODE* Banlance(NODE* n);

public:
	NODE* Rotate_LL(NODE* A);
	NODE* Rotate_RR(NODE* A);
	NODE* Rotate_RL(NODE* A);
	NODE* Rotate_LR(NODE* A);

private:
	void ClearAll(NODE* root);
private:
	NODE* m_Root = nullptr;
	int m_searchCount = 0;
};

