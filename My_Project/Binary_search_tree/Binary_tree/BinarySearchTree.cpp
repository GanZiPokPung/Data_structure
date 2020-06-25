#include "pch.h"
#include "BinarySearchTree.h"

BinarySearchTree::BinarySearchTree()
{
}

BinarySearchTree::~BinarySearchTree()
{
	ClearAll(m_Root);
}

void BinarySearchTree::InOrder(NODE* root)
{
	if (nullptr == root)
		return;
	// ���� ��ȸ
	InOrder(root->left);
	cout << "[" << root->data << "] ";
	InOrder(root->right);
}

void BinarySearchTree::PreOrder(NODE* root)
{
	if (nullptr == root)
		return;
	// ���� ��ȸ
	cout << "[" << root->data << "] ";
	PreOrder(root->left);
	PreOrder(root->right);
}

void BinarySearchTree::PostOrder(NODE* root)
{
	if (nullptr == root)
		return;
	// ���� ��ȸ
	PostOrder(root->left);
	PostOrder(root->right);
	cout << "[" << root->data << "] ";
}

void BinarySearchTree::LevelOrder(NODE* root)
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

int BinarySearchTree::CountNode(NODE* root)
{
	// ����� ����
	if (nullptr == root)
		return 0;
	return 1 + CountNode(root->left) + CountNode(root->right);
}

int BinarySearchTree::CountLeaf(NODE* root)
{
	// ��������� ����
	if (nullptr == root)
		return 0;
	if (nullptr == root->left && nullptr == root->right)
		return 1;
	else
		return CountLeaf(root->left) + CountLeaf(root->right);
}

int BinarySearchTree::CalcHeight(NODE* root)
{
	// ���� ���ϱ�
	if (nullptr == root)
		return 0;
	return 1 + max(CalcHeight(root->left), CalcHeight(root->right));
}

NODE* BinarySearchTree::Search(NODE* n, int key)
{
	if (nullptr == n)					// ��忡 ������ Ű�� �����Ƿ� Ž���� ����
		return nullptr;
	else if (n->data == key)			// ��忡 Ű�� �����ϴٸ� ���� ã����
		return n;
	else if (n->data > key)
		return Search(n->left, key);	// Ű�� ��庸�� ������� ���ʼ���Ʈ������ ã�´�.
	else
		return Search(n->right, key);	// Ű�� ��庸�� ū��� �����ʼ���Ʈ������ ã�´�.
}

void BinarySearchTree::Search_BST(int key)
{
	NODE* n = Search(m_Root, key);
	if (nullptr != n)
		cout << "[Ž�� ����] : ����, " << "[" << n->data << "] = "
		<< std::hex << n << endl;
	else
		cout << "[Ž�� ����] : ����, No " << key << endl;

	cout << std::dec;
}

bool BinarySearchTree::Insert(NODE* r, NODE* n)
{
	if (n->data == r->data)
		return false;					// �̹� ������ Ű�� �����ϹǷ� ���ԺҰ���(Ž�� ����)
	else if (n->data < r->data)
	{
		if (nullptr == r->left)
			r->left = n;			// Ž���� ������ ��ġ�� ���ο� ��� ����
		else
			Insert(r->left, n);		// ���� ã�ƾ� �� ����Ʈ���� ��������
	}
	else
	{
		if (nullptr == r->right)
			r->right = n;			// Ž���� ������ ��ġ�� ���ο� ��� ����
		else
			Insert(r->right, n);  	// ���� ã�ƾ� �� ����Ʈ���� ��������
	}
	return true;
}

void BinarySearchTree::Insert_BST(int key)
{
	NODE* n = new NODE;
	n->data = key;
	n->left = nullptr; n->right = nullptr;

	if (IsEmpty())
		m_Root = n;
	else if (!Insert(m_Root, n))
		SAFE_DELETE(n);
}

void BinarySearchTree::Delete(NODE* p, NODE* n)
{
	// n�� ������ ���
	// p�� ������ ����� �θ���

	// case 1 : �ܸ������ ���
	if (nullptr == n->left && nullptr == n->right)
	{
		// ���� ��Ʈ ����� ��Ʈ ��带 �����Ѵ�.
		if (nullptr == p)
		{
			SAFE_DELETE(m_Root);
		}
		else
		{
			// �θ𿡼� ������ ����� ��ũ�� ���´�. 
			if (n == p->left)
				p->left = nullptr;
			else
				p->right = nullptr;
		}
	}
	// case 2 : �ڽ��� �ϳ��� ����� ���
	else if (nullptr == n->left || nullptr == n->right)
	{
		// ������ ����� �ڽ��� �ִ� ���� ��带 �޾ƿ´�.
		NODE* child = (nullptr != n->left) ? n->left : n->right;
		// ���� ��尡 ��Ʈ ����� child�� ��Ʈ��带 ����Ѵ�.
		if (m_Root == n)
			m_Root = child;
		else
		{
			// ������ ��尡 �θ��� ���� �ڽ� ����� ���� �ڽ� ��带 child�� ����Ѵ�.
			// Ȥ�� ������ �ڽ� ����� ������ �ڽ� ��带 child�� ����Ѵ�.
			if (n == p->left)
				p->left = child;
			else
				p->right = child;
		}
	}
	// case 3 : �ڽ��� ���� ����� ���
	else
	{
		// �İ��� ����� �θ��� childParent
		// �İ��� ��� child
		NODE* childParent = n;
		NODE* child = n->right;

		// ������ �İ��� ��带 ã�� ���� 
		// ������ ����Ʈ���� ���� ���� ��带 ã�´�.
		while (nullptr != child->left)
		{
			childParent = child;
			child = child->left;
		}

		// �İ��� ����� �θ� ����� ���ʿ� ��ġ�Ѵٸ� 
		// �� ��ġ�� �İ��� ����� ������ ��带 ����Ѵ�.
		// �����ʿ� ��ġ�Ѵٸ� �װ��� ����Ѵ�.
		if (child == childParent->left)
			childParent->left = child->right;
		else
			childParent->right = child->right;

		// ���� ��� ��ġ�� �����͸� �İ��� ����� �����ͷ� �����Ѵ�.
		n->data = child->data;
		// ��ü�� �Ϸ�Ǿ����Ƿ� ���� ���ʿ��� �İ��� ��带 �����.
		n = child;
	}
	// ���� ��带 �����Ҵ� �����Ѵ�.
	SAFE_DELETE(n);
}

void BinarySearchTree::Delete_BST(int key)
{
	NODE* parent = nullptr;
	NODE* node = m_Root;

	if (nullptr == node)
		return;
	while (nullptr != node && key != node->data)
	{
		parent = node;
		node = (key < node->data) ? node->left : node->right;
	}
	if (nullptr == node)
	{
		cout << "Error : key is not in the tree!\n";
	}
	else
		Delete(parent, node);
}

void BinarySearchTree::ClearAll(NODE* root)
{
	// ��� ����
	// ������ȸ ������ �����Ѵ�
	if (nullptr == root)
		return;

	ClearAll(root->left);
	ClearAll(root->right);
	SAFE_DELETE(root);
}
