#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE  1
#define FALSE 0
#define MAX_INVEN 256
#define MAX_STR 64

#define LASTNAME 0
#define FIRSTNAME 1
#define TITLENAME 2
#define QUANTITY 3
#define PRICE 4

typedef struct _tagBookInformation
{
	char* book_name;
	int   quantity;
	float price;
	struct _tagBookInformation* nextBook;
}BOOKINFO;

typedef struct _tagInventory
{
	char* last_name;
	char* first_name;
	BOOKINFO* head;
	BOOKINFO* tail;
}INVENTORY;

// �� �Լ��� �� ���α׷��� ����Ͽ� ���ٴ� ǥ���� ����ϴ� �Լ��� ���� ������ ������ �����Ͽ��� ������
void greeting();

// �� �Լ��� ����ڿ��� �Է� ���ϸ��� �䱸�ϰ�, �Է� ������ �����͸� 2���� �ִ� ������ ����� �Լ���.
// ��, theInventory�� ����� �Լ�
int readDatabase(INVENTORY* inventory[]);

// �� �Լ��� ����� �޴��� ����ϴ� �Լ��� ������� choice�� ������. ���� ������ ������ ��
char printMenu();

// ��� ����ϴ� �Լ��� ������ ���� ������ ����ϸ� ���ں��δ� å ���� ������ ���ĵ� ������ �������
int displayInventory(INVENTORY* inventory[]);

// ����ڿ��� ���ڸ�(last, first name)�� �䱸�ϰ� �� ������ å ������ �������� ���ĵ� ������ �������.
// ���� ����ڰ� ��û�� ���ڰ� ������ ���ٸ� ������ ����� ����� ��
int displayAuthorsWork(INVENTORY* inventory[]);

// ����ڿ��� ���ڸ�, å����, ���, �׸��� å ������ �䱸�ϰ� ���� ���ڰ� �����ϸ�, ���� �� å�� ��� 
// ������ �����ϰ� �̹� ���� �Ѵٸ�, ������ ����� �� �����. ���� ���ڰ� �������� �ʴٸ�, theInventory�� 
// ���ο� ����(���ڸ�)�� �߰��Ǿ� �� ���ڿ� ���� ������ ����Ǿ�� ��
int addBook(INVENTORY* inventory[]);

// ����ڿ��� ���������� �����ϱ� ���� �ʿ��� ������ �̸��� å ������ �䱸�ϰ�, ���� �Ǽ��� �Էµ� ����
// ������ ������ ��. ���� ���ڳ� Ȥ�� å������ �������� ���� ��� ������ ��� �޽��� �ʿ�
int changePrice(INVENTORY* inventory[]);

// �� changePrice�� ���� ����� �ϳ� ������ �ƴ� ����� ������ �ִ� ����� ��. �׻� ���� ������ �Է� �޾ƾ���
int changeQty(INVENTORY* inventory[]);

// ��� �ִ� ��� å�� ������ ����Ͽ� ����� ��
int totalQty(INVENTORY* inventory[]);

// ��� �ִ� ��� å�� ������ �ջ��Ͽ� ����� ��
int calculateTotalAmount(INVENTORY* inventory[]);

int main()
{
	greeting();

	INVENTORY *theInventory[MAX_INVEN] = { NULL };

	readDatabase(theInventory);

	int flag = 1;

	while (flag)
	{
		char choice = printMenu();

		if (choice == '1')
			displayInventory(theInventory);
		else if (choice == '2')
			displayAuthorsWork(theInventory);
		else if (choice == '3')
			addBook(theInventory);
		else if (choice == '4')
			changePrice(theInventory);
		else if (choice == '5')
			changeQty(theInventory);
		else if (choice == '6')
			totalQty(theInventory);
		else if (choice == '7')
			calculateTotalAmount(theInventory);
		else if (choice == '8')
		{
			printf("Thank you for using this program\n");
			flag = 0;
		}
		else
			printf("Invalid choice\n");


	}

	return 0;
}

void greeting()
{
	printf("�ȳ��ϼ���. ���� ���� ���α׷��Դϴ�. �̿����ּż� ����� �����մϴ�.\n");
	system("pause");
	system("cls");
}

