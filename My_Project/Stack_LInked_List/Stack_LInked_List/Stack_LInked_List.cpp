#include "pch.h"
#include "LinkedListStack.h"
#include "Stack_Util_Reverse.h"

int main()
{
	Stack_Util_Reverse stack;
	char test[100] = "((A*B)/C)-{(D+E)&&(F-G)}";
	/*char* Reverse = stack.ReverseString(test);
	printf("%s\n", Reverse);*/

	bool check = stack.CheckBracketMatching(test);
	if (check)
		cout << "RIGHT!" << endl;
	else
		cout << "WRONG!" << endl;
}