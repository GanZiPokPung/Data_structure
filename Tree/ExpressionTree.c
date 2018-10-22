#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ListBaseStack.h"
#include "ExpressionTree.h"

BTreeNode * MakeExpTree(char exp[])
{
	Stack stack;
	BTreeNode * pnode;

	int expLen = strlen(exp);
	int i;

	StackInit(&stack);

	// 입력한 길이만큼
	for (i = 0; i < expLen; i++)
	{
		pnode = MakeBTreeNode();

		if (isdigit(exp[i]))		// 문자가 숫자 인지를 판단하는 함수
		{
			SetData(pnode, exp[i]-'0'); // 아스키 코드('0'을 빼서 숫자값이) 저장
		}
		// 문자가 연산기호 일때
		else      
		{
			// 스택에 저장되어있던 숫자를 마지막 값부터 오른쪽 왼쪽 서브 노드로 채운다.
			MakeRightSubTree(pnode, (Data)SPop(&stack));
			MakeLeftSubTree(pnode, (Data)SPop(&stack));
			SetData(pnode, exp[i]);	// 연산기호 아스키 코드 저장
		}

		// 서브 트리를 스택에 저장
		SPush(&stack, pnode);
	}

	return SPop(&stack);
}

int evaluateExpTree(BTreeNode * bt)
{
	int op1, op2;

	if (GetLeftSubTree(bt) == NULL && GetRightSubTree(bt) == NULL)
		return GetData(bt);

	//op1 = GetData(GetLeftSubTree(bt)); // 첫 번째 피연산자
	//op2 = GetData(GetRightSubTree(bt)); // 두 번째 피연산자

	// 재귀를 사용하여 모든 서브트리 계산
	op1 = evaluateExpTree(GetLeftSubTree(bt)); // 첫 번째 서브트리 계산
	op2 = evaluateExpTree(GetRightSubTree(bt)); // 두 번째 서브트리 계산

	switch (GetData(bt))
	{
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	}

	return 0;
}

void ShowNodeData(int data)
{
	if (0 <= data && data <= 9)
		printf("%d ", data);
	else
		printf("%c", data);
}

void ShowPrefixTypeExp(BTreeNode * bt)
{
	PreorderTraverse(bt, ShowNodeData);
}

void ShowInfixTypeExp(BTreeNode * bt)
{
	InorderTraverse(bt, ShowNodeData);
}

void ShowPostfixTypeExp(BTreeNode * bt)
{
	PostorderTraverse(bt, ShowNodeData);
}
