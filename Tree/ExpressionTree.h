#pragma once

#include "BinaryTree.h"

BTreeNode * MakeExpTree(char exp[]);
int evaluateExpTree(BTreeNode* bt);

void ShowPrefixTypeExp(BTreeNode* bt);
void ShowInfixTypeExp(BTreeNode* bt);
void ShowPostfixTypeExp(BTreeNode* bt);