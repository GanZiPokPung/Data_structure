// Practice.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "tree.h"

// ���� Ž�� Ʈ��

int main()
{
	Tree<int> tree(8);
	tree.buildSearchTree();
	//

	cout << "Preorder >> ";
	tree.preorder(tree.getRoot());
	cout << endl;

	tree.insertNode(new TreeNode<int>(4));
	cout << "Preorder >> ";
	tree.preorder(tree.getRoot());
	cout << endl;

	int number;
	cout << "Input number to search >> ";
	cin >> number;

	TreeNode<int>* found = tree.search(tree.getRoot(), number);

	if (found != null)
	{
		cout << "Found node." << endl;
		cout << *found;
	}
	else
	{
		cout << "Not found node." << endl;
	}

    return 0;
}

