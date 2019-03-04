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

#define FFLUSH while(getchar() != '\n')

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
int displayInventory(INVENTORY* inventory_origin[]);

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

/// ���Ǽ��� ���� ���� �߰��� �Լ�

// �κ��丮�� �������ش�.
int sortInven(INVENTORY * inventory[]);
// �κ��丮���� �������ش�.
int swapInven(INVENTORY** a, INVENTORY** b);
// �۰��� å�� �������ش�.
int sortBook(INVENTORY * inventory);
// å���� �������ش�.
int swapBook(BOOKINFO** srcPrev, BOOKINFO** src, BOOKINFO** dstPrev, BOOKINFO** dst);
// �κ��丮�� ������ش�.
int printInven(INVENTORY* inventory);
// �κ��丮�� �ִ� ������ �����ش�.
int removeInvenElement(INVENTORY* remove);
// ��� ����Ÿ�� �����.
int clearAll(INVENTORY* clear[]);
// �빮��, �ҹ��� ���о��� �˻縦 ����
int checkString(char* dst, char* src);
// qty�� �Է�
int inputQty();
// price�� �Է�
float inputPrice();
// �ܾ��� �� ���ڰ� �׻� �빮�ڷ� ������ �ٲ���
int changeCharArrToBase(char *arr);


int main()
{
	int check = FALSE;
	greeting();

	INVENTORY *theInventory[MAX_INVEN] = { NULL };

	while (check == FALSE)
	{
		check = readDatabase(theInventory);
	}
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
			// ����� �κ��丮�� �ִ� ��� ������ �Ҵ������Ѵ�.
			clearAll(theInventory);
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
		printf("Error reading database.\n");
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
			//// ������ ���̸� ��ü ���� Ż��
			//if (feof(fp))
			//	break;

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
						inven->head = (BOOKINFO*)malloc(sizeof(BOOKINFO));
						inven->head->book_name = NULL;
						inven->head->nextBook = info;
						inven->tail = info;
						break;
					}

					// �ߺ� �̸� üũ
					if (checkString(inventory[idx]->first_name, inven->first_name) &&
						checkString(inventory[idx]->last_name, inven->last_name))
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

			// �� ������ Ȥ�� ��ǥ�� �ٴٸ��� (,�� ������ ���ö�)(�Ǵ� ������ ���϶�)
			if ((tmpChar == ',') ||
				(tmpChar == '\n') ||
				feof(fp))
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
	printf("\n\nLoad Complete!\n");
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

int displayInventory(INVENTORY * inventory_origin[])
{
	// ���� ����� ���� �ӽ� inventory
	INVENTORY* inventory[MAX_INVEN] = { 0 };

	int i = 0;
	int j = 0;

	// �Ű������� ���� ���� �����ؿ´�.
	for (i = 0; inventory_origin[i] != NULL; i++)
	{
		inventory[i] = (INVENTORY*)malloc(sizeof(INVENTORY));
		memcpy(inventory[i], inventory_origin[i], sizeof(INVENTORY));
	}

	// �۰� �̸��� ����
	sortInven(inventory);

	// �۰��� å �̸��� ����
	for (i = 0; inventory[i] != NULL; i++)
	{
		sortBook(inventory[i]);
	}
	
	// ���ĵ� ���� ������ �����ش�.
	for (i = 0; inventory[i] != NULL; i++)
	{
		printInven(inventory[i]);
	}

	// ���� ����� ���� ����� �ӽ� inventory ����
	for (i = 0; inventory[i] != NULL; i++)
	{
		free(inventory[i]);
		inventory[i] = NULL;
	}

	system("pause");
	return TRUE;
}

