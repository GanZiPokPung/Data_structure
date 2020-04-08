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
	// 중위 순회
	InOrder(root->left);
	cout << "[" << root->data << "] ";
	InOrder(root->right);
}

void BinarySearchTree::PreOrder(NODE* root)
{
	if (nullptr == root)
		return;
	// 전위 순회
	cout << "[" << root->data << "] ";
	PreOrder(root->left);
	PreOrder(root->right);
}

void BinarySearchTree::PostOrder(NODE* root)
{
	if (nullptr == root)
		return;
	// 후위 순회
	PostOrder(root->left);
	PostOrder(root->right);
	cout << "[" << root->data << "] ";
}

void BinarySearchTree::LevelOrder(NODE* root)
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

int BinarySearchTree::CountNode(NODE* root)
{
	// 노드의 갯수
	if (nullptr == root)
		return 0;
	return 1 + CountNode(root->left) + CountNode(root->right);
}

int BinarySearchTree::CountLeaf(NODE* root)
{
	// 리프노드의 갯수
	if (nullptr == root)
		return 0;
	if (nullptr == root->left && nullptr == root->right)
		return 1;
	else
		return CountLeaf(root->left) + CountLeaf(root->right);
}

int BinarySearchTree::CalcHeight(NODE* root)
{
	// 높이 구하기
	if (nullptr == root)
		return 0;
	return 1 + max(CalcHeight(root->left), CalcHeight(root->right));
}

NODE* BinarySearchTree::Search(NODE* n, int key)
{
	if (nullptr == n)					// 노드에 동일한 키가 없으므로 탐색에 실패
		return nullptr;
	else if (n->data == key)			// 노드에 키와 동일하다면 값을 찾은것
		return n;
	else if (n->data > key)
		return Search(n->left, key);	// 키가 노드보다 작은경우 왼쪽서브트리에서 찾는다.
	else
		return Search(n->right, key);	// 키가 노드보다 큰경우 오른쪽서브트리에서 찾는다.
}

void BinarySearchTree::Search_BST(int key)
{
	NODE* n = Search(m_Root, key);
	if (nullptr != n)
		cout << "[탐색 연산] : 성공, " << "[" << n->data << "] = "
		<< std::hex << n << endl;
	else
		cout << "[탐색 연산] : 실패, No " << key << endl;

	cout << std::dec;
}

bool BinarySearchTree::Insert(NODE* r, NODE* n)
{
	if (n->data == r->data)
		return false;					// 이미 동일한 키가 존재하므로 삽입불가능(탐색 성공)
	else if (n->data < r->data)
	{
		if (nullptr == r->left)
			r->left = n;			// 탐색에 실패한 위치에 새로운 노드 삽입
		else
			Insert(r->left, n);		// 아직 찾아야 할 서브트리가 남아있음
	}
	else
	{
		if (nullptr == r->right)
			r->right = n;			// 탐색에 실패한 위치에 새로운 노드 삽입
		else
			Insert(r->right, n);  	// 아직 찾아야 할 서브트리가 남아있음
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
	// n은 삭제할 노드
	// p는 삭제할 노드의 부모노드

	// case 1 : 단말노드인 경우
	if (nullptr == n->left && nullptr == n->right)
	{
		// 만약 루트 노드라면 루트 노드를 삭제한다.
		if (nullptr == p)
		{
			SAFE_DELETE(m_Root);
		}
		else
		{
			// 부모에서 삭제할 노드의 링크를 끊는다. 
			if (n == p->left)
				p->left = nullptr;
			else
				p->right = nullptr;
		}
	}
	// case 2 : 자식이 하나인 노드의 경우
	else if (nullptr == n->left || nullptr == n->right)
	{
		// 삭제할 노드의 자식이 있는 곳의 노드를 받아온다.
		NODE* child = (nullptr != n->left) ? n->left : n->right;
		// 지울 노드가 루트 노드라면 child로 루트노드를 대신한다.
		if (m_Root == n)
			m_Root = child;
		else
		{
			// 삭제할 노드가 부모의 왼쪽 자식 노드라면 왼쪽 자식 노드를 child로 대신한다.
			// 혹은 오른쪽 자식 노드라면 오른쪽 자식 노드를 child로 대신한다.
			if (n == p->left)
				p->left = child;
			else
				p->right = child;
		}
	}
	// case 3 : 자식이 둘인 노드의 경우
	else
	{
		// 후계자 노드의 부모노드 childParent
		// 후계자 노드 child
		NODE* childParent = n;
		NODE* child = n->right;

		// 최적의 후계자 노드를 찾기 위해 
		// 오른쪽 서브트리의 가장 왼쪽 노드를 찾는다.
		while (nullptr != child->left)
		{
			childParent = child;
			child = child->left;
		}

		// 후계자 노드의 부모 노드의 왼쪽에 위치한다면 
		// 그 위치에 후계자 노드의 오른쪽 노드를 대신한다.
		// 오른쪽에 위치한다면 그곳을 대신한다.
		if (child == childParent->left)
			childParent->left = child->right;
		else
			childParent->right = child->right;

		// 지울 노드 위치의 데이터를 후계자 노드의 데이터로 복사한다.
		n->data = child->data;
		// 대체가 완료되었으므로 이제 불필요한 후계자 노드를 지운다.
		n = child;
	}
	// 지울 노드를 동적할당 해제한다.
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
	// 모두 삭제
	// 후위순회 순으로 삭제한다
	if (nullptr == root)
		return;

	ClearAll(root->left);
	ClearAll(root->right);
	SAFE_DELETE(root);
}
