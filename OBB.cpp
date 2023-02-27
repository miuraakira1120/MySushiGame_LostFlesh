#include "OBB.h"

void OBB::SetPos(XMVECTOR position)
{
	pos = position;
}

void OBB::SetNormalDirect(std::vector<XMVECTOR> direct)
{
	normalDirect = direct;
}

void OBB::SetLength(std::vector<float> length)
{
	fLength = length;
}

void OBB::SetOBBAll(XMVECTOR position, std::vector<XMVECTOR> direct, std::vector<float> length)
{
	pos = position;
	normalDirect = direct;
	fLength = length;
}

XMVECTOR OBB::GetDirect(int elem)
{
	if (normalDirect.size() > elem && 0 <= elem)
	{
		return normalDirect[elem];
	}
	return XMVectorZero();
}

float OBB::GetLen_W(int elem)
{
	if (fLength.size() > elem && 0 <= elem)
	{
		return fLength[elem];
	}
	return -1;
}

XMVECTOR OBB::GetPos_W()
{
	return pos;
}

