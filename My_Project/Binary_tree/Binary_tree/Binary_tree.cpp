// Binary_tree.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "BinaryTree.h"

int main()
{
	BinaryTree tree;
	NODE *a, *b, *c, *d, *e, *f, *g;
	NODE* root;

	// 단말 노드
	d = tree.CreateNode('D', nullptr, nullptr);
	f = tree.CreateNode('F', nullptr, nullptr);
	g = tree.CreateNode('G', nullptr, nullptr);
	//
	b = tree.CreateNode('B', d, f);
	c = tree.CreateNode('C', g, nullptr);
	a = tree.CreateNode('A', b, c);
	e = tree.CreateNode('E', nullptr, nullptr);
	root = tree.CreateNode('R', a, e);

	cout << "In-Order : "; tree.InOrder(root); cout << endl;
	cout << "Pre-Order : "; tree.PreOrder(root); cout << endl;
	cout << "Post-Order : "; tree.PostOrder(root); cout << endl;
	cout << "Level-Order : "; tree.LevelOrder(root); cout << endl<< endl;

	cout << "Node-Count : " << tree.CountNode(root); cout << endl;
	cout << "Leaf-Count : " << tree.CountLeaf(root); cout << endl;
	cout << "Max Height : " << tree.CalcHeight(root); cout << endl;
}