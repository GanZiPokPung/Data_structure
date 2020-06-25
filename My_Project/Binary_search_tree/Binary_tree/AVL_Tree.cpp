#include "pch.h"
#include "AVL_Tree.h"

AVL_Tree::AVL_Tree()
{
}

AVL_Tree::~AVL_Tree()
{
	ClearAll(m_Root);
}

int AVL_Tree::CalcHeight(NODE* root)
{
	// ���� ���ϱ�
	if (nullptr == root)
		return 0;
	return 1 + max(CalcHeight(root->left), CalcHeight(root->right));
}

int AVL_Tree::Diff(NODE* root)
{
	int left = CalcHeight(root->left);
	int right = CalcHeight(root->right);
	return left - right;
}

NODE* AVL_Tree::Search(NODE* n, int key)
{
	++m_searchCount;
	if (nullptr == n)					// ��忡 ������ Ű�� �����Ƿ� Ž���� ����
		return nullptr;
	else if (n->data == key)			// ��忡 Ű�� �����ϴٸ� ���� ã����
		return n;
	else if (n->data > key)
		return Search(n->left, key);	// Ű�� ��庸�� ������� ���ʼ���Ʈ������ ã�´�.
	else
		return Search(n->right, key);	// Ű�� ��庸�� ū��� �����ʼ���Ʈ������ ã�´�.
}

void AVL_Tree::Search_AVL(int key)
{
	NODE* n = Search(m_Root, key);
	if (nullptr != n)
		cout << "[Ž�� ����] : ����, ã�� Ƚ�� : " << m_searchCount
		<< " [" << n->data << "] = " << std::hex << n << endl;
	else
		cout << "[Ž�� ����] : ����, No " << key << endl;

	cout << std::dec;
	m_searchCount = 0;
}

bool AVL_Tree::Insert(NODE*& r, NODE* n)
{
	// �뷱�� ���� ���� �����ġ(�ּ�)�� m_Root�� ������ �ϱ� ������
	// ���۷��� ���������� �Ű������� �޴´�.

	if (n->data == r->data)
		return false;					// �̹� ������ Ű�� �����ϹǷ� ���ԺҰ���(Ž�� ����)
	else if (n->data < r->data)
	{
		if (nullptr == r->left)
			r->left = n;			// Ž���� ������ ��ġ�� ���ο� ��� ����
		else
		{
			Insert(r->left, n);		// ���� ã�ƾ� �� ����Ʈ���� ��������
			r = Banlance(r);		// ����߰��� �� ���¶�� Ʈ���� �뷱���� �����.
									// �׸��� �뷱���� ���� �� ��Ʈ��� ��ġ�� �������Ѵ�.
		}
	}
	else
	{
		if (nullptr == r->right)
			r->right = n;			// Ž���� ������ ��ġ�� ���ο� ��� ����
		else
		{
			Insert(r->right, n);  	// ���� ã�ƾ� �� ����Ʈ���� ��������
			r = Banlance(r);		// ����߰��� �� ���¶�� Ʈ���� �뷱���� �����.
									// �׸��� �뷱���� ���� �� ��Ʈ��� ��ġ�� �������Ѵ�.
		}
	}
	return true;
}

void AVL_Tree::Insert_AVL(int key)
{
	NODE* n = new NODE;
	n->data = key;
	n->left = nullptr; n->right = nullptr;

	if (IsEmpty())
		m_Root = n;
	else if (!Insert(m_Root, n))
		SAFE_DELETE(n);
}

NODE* AVL_Tree::Banlance(NODE* n)
{
	int factor = Diff(n);

	// ���� ����Ʈ�������� ���ԵǾ� ������ ���� ���
	if (1 < factor)
	{
		// ���� ����Ʈ���� ���� �ڽĳ�� �ʿ� �ұ����� �������Ƿ�
		// LL ȸ���� �Ѵ�.
		if (0 < Diff(n->left))
			n = Rotate_LL(n);
		// ���� ����Ʈ���� ������ �ڽĳ�� �ʿ� �ұ����� �������Ƿ�
		// LR ȸ���� �Ѵ�.
		else
			n = Rotate_LR(n);
	}
	// ������ ����Ʈ�������� ���ԵǾ� ������ ���� ���
	else if (-1 > factor)
	{
		// ������ ����Ʈ���� ���� �ڽĳ�� �ʿ� �ұ����� �������Ƿ�
		// RL ȸ���� �Ѵ�.
		if (0 < Diff(n->right) )
			n = Rotate_RL(n);
		// ������ ����Ʈ���� ������ �ڽĳ�� �ʿ� �ұ����� �������Ƿ�
		// RR ȸ���� �Ѵ�.
		else
			n = Rotate_RR(n);
	}

	return n;
}

NODE* AVL_Tree::Rotate_LL(NODE* A)
{
	NODE* B = A->left;
	A->left = B->right;
	B->right = A;
	return B;
}

NODE* AVL_Tree::Rotate_RR(NODE* A)
{
	NODE* B = A->right;
	A->right = B->left;
	B->left = A;
	return B;
}

NODE* AVL_Tree::Rotate_RL(NODE* A)
{
	NODE* B = A->right;
	A->right = Rotate_LL(B);
	return Rotate_RR(A);
}

NODE* AVL_Tree::Rotate_LR(NODE* A)
{
	NODE* B = A->left;
	A->left = Rotate_RR(B);
	return Rotate_LL(A);
}

void AVL_Tree::ClearAll(NODE* root)
{
	// ��� ����
	// ������ȸ ������ �����Ѵ�
	if (nullptr == root)
		return;

	ClearAll(root->left);
	ClearAll(root->right);
	SAFE_DELETE(root);
}