int displayAuthorsWork(INVENTORY * inventory[])
{
	int i = 0;
	char authorFirstName[MAX_STR];
	char authorLastName[MAX_STR];

	// �۰� �̸� �Է�
	printf("Enter the author's first name: ");
	scanf("%s", authorFirstName);
	printf("Enter the author's last name: ");
	scanf("%s", authorLastName);

	for (i = 0;  inventory[i] != NULL; i++)
	{
		// ����Ÿ���̽��� ���� �۰��� �ִ��� Ȯ��
		if (checkString(authorFirstName, inventory[i]->first_name) &&
			checkString(authorLastName, inventory[i]->last_name))
		{
			// ������ �۰��� å ����� ����Ѵ�.

			// ��¸��� ���� �κ��丮 ������ �����Ҵ� �Ѵ�.
			INVENTORY* tempInven = (INVENTORY*)malloc(sizeof(INVENTORY));
			memcpy(tempInven, inventory[i], sizeof(INVENTORY));

			// å ���� ����
			sortBook(tempInven);

			// å ��� ���
			printInven(tempInven);

			// ��� �� �����Ҵ� ����
			free(tempInven);
			tempInven = NULL;
			system("pause");
			return TRUE;
		}
	}

	printf("Sorry, but no books by %s, %s in the inventory.\n", authorLastName, authorFirstName);

	
	system("pause");
	return FALSE;
}

int addBook(INVENTORY * inventory[])
{
	int invenIdx = 0;
	int i = 0;

	char authorFirstName[MAX_STR];
	char authorLastName[MAX_STR];
	char bookTitle[MAX_STR];
	int quantity = 0;
	float price = 0.f;
	
	// �۰� �̸� �Է�
	printf("Enter the author's first name: ");
	scanf("%s", authorFirstName);
	printf("Enter the author's last name: ");
	scanf("%s", authorLastName);

	// �Է� ���۸� ����ش�.
	FFLUSH;

	// å ���� �Է�
	printf("Enter the title: ");
	// scanset character�� �̿��Ͽ� ������ ���������� ���� �Է¹���
	scanf("%[^\n]s", bookTitle);

	// ��Ŀ� �´� ���ڷ� ���� (�չ��ڿ��� �빮��)
	changeCharArrToBase(authorFirstName);
	changeCharArrToBase(authorLastName);
	changeCharArrToBase(bookTitle);

	// �ߺ� üũ
	for (invenIdx = 0; inventory[invenIdx] != NULL; invenIdx++)
	{
		// �۰� �̸� �ߺ� �˻�
		if (checkString(authorFirstName, inventory[invenIdx]->first_name) &&
			checkString(authorLastName, inventory[invenIdx]->last_name))
		{
			printf("The author already exist. Searching the book...\n");
			// �۰��� �̹� ������ ���
			// å �ߺ� �˻�
			BOOKINFO *searchRef = inventory[invenIdx]->head->nextBook;
			while (searchRef != NULL)
			{
				if (checkString(bookTitle, searchRef->book_name))
				{
					printf("This book is already in the Inventory and cannot be added again.\n");
					system("pause");
					return FALSE;
				}
				searchRef = searchRef->nextBook;
			}

			printf("You can add the book!\n");
			// å �߰�
			// ����
			quantity = inputQty();
			// ����
			price = inputPrice();


			BOOKINFO* newBook = (BOOKINFO*)malloc(sizeof(BOOKINFO));
			newBook->nextBook = NULL;
			newBook->book_name = (char*)malloc(strlen(bookTitle) + 1);
			strcpy(newBook->book_name, bookTitle);
			newBook->quantity = quantity;
			newBook->price = price;
			inventory[invenIdx]->tail->nextBook = newBook;
			inventory[invenIdx]->tail = newBook;
			printf("Add the book successfully.\n");

			system("pause");

			return TRUE;
		}
	}
	
	// �۰��� �����ͺ��̽��� �������� �ʴٸ�..

	// ����
	quantity = inputQty();
	// ����
	price = inputPrice();

	// �۰�, å �߰�
	inventory[invenIdx] = (INVENTORY*)malloc(sizeof(INVENTORY));

	// �۰� �̸�
	inventory[invenIdx]->first_name = (char*)malloc(strlen(authorFirstName) + 1);
	strcpy(inventory[invenIdx]->first_name, authorFirstName);
	inventory[invenIdx]->last_name = (char*)malloc(strlen(authorLastName) + 1);
	strcpy(inventory[invenIdx]->last_name, authorLastName);

	BOOKINFO* newBook = (BOOKINFO*)malloc(sizeof(BOOKINFO));

	// å ����
	newBook->nextBook = NULL;
	newBook->book_name = (char*)malloc(strlen(bookTitle) + 1);
	strcpy(newBook->book_name, bookTitle);
	newBook->quantity = quantity;
	newBook->price = price;

	// ��带 ����Ű�� ���̳�带 �����.
	inventory[invenIdx]->head = (BOOKINFO*)malloc(sizeof(BOOKINFO));
	inventory[invenIdx]->head->book_name = NULL;

	// ���̳�� ���� ��尡 �Ҵ��� å ������ ����Ű�� �Ѵ�.
	inventory[invenIdx]->head->nextBook = newBook;
	// ������ �� å ������ ����Ų��.
	inventory[invenIdx]->tail = newBook;

	printf("Add the author and the book successfully.\n");

	system("pause");
	return TRUE;
}

