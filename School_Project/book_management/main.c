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

// 이 함수는 이 프로그램을 사용하여 고맙다는 표현을 출력하는 함수로 샘플 실행의 내용을 포함하여도 괜찮음
void greeting();

// 이 함수는 사용자에게 입력 파일명을 요구하고, 입력 파일의 데이터를 2번에 있는 구조로 만드는 함수임.
// 즉, theInventory를 만드는 함수
int readDatabase(INVENTORY* inventory[]);

// 이 함수는 사용자 메뉴를 출력하는 함수로 사용자의 choice를 리턴함. 샘플 실행을 참조할 것
char printMenu();

// 재고를 출력하는 함수로 저자의 정렬 순으로 출력하며 저자별로는 책 제목 순으로 정렬된 정보를 출력해줌
int displayInventory(INVENTORY* inventory_origin[]);

// 사용자에게 저자명(last, first name)을 요구하고 그 저자의 책 정보를 제목으로 정렬된 순으로 출력해줌.
// 만약 사용자가 요청한 저자가 정보에 없다면 적절한 출력을 해줘야 함
int displayAuthorsWork(INVENTORY* inventory[]);

// 사용자에게 저자명, 책제목, 재고량, 그리고 책 가격을 요구하고 만약 저자가 존재하면, 만약 새 책을 경우 
// 정보를 저장하고 이미 존재 한다면, 적절한 출력을 해 줘야함. 만약 저자가 존재하지 않다면, theInventory에 
// 새로운 원소(저자명)가 추가되어 그 저자에 대한 정보로 저장되어야 함
int addBook(INVENTORY* inventory[]);

// 사용자에게 가격정보를 변경하기 위해 필요한 저자의 이름과 책 제목을 요구하고, 양의 실수로 입력될 때만
// 가격을 변경해 줌. 만약 저자나 혹은 책제목이 존재하지 않을 경우 적절한 출력 메시지 필요
int changePrice(INVENTORY* inventory[]);

// 위 changePrice와 같은 기능을 하나 가격이 아닌 재고량을 변경해 주는 기능을 함. 항상 양의 정수를 입력 받아야함
int changeQty(INVENTORY* inventory[]);

// 재고에 있는 모든 책의 개수를 계산하여 출력해 줌
int totalQty(INVENTORY* inventory[]);

// 재고에 있는 모든 책의 가격을 합산하여 출력해 줌
int calculateTotalAmount(INVENTORY* inventory[]);

/// 편의성을 위해 새로 추가한 함수

// 인벤토리를 정렬해준다.
int sortInven(INVENTORY * inventory[]);
// 인벤토리끼리 스왑해준다.
int swapInven(INVENTORY** a, INVENTORY** b);
// 작가의 책을 정렬해준다.
int sortBook(INVENTORY * inventory);
// 책끼리 스왑해준다.
int swapBook(BOOKINFO** srcPrev, BOOKINFO** src, BOOKINFO** dstPrev, BOOKINFO** dst);
// 인벤토리를 출력해준다.
int printInven(INVENTORY* inventory);
// 인벤토리에 있는 값들을 지워준다.
int removeInvenElement(INVENTORY* remove);
// 모든 데이타를 지운다.
int clearAll(INVENTORY* clear[]);
// 대문자, 소문자 구분없이 검사를 위함
int checkString(char* dst, char* src);
// qty값 입력
int inputQty();
// price값 입력
float inputPrice();
// 단어의 앞 문자가 항상 대문자로 오도록 바꿔줌
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
			// 종료시 인벤토리에 있는 모든 정보를 할당해제한다.
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
	printf("안녕하세요. 서적 관리 프로그램입니다. 이용해주셔서 대단히 감사합니다.\n");
	system("pause");
	system("cls");
}

