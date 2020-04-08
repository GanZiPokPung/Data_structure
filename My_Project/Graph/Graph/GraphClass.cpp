#include "pch.h"
#include "GraphMatrix.h"

GraphMatrix::GraphMatrix()
{
}

GraphMatrix::~GraphMatrix()
{
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
	}
}

void GraphMatrix::Insert(VtxData name)
{
}

void GraphMatrix::InsertEdgeTwoWay(int u, int v, int value)
{
}

void GraphMatrix::InsertEdgeOneWay(int u, int v, int value)
{
}
