#include <stdio.h>
#include "DBLinkedList.h"

int main()
{
	List list;
	Data data;

	ListInit(&list);

	LInsert(&list, 33);
	LInsert(&list, 22);
	LInsert(&list, 11);
	RInsert(&list, 44);
	RInsert(&list, 55);
	RInsert(&list, 66);

	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		while (LNext(&list, &data))
		{
			printf("%d ", data);
		}
	}
	printf("\n");


	if (LFirst(&list, &data))
	{
		if (data == 22 || data == 33)
			LRemove(&list);

		while (LNext(&list, &data))
		{
			if (data == 22 || data == 33)
				LRemove(&list);
		}
	}

	if (LFirst(&list, &data))
	{
		printf("%d ", data);

		while (LNext(&list, &data))
		{
			printf("%d ", data);
		}
	}
	printf("\n");

}