int changePrice(INVENTORY * inventory[])
{
	int i = 0;
	char authorFirstName[MAX_STR];
	char authorLastName[MAX_STR];
	char bookTitle[MAX_STR];
	float price = 0.f;

	// �۰� �̸� �Է�
	printf("Enter the author's first name: ");
	scanf("%s", authorFirstName);
	printf("Enter the author's last name: ");
	scanf("%s", authorLastName);

	for (i = 0; inventory[i] != NULL; i++)
	{
		if (checkString(authorFirstName, inventory[i]->first_name) &&
			checkString(authorLastName, inventory[i]->last_name))
		{
			// �۰� �̸� �����

			// �Է� ���۸� ����ش�.
			FFLUSH;

			// å ���� �Է�
			printf("Enter the title: ");
			// scanset character�� �̿��Ͽ� ������ ���������� ���� �Է¹���
			scanf("%[^\n]s", bookTitle);

			BOOKINFO *searchRef = inventory[i]->head->nextBook;
			while (searchRef != NULL)
			{
				if (checkString(bookTitle, searchRef->book_name))
				{
					// ����
					price = inputPrice();
					printf("Price will be updated from %.2f to %.2f\n", searchRef->price, price);
					searchRef->price = price;
					system("pause");
					return TRUE;
				}
				searchRef = searchRef->nextBook;
			}
			
			changeCharArrToBase(bookTitle);
			changeCharArrToBase(authorLastName);
			changeCharArrToBase(authorFirstName);

			printf("No book with in the title %s by %s, %s in your database. So you cannot change the price\n"
				   , bookTitle, authorLastName, authorFirstName);

			system("pause");
			return FALSE;
		}
	}

	printf("No such author in your database. So you cannot change the price\n");

	system("pause");
	return FALSE;
}

int changeQty(INVENTORY * inventory[])
{
	int i = 0;
	char authorFirstName[MAX_STR];
	char authorLastName[MAX_STR];
	char bookTitle[MAX_STR];
	int quantity = 0;

	// �۰� �̸� �Է�
	printf("Enter the author's first name: ");
	scanf("%s", authorFirstName);
	printf("Enter the author's last name: ");
	scanf("%s", authorLastName);

	for (i = 0; inventory[i] != NULL; i++)
	{
		if (checkString(authorFirstName, inventory[i]->first_name) &&
			checkString(authorLastName, inventory[i]->last_name))
		{
			// �۰� �̸� �����
			// �Է� ���۸� ����ش�.
			FFLUSH;

			// å ���� �Է�
			printf("Enter the title: ");
			// scanset character�� �̿��Ͽ� ������ ���������� ���� �Է¹���
			scanf("%[^\n]s", bookTitle);

			BOOKINFO *searchRef = inventory[i]->head->nextBook;
			while (searchRef != NULL)
			{
				if (checkString(bookTitle, searchRef->book_name))
				{
					// ����
					quantity = inputQty();
					printf("Qty will be updated from %d to %d\n", searchRef->quantity, quantity);
					searchRef->quantity = quantity;
					system("pause");
					return TRUE;
				}
				searchRef = searchRef->nextBook;
			}

			changeCharArrToBase(bookTitle);
			changeCharArrToBase(authorLastName);
			changeCharArrToBase(authorFirstName);

			printf("No book with in the title %s by %s, %s in your database. So you cannot change the Qty\n"
				, bookTitle, authorLastName, authorFirstName);

			system("pause");
			return FALSE;
		}
	}

	printf("No such author in your database. So you cannot change the Qty\n");

	system("pause");
	return FALSE;
}

