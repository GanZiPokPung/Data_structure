#include "pch.h"
#include "GraphLinkedList.h"

GraphLinkedList::GraphLinkedList()
{
}

GraphLinkedList::~GraphLinkedList()
{
	Reset();
	ResetVisited();
}

void GraphLinkedList::Initialize()
{
	m_Size = 0;
	for (int i = 0; i < MAX_VTXS; ++i)
	{
		m_Adj[i] = nullptr;
		m_Visited[i] = 0;
	}
}

void GraphLinkedList::Reset()
{
	GNode* n;
	for (int i = 0; i < m_Size; ++i)
	{
		while (m_Adj[i] != nullptr)
		{
			n = m_Adj[i];
			m_Adj[i] = n->link;
			delete n;
			n = nullptr;
		}
	}

	m_Size;
}

void GraphLinkedList::InsertVertex(VtxData name)
{
	if (IsFull())
	{
		cout << "Error : 그래프 정점의 개수 초과" << endl;
		exit(-1);
	}
	else
	{
		m_Data[m_Size++] = name;
	}
}

void GraphLinkedList::InsertEdgeOneWay(int u, int v)
{
	GNode* n = new GNode;
	n->link = m_Adj[u];
	n->id = v;
	m_Adj[u] = n;
}

void GraphLinkedList::Print()
{
	cout << "***그래프(인접리스트)***" << endl;
	cout << "크기 : " << m_Size << endl;

	for (int i = 0; i < m_Size; ++i)
	{
		cout << m_Data[i] << "  ";
		for (GNode* n = m_Adj[i]; n != nullptr; n = n->link)
		{
			cout << " " << m_Data[n->id];
		}
		cout << endl;
	}
}

void GraphLinkedList::BFS(int v)
{
	m_Visited[v] = 1;
	cout << m_Data[v] << "  ";
	m_Queue.push(v);
	while (!m_Queue.empty())
	{
		v = m_Queue.front();
		m_Queue.pop();
		for (GNode* n = m_Adj[v]; n != nullptr; n = n->link)
		{
			if (m_Visited[n->id] == 0)
			{
				m_Visited[n->id] = 1;
				cout << m_Data[n->id] << "  ";
				m_Queue.push(n->id);
			}
		}
	}
}

void GraphLinkedList::DFS(int v)
{
	m_Visited[v] = 1;
	cout << m_Data[v] << "  ";
	for (GNode* n = m_Adj[v]; n != nullptr; n = n->link)
	{
		if (m_Visited[n->id] == 0)
			DFS(n->id);
	}
}

void GraphLinkedList::ResetVisited()
{
	for (int i = 0; i < m_Size; ++i)
	{
		m_Visited[i] = 0;
	}
}
