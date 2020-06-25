#include "pch.h"
#include "BinaryTree.h"


BinaryTree::BinaryTree()
{
	
}

BinaryTree::~BinaryTree()
{
	ClearAll(m_Root);
}

void BinaryTree::InOrder(NODE* root)
{
	if (nullptr == root)
		return;
	// ���� ��ȸ
	InOrder(root->left);
	cout << "[" << root->data << "] ";
	InOrder(root->right);
}

void BinaryTree::PreOrder(NODE* root)
{
	if (nullptr == root)
		return;
	// ���� ��ȸ
	cout << "[" << root->data << "] ";
	PreOrder(root->left);
	PreOrder(root->right);
}

void BinaryTree::PostOrder(NODE* root)
{
	if (nullptr == root)
		return;
	// ���� ��ȸ
	PostOrder(root->left);
	PostOrder(root->right);
	cout << "[" << root->data << "] ";
}

void BinaryTree::LevelOrder(NODE* root)
{
	if (nullptr == root)
		return;

	// ť�� �̿��� ���� ��ȸ
	queue<NODE*> q;
	q.push(root);
	while (!q.empty())
	{
		NODE* node = q.front();
		if (nullptr != node)
		{
			cout << "[" << node->data << "] ";
			q.push(node->left);
			q.push(node->right);
		}
		q.pop();
	}
}

int BinaryTree::CountNode(NODE* root)
{
	// ����� ����
	if (nullptr == root) 
		return 0;
	return 1 + CountNode(root->left) + CountNode(root->right);
}

int BinaryTree::CountLeaf(NODE* root)
{
	// ��������� ����
	if (nullptr == root) 
		return 0;
	if (nullptr == root->left && nullptr == root->right)
		return 1;
	else
		return CountLeaf(root->left) + CountLeaf(root->right);
}

int BinaryTree::CalcHeight(NODE* root)
{
	// ���� ���ϱ�
	if (nullptr == root)
		return 0;
	return 1 + max(CalcHeight(root->left), CalcHeight(root->right));
}

NODE* BinaryTree::SetRoot(DATA data, NODE* left, NODE* right)
{
	// ��Ʈ��� ����
	m_Root = new NODE;
	m_Root->data = data;
	m_Root->left = left;
	m_Root->right = right;

	return m_Root;
}

NODE* BinaryTree::CreateNode(DATA data, NODE* left, NODE* right)
{
	// ��带 ����� Ʈ���� ����
	NODE* newNode = new NODE;
	newNode->data = data;
	newNode->left = left;
	newNode->right = right;

	return newNode;
}

void BinaryTree::ClearAll(NODE* root)
{
	// ��� ����
	// ������ȸ ������ �����Ѵ�
	if (nullptr == root)
		return;

	ClearAll(root->left);
	ClearAll(root->right);
	SAFE_DELETE(root);
}
