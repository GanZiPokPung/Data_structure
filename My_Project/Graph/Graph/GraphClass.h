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
	void InsertEdgeTwoWay(int u, int v, int value);
	void InsertEdgeOneWay(int u, int v, int value);

	void Print();

private:
	int m_Adj[MAX_VTXS][MAX_VTXS];
	int m_Size = 0;
	VtxData m_Data[MAX_VTXS];
};

