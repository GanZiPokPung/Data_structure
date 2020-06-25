#include "pch.h"
#include "GraphMatrix.h"

GraphMatrix::GraphMatrix()
{
}

GraphMatrix::~GraphMatrix()
{
	ResetVisited();
}

void GraphMatrix::Initialize()
{
	m_Size = 0;
	for (int i = 0; i < MAX_VTXS; ++i)
	{
		for (int j = 0; j < MAX_VTXS; ++j)
		{
			m_Adj[i][j] = 0;
		}
		m_Visited[i] = 0;
	}
}

void GraphMatrix::Insert(VtxData name)
{
	if (IsFull())
	{
		cout << "Error : �׷��� ������ ���� �ʰ�" << endl;
		exit(-1);
	}
	else
	{
		m_Data[m_Size++] = name;
	}
}

void GraphMatrix::InsertEdgeOneWay(int u, int v, int value)
{
	m_Adj[u][v] = value;
}

void GraphMatrix::InsertEdgeTwoWay(int u, int v, int value)
{
	m_Adj[u][v] = m_Adj[v][u] = value;
}

void GraphMatrix::Print()
{
	cout << "***�׷���(�������)***" << endl;
	cout << "ũ�� : " << m_Size << endl;

	for (int i = 0; i < m_Size; ++i)
	{
		cout << m_Data[i] << "  ";
		for (int j = 0; j < m_Size; ++j)
		{
			cout << " " << m_Adj[i][j];
		}
		cout << endl;
	}
}

void GraphMatrix::BFS(int v)
{
	m_Visited[v] = 1;
	cout << m_Data[v] << "  ";
	m_Queue.push(v);
	while (!m_Queue.empty())
	{
		v = m_Queue.front();
		m_Queue.pop();
		for (int w = 0; w < m_Size; ++w)
		{
			if (m_Adj[v][w] != 0 && m_Visited[w] == 0)
			{
				m_Visited[w] = 1;
				cout << m_Data[w] << "  ";
				m_Queue.push(w);
			}
		}
	}
}

void GraphMatrix::DFS(int v)
{
	m_Visited[v] = 1;
	cout << m_Data[v] << "  ";
	for (int w = 0; w < m_Size; ++w)
	{
		if (m_Adj[v][w] != 0 && m_Visited[w] == 0)
			DFS(w);
	}
}

void GraphMatrix::ResetVisited()
{
	for (int i = 0; i < m_Size; ++i)
	{
		m_Visited[i] = 0;
	}
}