int totalQty(INVENTORY * inventory[])
{
	int i = 0;
	int totalNum = 0;
	
	// ����Ÿ ���̽��� ��ȸ���� ���� å �������� ������ totalNum�� �����ش�.
	for (i = 0; inventory[i] != NULL; i++)
	{
		BOOKINFO *searchRef = inventory[i]->head->nextBook;
		while (searchRef != NULL)
		{
			totalNum += searchRef->quantity;
			searchRef = searchRef->nextBook;
		}
	}

	printf("The total number of books is %d\n", totalNum);
	system("pause");

	return TRUE;
}

int calculateTotalAmount(INVENTORY * inventory[])
{
	int i = 0;
	float totalNum = 0.f;

	// ����Ÿ ���̽��� ��ȸ���� ���� å �������� ���ݸ� totalNum�� �����ش�.
	for (i = 0; inventory[i] != NULL; i++)
	{
		BOOKINFO *searchRef = inventory[i]->head->nextBook;
		while (searchRef != NULL)
		{
			totalNum += searchRef->quantity * searchRef->price;
			searchRef = searchRef->nextBook;
		}
	}

	printf("The total value of the inventory is $%.2f\n", totalNum);
	system("pause");

	return TRUE;
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
			if (stricmp(inventory[j]->last_name, inventory[j + 1]->last_name) > 0)
			{
				swapInven(&inventory[j], &inventory[j + 1]);
			}
			// last name�� ���� ���� ���
			else if (!stricmp(inventory[j]->last_name, inventory[j + 1]->last_name))
			{
				// first name�� ���Ѵ�.
				if (stricmp(inventory[j]->first_name, inventory[j + 1]->first_name) > 0)
				{
					swapInven(&inventory[j], &inventory[j + 1]);
				}
			}
		}
	}

	return TRUE;
}

int removeInvenElement(INVENTORY* remove)
{
	// �κ��丮 ����ü���� �Ҵ�� ��� ���ҵ��� �����Ѵ�.
	free(remove->first_name);
	remove->first_name = NULL;
	free(remove->last_name);
	remove->last_name = NULL;

	// å ������ tail���� ��ȸ���� �����Ѵ�.
	BOOKINFO* searchRef = remove->head;

	while (searchRef != NULL)
	{
		free(searchRef->book_name);
		searchRef->book_name = NULL;
		searchRef = searchRef->nextBook;
	}
}

int clearAll(INVENTORY * clear[])
{
	// ��ȸ���� ��� ����Ÿ ���̽��� �����Ҵ��Ѵ�.
	int i = 0;
	for (i = 0; clear[i] != NULL; i++)
	{
		removeInvenElement(clear[i]);
		free(clear[i]);
		clear[i] = NULL;
	}

	return TRUE;
}

int swapInven(INVENTORY** a, INVENTORY** b)
{
	// �ܼ��� �ּҰ� ����
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

	for (i = 0; i < bookCount - 1; i++)
		{
			bookRef = inventory->head;
			for (j = 0; j < (bookCount - 1) - i - 1; j++)
			{
				// inventory[i]�� last name�� [j]�� �� ���� ���ڿ��� �� ũ�Ƿ�
				if (stricmp((bookRef->nextBook->book_name), (bookRef->nextBook->nextBook->book_name)) > 0)
				{
					swapBook(&bookRef, &(bookRef->nextBook), &(bookRef->nextBook), &(bookRef->nextBook->nextBook));
				}

				bookRef = bookRef->nextBook;
			}
			inventory->tail = bookRef;
		}

	return TRUE;
}

int swapBook(BOOKINFO** srcPrev, BOOKINFO** src, BOOKINFO** dstPrev, BOOKINFO** dst)
{

	// �پ��ִ� ����� ��츸 ���� ����

	//
	BOOKINFO* tempSrc = (*srcPrev)->nextBook;
	//
	BOOKINFO* tempDst = (*dstPrev)->nextBook;

	BOOKINFO* tempSN = (*dst)->nextBook;
	BOOKINFO* tempDN = (*src);
	tempDst->nextBook = tempDN;
	tempSrc->nextBook = tempSN;

	(*srcPrev)->nextBook = tempDst;
	(*dstPrev)->nextBook = tempSrc;
	
	return TRUE;
}

