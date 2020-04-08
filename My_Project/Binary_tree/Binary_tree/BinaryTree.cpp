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
	// 중위 순회
	InOrder(root->left);
	cout << "[" << root->data << "] ";
	InOrder(root->right);
}

void BinaryTree::PreOrder(NODE* root)
{
	if (nullptr == root)
		return;
	// 전위 순회
	cout << "[" << root->data << "] ";
	PreOrder(root->left);
	PreOrder(root->right);
}

void BinaryTree::PostOrder(NODE* root)
{
	if (nullptr == root)
		return;
	// 후위 순회
	PostOrder(root->left);
	PostOrder(root->right);
	cout << "[" << root->data << "] ";
}

void BinaryTree::LevelOrder(NODE* root)
{
	if (nullptr == root)
		return;

	// 큐를 이용한 레벨 순회
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
	// 노드의 갯수
	if (nullptr == root) 
		return 0;
	return 1 + CountNode(root->left) + CountNode(root->right);
}

int BinaryTree::CountLeaf(NODE* root)
{
	// 리프노드의 갯수
	if (nullptr == root) 
		return 0;
	if (nullptr == root->left && nullptr == root->right)
		return 1;
	else
		return CountLeaf(root->left) + CountLeaf(root->right);
}

int BinaryTree::CalcHeight(NODE* root)
{
	// 높이 구하기
	if (nullptr == root)
		return 0;
	return 1 + max(CalcHeight(root->left), CalcHeight(root->right));
}

NODE* BinaryTree::SetRoot(DATA data, NODE* left, NODE* right)
{
	// 루트노드 세팅
	m_Root = new NODE;
	m_Root->data = data;
	m_Root->left = left;
	m_Root->right = right;

	return m_Root;
}

NODE* BinaryTree::CreateNode(DATA data, NODE* left, NODE* right)
{
	// 노드를 만들어 트리에 세팅
	NODE* newNode = new NODE;
	newNode->data = data;
	newNode->left = left;
	newNode->right = right;

	return newNode;
}

void BinaryTree::ClearAll(NODE* root)
{
	// 모두 삭제
	// 후위순회 순으로 삭제한다
	if (nullptr == root)
		return;

	ClearAll(root->left);
	ClearAll(root->right);
	SAFE_DELETE(root);
}
