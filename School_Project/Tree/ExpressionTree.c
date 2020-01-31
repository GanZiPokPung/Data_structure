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

	// �Է��� ���̸�ŭ
	for (i = 0; i < expLen; i++)
	{
		pnode = MakeBTreeNode();

		if (isdigit(exp[i]))		// ���ڰ� ���� ������ �Ǵ��ϴ� �Լ�
		{
			SetData(pnode, exp[i]-'0'); // �ƽ�Ű �ڵ�('0'�� ���� ���ڰ���) ����
		}
		// ���ڰ� �����ȣ �϶�
		else      
		{
			// ���ÿ� ����Ǿ��ִ� ���ڸ� ������ ������ ������ ���� ���� ���� ä���.
			MakeRightSubTree(pnode, (Data)SPop(&stack));
			MakeLeftSubTree(pnode, (Data)SPop(&stack));
			SetData(pnode, exp[i]);	// �����ȣ �ƽ�Ű �ڵ� ����
		}

		// ���� Ʈ���� ���ÿ� ����
		SPush(&stack, pnode);
	}

	return SPop(&stack);
}

int evaluateExpTree(BTreeNode * bt)
{
	int op1, op2;

	if (GetLeftSubTree(bt) == NULL && GetRightSubTree(bt) == NULL)
		return GetData(bt);

	//op1 = GetData(GetLeftSubTree(bt)); // ù ��° �ǿ�����
	//op2 = GetData(GetRightSubTree(bt)); // �� ��° �ǿ�����

	// ��͸� ����Ͽ� ��� ����Ʈ�� ���
	op1 = evaluateExpTree(GetLeftSubTree(bt)); // ù ��° ����Ʈ�� ���
	op2 = evaluateExpTree(GetRightSubTree(bt)); // �� ��° ����Ʈ�� ���

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