int readDatabase(INVENTORY* inventory[])
{
	int idx = 0;

	// �κ��丮 �ʱ�ȭ (���߿� ����� �ɷ� �ٲ����)
	for (idx = 0; idx < MAX_INVEN; idx++)
	{
		inventory[idx] = NULL;
	}

	FILE* fp = NULL;
	char fileName[MAX_STR];
	char basePath[MAX_STR] = "..\\book_management\\";

	// ���ϸ� �Է�
	printf("Enter the name of the file: ? ");
	scanf("%s", fileName);

	// ���� ���� ��Ʈ�� ����
	strcat(basePath, fileName);

	// ������ �д� �������� 
	fp = fopen(basePath, "rt");

	// ���ϸ��� �ٸ��ų� �θ��µ��� ������ ���涧
	if (fp == NULL)
	{
		printf("Error reading data.\n");
		system("pause");
		return FALSE;
	}

	char tmpChar = 0;
	char tmpNum = 0;
	char tmpString[MAX_STR] = { 0 };
	int  tmpType = LASTNAME;

	INVENTORY *inven = NULL;
	BOOKINFO *info = NULL;

	// ���� ������
	// loop
	while (!feof(fp))
	{
		// �۰� �̸��� å������带 ��� inven�� ����� ������ info��
		// �����Ҵ�
		inven = (INVENTORY*)malloc(sizeof(INVENTORY));
		info = (BOOKINFO*)malloc(sizeof(BOOKINFO));

		// ������ �� ������ ����
		while (TRUE)
		{
			// ������ ���̸� ��ü ���� Ż��
			if (feof(fp))
				break;

			// ����(������ �Է°�) ���� �Է��ߴٸ�
			if (tmpType > PRICE)
			{
				info->nextBook = NULL;
				// �ε��� ��ġ üũ
				for (idx = 0; idx < MAX_INVEN; idx++)
				{
					// ���ο� �̸�
					if (inventory[idx] == NULL)
					{
						inven->head = (INVENTORY*)malloc(sizeof(INVENTORY));
						inven->head->book_name = NULL;
						inven->head->nextBook = info;
						inven->tail = info;
						break;
					}

					// �ߺ� �̸� üũ
					if (!strcmp(inventory[idx]->first_name, inven->first_name) &&
						!strcmp(inventory[idx]->last_name, inven->last_name))
					{
						inventory[idx]->tail->nextBook = info;
						inventory[idx]->tail = info;

						// ���ο� ������ ��������
						goto endline;
					}
				}
				// ���ο� ����
				inventory[idx] = inven;

			endline:
				tmpType = LASTNAME;
				break;
			}

			tmpChar = fgetc(fp);

			// Ȯ���� ���� ���� ���� �ϳ��� ���
			printf("%c", tmpChar);

			// �� ������ Ȥ�� ��ǥ�� �ٴٸ��� (,�� ������ ���ö�)
			if ((tmpChar == ',') || (tmpChar == '\n'))
			{
				// ������ ���� ������ �������
				switch (tmpType)
				{
					// ������ �̸�
				case LASTNAME:
					inven->last_name = (char*)malloc(strlen(tmpString) + 1);
					strcpy(inven->last_name, tmpString);
					break;
					// ó�� �̸�
				case FIRSTNAME:
					inven->first_name = (char*)malloc(strlen(tmpString) + 1);
					strcpy(inven->first_name, tmpString);
					break;
					// å �̸�
				case TITLENAME:
					info->book_name = (char*)malloc(strlen(tmpString) + 1);
					strcpy(info->book_name, tmpString);
					break;
					// ����
				case QUANTITY:
					info->quantity = atoi(tmpString);
					break;
					// ����
				case PRICE:
					info->price = atof(tmpString);
					break;
				default:
					return FALSE;
				}

				// �ٽ� �������� �� �ʱ�ȭ
				tmpChar = 0;
				tmpNum = 0;
				for (idx = 0; idx < MAX_STR; idx++)
					tmpString[idx] = 0;
				tmpType++;
			}
			else
			{
				tmpString[tmpNum] = tmpChar;
				tmpNum++;
			}
		}
	}

	fclose(fp);
	printf("\n\n Load Complete!\n");
	system("pause");
	return TRUE;
}

char printMenu()
{
	char input = "";

	// �Է¹��ۿ� ���� ���͸� ������
	getchar();
	system("cls");
	printf("Enter 1 to display the inventory\n");
	printf("Enter 2 to display the books by one author\n");
	printf("Enter 3 to add a book\n");
	printf("Enter 4 to change the price\n");
	printf("Enter 5 to change the qty on hand\n");
	printf("Enter 6 to view the total number of books in the inventory\n");
	printf("Enter 7 to see the total amount of the entire inventory\n");
	printf("Enter 8 to exit\n");

	printf("Enter your choice: ");
	scanf("%c", &input);

	return input;
}

int displayInventory(INVENTORY * inventory[])
{
	int i = 0;
	int j = 0;

	sortInven(inventory);
	for (i = 0; inventory[i] != NULL; i++)
	{
		sortBook(inventory[i]);
	}
	
	for (i = 0; inventory[i] != NULL; i++)
	{
		printf("The author is: %s, %s\n\n", inventory[i]->last_name, inventory[i]->first_name);

		BOOKINFO* bookRef = inventory[i]->head;
		while (bookRef != NULL)
		{
			printf("\n----\n");
			printf("\t"); printf("The title is: %s\n", bookRef->book_name);
			printf("\t"); printf("The qty is: %d\n", bookRef->quantity);
			printf("\t"); printf("The price is: %f\n", bookRef->price);
			bookRef = bookRef->nextBook;
		}

		printf("\n");
	}

	system("pause");
	return TRUE;
}

