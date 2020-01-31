#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayList.h"
#include "NameCard.h"

int main()
{
	////3-1
	//List  list;
	//LData data;
	//LData dataRemove;
	//int sumResult = 0;
	//int result = TRUE;
	//ListInit(&list);

	//for (int i = 1; i <= 10; i++)
	//{
	//	LInsert(&list, i);
	//}

	//result = LFirst(&list, &data);
	//if (result == FALSE)
	//	return -1;
	//
	//while (result != FALSE)
	//{
	//	sumResult += data;
	//	result = LNext(&list, &data);
	//}
	//
	//printf("%d\n", sumResult);

	//result = LFirst(&list, &data);
	//if (result == FALSE)
	//	return -1;
	//result = TRUE;

	//while (result != FALSE)
	//{
	//	if ((data % 3 == 0) || (data % 2 == 0))
	//	{
	//		dataRemove = LRemove(&list);
	//	}
	//	result = LNext(&list, &data);
	//}

	//result = LFirst(&list, &data);
	//if (result == FALSE)
	//	return -1;
	//result = TRUE;

	//while (result != FALSE)
	//{
	//	printf("%d ", data);
	//	result = LNext(&list, &data);
	//}

	//3-2
	List list;
	NameCard* card;
	LData data;
	
	ListInit(&list);

	card = MakeNameCard("Kim", "010-0000-0000");
	LInsert(&list, card);
	
	card = MakeNameCard("Lee", "010-1111-1111");
	LInsert(&list, card);
	
	card = MakeNameCard("Park", "010-2222-2222");
	LInsert(&list, card);

	if (LFirst(&list, &data))
	{
		if (NameCompare(data, "Kim") == TRUE)
		{
			printf("이름 : %s   번호 : %s\n", data->name, data->phone);
		}

		while (LNext(&list, &data))
		{
			if (NameCompare(data, "Kim") == TRUE)
			{
				printf("이름 : %s   번호 : %s\n", data->name, data->phone);
			}
		}
	}

	if (LFirst(&list, &data))
	{
		if (NameCompare(data, "Lee") == TRUE)
		{
			ChangePhoneNum(data, "010-1234-1234");
		}

		while (LNext(&list, &data))
		{
			if (NameCompare(data, "Lee") == TRUE)
			{
				ChangePhoneNum(data, "010-1234-1234");
			}
		}
	}

	if (LFirst(&list, &data))
	{
		if (NameCompare(data, "Park") == TRUE)
		{
			NameCard* tempCard = LRemove(&list);
			free(tempCard);
		}

		while (LNext(&list, &data))
		{
			if (NameCompare(data, "Park") == TRUE)
			{
				NameCard* tempCard = LRemove(&list);
				free(tempCard);
			}
		}
	}

	if (LFirst(&list, &data))
	{
		printf("이름 : %s   번호 : %s\n", data->name, data->phone);

		while (LNext(&list, &data))
		{	
			printf("이름 : %s   번호 : %s\n", data->name, data->phone);
		}
	}

	

	return 0;
}

NameCard * MakeNameCard(char * name, char * phone)
{
	NameCard *alloc = (NameCard*)malloc(sizeof(NameCard));
	strcpy_s(alloc->name, sizeof(alloc->name), name);
	strcpy_s(alloc->phone, sizeof(alloc->phone), phone);
	return alloc;
}

void ShowNameCardInfo(NameCard * pcard)
{
	printf("\n------------------------\n");
	printf("이름 : %s\n전화번호 : %s\n", pcard->name, pcard->phone);
	printf("\n------------------------\n");
}

int NameCompare(NameCard * pcard, char * name)
{
	if (!strcmp(pcard->name, name))
		return TRUE;
	else
		return FALSE;
}

void ChangePhoneNum(NameCard * pcard, char * phone)
{
	strcpy_s(pcard->phone, sizeof(pcard->phone), phone);
}
