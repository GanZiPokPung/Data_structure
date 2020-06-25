// Binary_tree.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "AVL_Tree.h"

int main()
{
	AVL_Tree tree;

	cout << "[삽입 연산] : 6 8 9 11 10";
	tree.Insert_AVL(6);
	tree.Insert_AVL(8);
	tree.Insert_AVL(9);
	tree.Insert_AVL(11);
	tree.Insert_AVL(10);

	cout << "\n트리의 높이 = " << tree.CalcHeight(tree.GetRoot()) << endl;

	tree.Search_AVL(10);
	tree.Search_AVL(11);
}