int printInven(INVENTORY * inventory)
{
	// �κ��丮 ���� ���
	printf("The author is: %s, %s\n\n", inventory->last_name, inventory->first_name);

	BOOKINFO* bookRef = inventory->head->nextBook;
	while (bookRef != NULL)
	{
		printf("\n----\n");
		printf("\t"); printf("The title is: %s\n", bookRef->book_name);
		printf("\t"); printf("The qty is: %d\n", bookRef->quantity);
		printf("\t"); printf("The price is: %.2f\n", bookRef->price);
		bookRef = bookRef->nextBook;
	}

	printf("\n");

	return 0;
}

int checkString(char * dst, char * src)
{
	// ��, �ҹ��� ������� ���ڿ��� �˻��Ѵ�.
	if (!stricmp(dst, src))
		return TRUE;
	else
		return FALSE;
}

int inputQty()
{
	int i = 0;
	char quantityInput[MAX_STR];

	while (TRUE)
	{
		int errorCheck = 0;
		printf("Enter the qty: ");
		scanf("%s", quantityInput);

		for (i = 0; i < strlen(quantityInput); i++)
		{
			// ���ڷθ� �̷���� �ִ��� �˻��Ѵ�.
			if (quantityInput[i] < '0' || quantityInput[i] > '9')
			{
				++errorCheck;
			}
		}

		// ���ڿ� ���� �ƽ�Ű�ڵ� ����� �ٽ� �Է�
		if (errorCheck > 0)
		{
			printf("Invalid input for qty.\n");
		}
		else
		{
			return atoi(quantityInput);
		}
	}
}

float inputPrice()
{
	int i = 0;
	char priceInput[MAX_STR];

	while (TRUE)
	{
		int errorCheck = 0;
		int pointCheck = 0;
		int rangeCheck = 0;
		printf("Enter the price: ");
		scanf("%s", priceInput);

		for (i = 0; i < strlen(priceInput); i++)
		{
			// ���ڷθ� �̷���� �ִ��� �˻��Ѵ�.
			if (priceInput[i] < '0' || priceInput[i] > '9')
			{
				// �Ǽ� ǥ���� ���� .�� �ִ��� �˻��Ѵ�.
				if (priceInput[i] == '.')
				{
					++pointCheck;
				}
				else
				{
					++errorCheck;
				}
			}
			else
			{
				// .�� ���Ե� �� ������ �����϶�
				if (pointCheck == 1)
				{
					++rangeCheck;
				}
			}
		}

		// .�� ���ų� ���ڷθ� �̷���� ���� ���� ���
		if (errorCheck > 0 ||
			pointCheck != 1 ||
			rangeCheck > 2)
		{
			printf("Invalid input for price.\n");
		}
		else
		{
			return atof(priceInput);
		}
	}
}

int changeCharArrToBase(char * arr)
{
	int i = 0;
	int initialCheck = FALSE;

	// ���ڿ� �� �� �빮�� ����
	if (arr[0] >= 'a' && arr[0] <= 'z')
	{
		arr[0] -= 32;
	}

	++i;

	while (arr[i] != '\0')
	{
		// �� ������ �ձ��ڰ� �빮���̹Ƿ�
		// ���� �ƽ�Ű�ڵ��� ���
		if (arr[i] == ' ')
		{
			// initialCheck�� TRUE
			initialCheck = TRUE;
		}
		else if (arr[i] >= 'A' && arr[i] <= 'Z')
		{
			// ���� �ձ��ڰ� �����̸鼭 �빮���� ���
			// �״�� ����
			if (initialCheck == TRUE)
				initialCheck = FALSE;
			else
				arr[i] += 32;
		}
		else
		{
			if (initialCheck == TRUE)
			{
				// ���� �ձ��ڰ� �����̸鼭 �ҹ����� ���
				// �빮�ڷ� ����
				if (arr[i] >= 'a' && arr[i] <= 'z')
				{
					arr[i] -= 32;
					initialCheck = FALSE;
				}
			}
		}

		++i;
	}

	return TRUE;
}
