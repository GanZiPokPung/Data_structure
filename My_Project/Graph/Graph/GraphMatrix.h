#pragma once

class GraphMatrix
{
public:
	GraphMatrix();
	~GraphMatrix();

public:
	bool IsEmpty() { return (m_Size == 0); }
	bool IsFull() { return (m_Size >= MAX_VTXS); }

public:
	void Initialize();
	void Insert(VtxData name);
	void InsertEdgeOneWay(int u, int v, int value);		// 간선 한쪽 방향
	void InsertEdgeTwoWay(int u, int v, int value);		// 간선 양쪽 방향
	void Print();
	
	void BFS(int v);
	void DFS(int v);
	void ResetVisited();
private:
	int m_Adj[MAX_VTXS][MAX_VTXS];		// 인접행렬
	int m_Size = 0;						// 전체 정점의 개수
	VtxData m_Data[MAX_VTXS];			// 정점에 저장할 데이터 배열
	int m_Visited[MAX_VTXS];
	queue<int> m_Queue;
};

