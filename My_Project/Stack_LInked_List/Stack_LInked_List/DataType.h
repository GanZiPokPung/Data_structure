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

// ÇÇ¿¬»êÀÚ
const int operand = 1;
// ¿©´Â °ıÈ£
const int lparen = 2;
// ´İ´Â °ıÈ£
const int rparen = 3;