int readDatabase(INVENTORY* inventory[])
{
	int idx = 0;

	// 인벤토리 초기화 (나중에 지우는 걸로 바꿔야함)
	for (idx = 0; idx < MAX_INVEN; idx++)
	{
		inventory[idx] = NULL;
	}

	FILE* fp = NULL;
	char fileName[MAX_STR];
	char basePath[MAX_STR] = "..\\book_management\\";

	// 파일명 입력
	printf("Enter the name of the file: ? ");
	scanf("%s", fileName);

	// 원래 파일 루트와 연결
	strcat(basePath, fileName);

	// 파일을 읽는 형식으로 
	fp = fopen(basePath, "rt");

	// 파일명이 다르거나 부르는데에 문제가 생길때
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

	// 파일 끝까지
	// loop
	while (!feof(fp))
	{
		// 작가 이름과 책정보노드를 담는 inven과 노드의 내용인 info를
		// 동적할당
		inven = (INVENTORY*)malloc(sizeof(INVENTORY));
		info = (BOOKINFO*)malloc(sizeof(BOOKINFO));

		// 파일의 줄 끝까지 루프
		while (TRUE)
		{
			//// 파일의 끝이면 전체 루프 탈출
			//if (feof(fp))
			//	break;

			// 가격(마지막 입력값) 까지 입력했다면
			if (tmpType > PRICE)
			{
				info->nextBook = NULL;
				// 인덱스 위치 체크
				for (idx = 0; idx < MAX_INVEN; idx++)
				{
					// 새로운 이름
					if (inventory[idx] == NULL)
					{
						inven->head = (BOOKINFO*)malloc(sizeof(BOOKINFO));
						inven->head->book_name = NULL;
						inven->head->nextBook = info;
						inven->tail = info;
						break;
					}

					// 중복 이름 체크
					if (checkString(inventory[idx]->first_name, inven->first_name) &&
						checkString(inventory[idx]->last_name, inven->last_name))
					{
						inventory[idx]->tail->nextBook = info;
						inventory[idx]->tail = info;

						// 새로운 삽입을 막기위함
						goto endline;
					}
				}
				// 새로운 삽입
				inventory[idx] = inven;

			endline:
				tmpType = LASTNAME;
				break;
			}

			tmpChar = fgetc(fp);

			// 줄 끝까지 혹은 쉼표에 다다를때 (,나 개행이 나올때)(또는 파일의 끝일때)
			if ((tmpChar == ',') ||
				(tmpChar == '\n') ||
				feof(fp))
			{
				// 삽입을 위한 정보를 집어넣음
				switch (tmpType)
				{
					// 마지막 이름
				case LASTNAME:
					inven->last_name = (char*)malloc(strlen(tmpString) + 1);
					strcpy(inven->last_name, tmpString);
					break;
					// 처음 이름
				case FIRSTNAME:
					inven->first_name = (char*)malloc(strlen(tmpString) + 1);
					strcpy(inven->first_name, tmpString);
					break;
					// 책 이름
				case TITLENAME:
					info->book_name = (char*)malloc(strlen(tmpString) + 1);
					strcpy(info->book_name, tmpString);
					break;
					// 수량
				case QUANTITY:
					info->quantity = atoi(tmpString);
					break;
					// 가격
				case PRICE:
					info->price = atof(tmpString);
					break;
				default:
					return FALSE;
				}

				// 다시 쓰기위해 값 초기화
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

	// 입력버퍼에 들어온 엔터를 없애줌
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
	// 정렬 출력을 위한 임시 inventory
	INVENTORY* inventory[MAX_INVEN] = { 0 };

	int i = 0;
	int j = 0;

	// 매개변수로 받은 값을 복사해온다.
	for (i = 0; inventory_origin[i] != NULL; i++)
	{
		inventory[i] = (INVENTORY*)malloc(sizeof(INVENTORY));
		memcpy(inventory[i], inventory_origin[i], sizeof(INVENTORY));
	}

	// 작가 이름순 정렬
	sortInven(inventory);

	// 작가의 책 이름순 정렬
	for (i = 0; inventory[i] != NULL; i++)
	{
		sortBook(inventory[i]);
	}
	
	// 정렬된 후의 내용을 보여준다.
	for (i = 0; inventory[i] != NULL; i++)
	{
		printInven(inventory[i]);
	}

	// 정렬 출력을 위해 사용한 임시 inventory 삭제
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

	// 작가 이름 입력
	printf("Enter the author's first name: ");
	scanf("%s", authorFirstName);
	printf("Enter the author's last name: ");
	scanf("%s", authorLastName);

	for (i = 0;  inventory[i] != NULL; i++)
	{
		// 데이타베이스에 같은 작가가 있는지 확인
		if (checkString(authorFirstName, inventory[i]->first_name) &&
			checkString(authorLastName, inventory[i]->last_name))
		{
			// 있으면 작가의 책 목록을 출력한다.

			// 출력만을 위한 인벤토리 변수를 동적할당 한다.
			INVENTORY* tempInven = (INVENTORY*)malloc(sizeof(INVENTORY));
			memcpy(tempInven, inventory[i], sizeof(INVENTORY));

			// 책 제목별 정렬
			sortBook(tempInven);

			// 책 목록 출력
			printInven(tempInven);

			// 출력 후 동적할당 해제
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
	
	// 작가 이름 입력
	printf("Enter the author's first name: ");
	scanf("%s", authorFirstName);
	printf("Enter the author's last name: ");
	scanf("%s", authorLastName);

	// 입력 버퍼를 비워준다.
	FFLUSH;

	// 책 제목 입력
	printf("Enter the title: ");
	// scanset character를 이용하여 개행이 있을때까지 값을 입력받음
	scanf("%[^\n]s", bookTitle);

	// 양식에 맞는 문자로 변경 (앞문자에만 대문자)
	changeCharArrToBase(authorFirstName);
	changeCharArrToBase(authorLastName);
	changeCharArrToBase(bookTitle);

	// 중복 체크
	for (invenIdx = 0; inventory[invenIdx] != NULL; invenIdx++)
	{
		// 작가 이름 중복 검사
		if (checkString(authorFirstName, inventory[invenIdx]->first_name) &&
			checkString(authorLastName, inventory[invenIdx]->last_name))
		{
			printf("The author already exist. Searching the book...\n");
			// 작가가 이미 존재할 경우
			// 책 중복 검사
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
			// 책 추가
			// 수량
			quantity = inputQty();
			// 가격
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
	
	// 작가가 데이터베이스에 존재하지 않다면..

	// 수량
	quantity = inputQty();
	// 가격
	price = inputPrice();

	// 작가, 책 추가
	inventory[invenIdx] = (INVENTORY*)malloc(sizeof(INVENTORY));

	// 작가 이름
	inventory[invenIdx]->first_name = (char*)malloc(strlen(authorFirstName) + 1);
	strcpy(inventory[invenIdx]->first_name, authorFirstName);
	inventory[invenIdx]->last_name = (char*)malloc(strlen(authorLastName) + 1);
	strcpy(inventory[invenIdx]->last_name, authorLastName);

	BOOKINFO* newBook = (BOOKINFO*)malloc(sizeof(BOOKINFO));

	// 책 정보
	newBook->nextBook = NULL;
	newBook->book_name = (char*)malloc(strlen(bookTitle) + 1);
	strcpy(newBook->book_name, bookTitle);
	newBook->quantity = quantity;
	newBook->price = price;

	// 헤드를 가리키는 더미노드를 만든다.
	inventory[invenIdx]->head = (BOOKINFO*)malloc(sizeof(BOOKINFO));
	inventory[invenIdx]->head->book_name = NULL;

	// 더미노드 다음 노드가 할당한 책 정보를 가리키게 한다.
	inventory[invenIdx]->head->nextBook = newBook;
	// 테일이 새 책 정보를 가리킨다.
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

	// 작가 이름 입력
	printf("Enter the author's first name: ");
	scanf("%s", authorFirstName);
	printf("Enter the author's last name: ");
	scanf("%s", authorLastName);

	for (i = 0; inventory[i] != NULL; i++)
	{
		if (checkString(authorFirstName, inventory[i]->first_name) &&
			checkString(authorLastName, inventory[i]->last_name))
		{
			// 작가 이름 존재시

			// 입력 버퍼를 비워준다.
			FFLUSH;

			// 책 제목 입력
			printf("Enter the title: ");
			// scanset character를 이용하여 개행이 있을때까지 값을 입력받음
			scanf("%[^\n]s", bookTitle);

			BOOKINFO *searchRef = inventory[i]->head->nextBook;
			while (searchRef != NULL)
			{
				if (checkString(bookTitle, searchRef->book_name))
				{
					// 가격
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

	// 작가 이름 입력
	printf("Enter the author's first name: ");
	scanf("%s", authorFirstName);
	printf("Enter the author's last name: ");
	scanf("%s", authorLastName);

	for (i = 0; inventory[i] != NULL; i++)
	{
		if (checkString(authorFirstName, inventory[i]->first_name) &&
			checkString(authorLastName, inventory[i]->last_name))
		{
			// 작가 이름 존재시
			// 입력 버퍼를 비워준다.
			FFLUSH;

			// 책 제목 입력
			printf("Enter the title: ");
			// scanset character를 이용하여 개행이 있을때까지 값을 입력받음
			scanf("%[^\n]s", bookTitle);

			BOOKINFO *searchRef = inventory[i]->head->nextBook;
			while (searchRef != NULL)
			{
				if (checkString(bookTitle, searchRef->book_name))
				{
					// 수량
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
	
	// 데이타 베이스를 순회돌며 가진 책 정보에서 수량만 totalNum에 더해준다.
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

	// 데이타 베이스를 순회돌며 가진 책 정보에서 가격만 totalNum에 더해준다.
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

	// 실제 정보 사이즈를 구함
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
			// inventory[i]의 last name이 [j]의 것 보다 문자열이 더 크므로
			if (stricmp(inventory[j]->last_name, inventory[j + 1]->last_name) > 0)
			{
				swapInven(&inventory[j], &inventory[j + 1]);
			}
			// last name이 서로 같을 경우
			else if (!stricmp(inventory[j]->last_name, inventory[j + 1]->last_name))
			{
				// first name을 비교한다.
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
	// 인벤토리 구조체에서 할당된 모든 원소들을 해제한다.
	free(remove->first_name);
	remove->first_name = NULL;
	free(remove->last_name);
	remove->last_name = NULL;

	// 책 정보는 tail까지 순회돌며 해제한다.
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
	// 순회돌며 모든 데이타 베이스를 동적할당한다.
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
	// 단순한 주소값 스왑
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

	// 책의 갯수를 구함
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
				// inventory[i]의 last name이 [j]의 것 보다 문자열이 더 크므로
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

	// 붙어있는 노드의 경우만 스왑 가능

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
	// 인벤토리 정보 출력
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
	// 대, 소문자 상관없이 문자열을 검사한다.
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
			// 숫자로만 이루어져 있는지 검사한다.
			if (quantityInput[i] < '0' || quantityInput[i] > '9')
			{
				++errorCheck;
			}
		}

		// 숫자외 문자 아스키코드 존재시 다시 입력
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
			// 숫자로만 이루어져 있는지 검사한다.
			if (priceInput[i] < '0' || priceInput[i] > '9')
			{
				// 실수 표현을 위한 .이 있는지 검사한다.
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
				// .이 포함된 후 숫자인 문자일때
				if (pointCheck == 1)
				{
					++rangeCheck;
				}
			}
		}

		// .이 없거나 숫자로만 이루어져 있지 않을 경우
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

	// 문자열 맨 앞 대문자 변경
	if (arr[0] >= 'a' && arr[0] <= 'z')
	{
		arr[0] -= 32;
	}

	++i;

	while (arr[i] != '\0')
	{
		// 각 문장의 앞글자가 대문자이므로
		// 공백 아스키코드일 경우
		if (arr[i] == ' ')
		{
			// initialCheck를 TRUE
			initialCheck = TRUE;
		}
		else if (arr[i] >= 'A' && arr[i] <= 'Z')
		{
			// 만약 앞글자가 공백이면서 대문자인 경우
			// 그대로 놔둠
			if (initialCheck == TRUE)
				initialCheck = FALSE;
			else
				arr[i] += 32;
		}
		else
		{
			if (initialCheck == TRUE)
			{
				// 만약 앞글자가 공백이면서 소문자인 경우
				// 대문자로 변경
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
