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
	// 높이 구하기
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
	if (nullptr == n)					// 노드에 동일한 키가 없으므로 탐색에 실패
		return nullptr;
	else if (n->data == key)			// 노드에 키와 동일하다면 값을 찾은것
		return n;
	else if (n->data > key)
		return Search(n->left, key);	// 키가 노드보다 작은경우 왼쪽서브트리에서 찾는다.
	else
		return Search(n->right, key);	// 키가 노드보다 큰경우 오른쪽서브트리에서 찾는다.
}

void AVL_Tree::Search_AVL(int key)
{
	NODE* n = Search(m_Root, key);
	if (nullptr != n)
		cout << "[탐색 연산] : 성공, 찾은 횟수 : " << m_searchCount
		<< " [" << n->data << "] = " << std::hex << n << endl;
	else
		cout << "[탐색 연산] : 실패, No " << key << endl;

	cout << std::dec;
	m_searchCount = 0;
}

bool AVL_Tree::Insert(NODE*& r, NODE* n)
{
	// 밸런스 조정 후의 노드위치(주소)를 m_Root에 덮어써야 하기 때문에
	// 레퍼런스 포인터형을 매개변수로 받는다.

	if (n->data == r->data)
		return false;					// 이미 동일한 키가 존재하므로 삽입불가능(탐색 성공)
	else if (n->data < r->data)
	{
		if (nullptr == r->left)
			r->left = n;			// 탐색에 실패한 위치에 새로운 노드 삽입
		else
		{
			Insert(r->left, n);		// 아직 찾아야 할 서브트리가 남아있음
			r = Banlance(r);		// 노드추가가 된 상태라면 트리의 밸런스를 맞춘다.
									// 그리고 밸런스를 맞춘 후 루트노드 위치를 재조정한다.
		}
	}
	else
	{
		if (nullptr == r->right)
			r->right = n;			// 탐색에 실패한 위치에 새로운 노드 삽입
		else
		{
			Insert(r->right, n);  	// 아직 찾아야 할 서브트리가 남아있음
			r = Banlance(r);		// 노드추가가 된 상태라면 트리의 밸런스를 맞춘다.
									// 그리고 밸런스를 맞춘 후 루트노드 위치를 재조정한다.
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

	// 왼쪽 서브트리쪽으로 삽입되어 균형이 깨진 경우
	if (1 < factor)
	{
		// 왼쪽 서브트리의 왼쪽 자식노드 쪽에 불균형이 생겼으므로
		// LL 회전을 한다.
		if (0 < Diff(n->left))
			n = Rotate_LL(n);
		// 왼쪽 서브트리의 오른쪽 자식노드 쪽에 불균형이 생겼으므로
		// LR 회전을 한다.
		else
			n = Rotate_LR(n);
	}
	// 오른쪽 서브트리쪽으로 삽입되어 균형이 깨진 경우
	else if (-1 > factor)
	{
		// 오른쪽 서브트리의 왼쪽 자식노드 쪽에 불균형이 생겼으므로
		// RL 회전을 한다.
		if (0 < Diff(n->right) )
			n = Rotate_RL(n);
		// 오른쪽 서브트리의 오른쪽 자식노드 쪽에 불균형이 생겼으므로
		// RR 회전을 한다.
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
	// 모두 삭제
	// 후위순회 순으로 삭제한다
	if (nullptr == root)
		return;

	ClearAll(root->left);
	ClearAll(root->right);
	SAFE_DELETE(root);
}
