// Graph.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include "GraphMatrix.h"

int main()
{
	GraphMatrix gm;
	gm.Initialize();

	for (int i = 0; i < 8; ++i)
	{
		gm.Insert('A' + i);
	}
	
	// A
	gm.InsertEdgeOneWay(0, 1, 1); gm.InsertEdgeOneWay(0, 2, 1);
	// B
	gm.InsertEdgeOneWay(1, 0, 1); gm.InsertEdgeOneWay(1, 3, 1);
	// C
	gm.InsertEdgeOneWay(2, 0, 1); gm.InsertEdgeOneWay(2, 3, 1);
	gm.InsertEdgeOneWay(2, 4, 1);
	// D
	gm.InsertEdgeOneWay(3, 1, 1); gm.InsertEdgeOneWay(3, 2, 1);
	gm.InsertEdgeOneWay(3, 5, 1);
	// E
	gm.InsertEdgeOneWay(4, 2, 1); gm.InsertEdgeOneWay(4, 6, 1);
	gm.InsertEdgeOneWay(4, 7, 1);
	// F
	gm.InsertEdgeOneWay(5, 3, 1);
	// G
	gm.InsertEdgeOneWay(6, 4, 1); gm.InsertEdgeOneWay(6, 7, 1);
	// H
	gm.InsertEdgeOneWay(7, 4, 1); gm.InsertEdgeOneWay(7, 6, 1);
	
	// BFS A부터 시작
	cout << "BFS ==> ";
	gm.BFS(0);
	cout << endl;

}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