int displayAuthorsWork(INVENTORY * inventory[])
{
	return 0;
}

int addBook(INVENTORY * inventory[])
{
	return 0;
}

int changePrice(INVENTORY * inventory[])
{
	return 0;
}

int changeQty(INVENTORY * inventory[])
{
	return 0;
}

int totalQty(INVENTORY * inventory[])
{
	return 0;
}

int calculateTotalAmount(INVENTORY * inventory[])
{
	return 0;
}

int sortInven(INVENTORY * inventory[])
{
	int i = 0;
	int j = 0;
	int invenSize = 0;

	// ���� ���� ����� ����
	for (i = 0; i < MAX_INVEN; i++)
	{
		if (inventory[i] == NULL)
			break;
		invenSize++;
	}

	for (i = 0; i < invenSize - 1; i++)
	{
		for (j = 0; j < invenSize - 1 - i; j++)
		{
			// inventory[i]�� last name�� [j]�� �� ���� ���ڿ��� �� ũ�Ƿ�
			if (strcmp(inventory[j]->last_name, inventory[j + 1]->last_name) > 0)
			{
				swapInvenPointer(&inventory[j], &inventory[j + 1]);
				//swapInven(inventory[j], inventory[j + 1]);
			}
		}
	}

	return TRUE;
}

int removeInvenElement(INVENTORY* remove)
{
	free(remove->first_name);
	remove->first_name = NULL;
	free(remove->last_name);
	remove->last_name = NULL;
}

int swapInvenPointer(INVENTORY** a, INVENTORY** b)
{
	INVENTORY* tmp = *a;
	*a = *b;
	*b = tmp;
}

int sortBook(INVENTORY * inventory)
{
	int i = 0;
	int j = 0;
	int bookCount = 0;

	BOOKINFO* bookRef = inventory->head;
	BOOKINFO* prevDst = NULL;

	// å�� ������ ����
	while (bookRef != NULL)
	{
		bookRef = bookRef->nextBook;
		bookCount++;
	}

	//for (i = 0; i < bookCount - 1; i++)
	//{
	//	bookRef = inventory->head;
	//	for (j = 0; j < bookCount - 1 - i; j++)
	//	{
	//		// inventory[i]�� last name�� [j]�� �� ���� ���ڿ��� �� ũ�Ƿ�
	//		if (strcmp((bookRef->nextBook->book_name), (bookRef->nextBook->nextBook->book_name)) > 0)
	//		{
	//			swapBook(&bookRef, &(bookRef->nextBook), &(bookRef->nextBook), &(bookRef->nextBook->nextBook));
	//		}

	//		bookRef = bookRef->nextBook;
	//	}
	//	inventory->tail = bookRef;
	//}

	for (i = 0; i < bookCount - 1; i++)
		{
			bookRef = inventory->head;
			for (j = 0; j < bookCount - 1 - i; j++)
			{
				// inventory[i]�� last name�� [j]�� �� ���� ���ڿ��� �� ũ�Ƿ�
				if (strcmp((bookRef->nextBook->book_name), (bookRef->nextBook->nextBook->book_name)) > 0)
				{
					swapBook(&bookRef, &(bookRef->nextBook), &(bookRef->nextBook), &(bookRef->nextBook->nextBook));
				}

				bookRef = bookRef->nextBook;
			}
			inventory->tail = bookRef;
		}

	return TRUE;
}
// null s s e
int swapBook(BOOKINFO** srcPrev, BOOKINFO** src, BOOKINFO** dstPrev, BOOKINFO** dst)
{
	//
	BOOKINFO* tempSrc = (*srcPrev)->nextBook;
	//
	BOOKINFO* tempDst = (*dstPrev)->nextBook;

	// ���� �پ��ִ� ���
	BOOKINFO* tempSN = (*dst)->nextBook;
	BOOKINFO* tempDN = (*src);
	tempDst->nextBook = tempDN;
	tempSrc->nextBook = tempSN;

	// ������ ���� ���߿� ���� ó��

	(*srcPrev)->nextBook = tempDst;
	(*dstPrev)->nextBook = tempSrc;




	//// ��� ���� ����
	//// dstPrev -> dst(=srcPrev) -> src �� ��� dstPrev -> src(=srcPrev) -> dst ������ �����

	//// dstPrev->next�� src�� ����Ű���� ����.
	//dstPrev->nextBook = *src;

	//// srcPrev�� src�� ����Ű���� ����
	//*srcPrev = *src;

	//// dst�� src ��ȯ
	//BOOKINFO* tmp = *dst;
	//*dst = *src;
	//*src = tmp;

	//// src->next�� dst->next�� ����Ű���� ����, dst->next�� src�� ����Ű���� ����.
	//(*src)->nextBook = (*dst)->nextBook;
	//(*dst)->nextBook = *src;
	
	return TRUE;
}
