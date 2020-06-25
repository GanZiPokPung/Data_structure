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
	void InsertEdgeOneWay(int u, int v, int value);		// ���� ���� ����
	void InsertEdgeTwoWay(int u, int v, int value);		// ���� ���� ����
	void Print();
	
	void BFS(int v);
	void DFS(int v);
	void ResetVisited();
private:
	int m_Adj[MAX_VTXS][MAX_VTXS];		// �������
	int m_Size = 0;						// ��ü ������ ����
	VtxData m_Data[MAX_VTXS];			// ������ ������ ������ �迭
	int m_Visited[MAX_VTXS];
	queue<int> m_Queue;
};

