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

// 이 함수는 이 프로그램을 사용하여 고맙다는 표현을 출력하는 함수로 샘플 실행의 내용을 포함하여도 괜찮음
void greeting();

// 이 함수는 사용자에게 입력 파일명을 요구하고, 입력 파일의 데이터를 2번에 있는 구조로 만드는 함수임.
// 즉, theInventory를 만드는 함수
int readDatabase(INVENTORY* inventory[]);

// 이 함수는 사용자 메뉴를 출력하는 함수로 사용자의 choice를 리턴함. 샘플 실행을 참조할 것
char printMenu();

// 재고를 출력하는 함수로 저자의 정렬 순으로 출력하며 저자별로는 책 제목 순으로 정렬된 정보를 출력해줌
int displayInventory(INVENTORY* inventory[]);

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
			// 파일의 끝이면 전체 루프 탈출
			if (feof(fp))
				break;

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
						inven->head = (INVENTORY*)malloc(sizeof(INVENTORY));
						inven->head->book_name = NULL;
						inven->head->nextBook = info;
						inven->tail = info;
						break;
					}

					// 중복 이름 체크
					if (!strcmp(inventory[idx]->first_name, inven->first_name) &&
						!strcmp(inventory[idx]->last_name, inven->last_name))
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

			// 확인을 위해 읽은 문자 하나씩 출력
			printf("%c", tmpChar);

			// 줄 끝까지 혹은 쉼표에 다다를때 (,나 개행이 나올때)
			if ((tmpChar == ',') || (tmpChar == '\n'))
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
	printf("\n\n Load Complete!\n");
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

	// 책의 갯수를 구함
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
	//		// inventory[i]의 last name이 [j]의 것 보다 문자열이 더 크므로
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
				// inventory[i]의 last name이 [j]의 것 보다 문자열이 더 크므로
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

	// 둘이 붙어있는 경우
	BOOKINFO* tempSN = (*dst)->nextBook;
	BOOKINFO* tempDN = (*src);
	tempDst->nextBook = tempDN;
	tempSrc->nextBook = tempSN;

	// 떨어진 경우는 나중에 따로 처리

	(*srcPrev)->nextBook = tempDst;
	(*dstPrev)->nextBook = tempSrc;




	//// 노드 정렬 문제
	//// dstPrev -> dst(=srcPrev) -> src 인 경우 dstPrev -> src(=srcPrev) -> dst 순서로 변경됨

	//// dstPrev->next가 src를 가리키도록 변경.
	//dstPrev->nextBook = *src;

	//// srcPrev가 src를 가리키도록 변경
	//*srcPrev = *src;

	//// dst와 src 교환
	//BOOKINFO* tmp = *dst;
	//*dst = *src;
	//*src = tmp;

	//// src->next는 dst->next를 가리키도록 변경, dst->next는 src를 가리키도록 변경.
	//(*src)->nextBook = (*dst)->nextBook;
	//(*dst)->nextBook = *src;
	
	return TRUE;
}
