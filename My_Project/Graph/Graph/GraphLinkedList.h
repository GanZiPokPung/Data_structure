#pragma once
class GraphLinkedList
{
public:
	GraphLinkedList();
	~GraphLinkedList();

public:
	bool IsEmpty() { return (m_Size == 0); }
	bool IsFull() { return (m_Size >= MAX_VTXS); }

public:
	void Initialize();
	void Reset();
	void InsertVertex(VtxData name);
	void InsertEdgeOneWay(int u, int v);
	void Print();

	void BFS(int v);
	void DFS(int v);
	void ResetVisited();
private:
	GNode* m_Adj[MAX_VTXS];
	int m_Size = 0;
	VtxData m_Data[MAX_VTXS];
	int m_Visited[MAX_VTXS];
	queue<int> m_Queue;
};

