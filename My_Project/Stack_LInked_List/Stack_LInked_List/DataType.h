#pragma once

typedef struct _tagNodeInfo
{
	int				Data;
	_tagNodeInfo*	Link;
}NODE;

typedef struct _tagLinkedListStack
{
	int				ElementCount;
	int				Type;
	NODE*			Top;
}LLSTACK;

// �ǿ�����
const int operand = 1;
// ���� ��ȣ
const int lparen = 2;
// �ݴ� ��ȣ
const int rparen = 3;
