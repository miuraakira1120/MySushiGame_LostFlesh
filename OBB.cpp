#include "OBB.h"

void OBB::SetPos(XMVECTOR position)
{
	pos = position;
}

void OBB::SetNormalDirect(XMVECTOR direct1, XMVECTOR direct2, XMVECTOR direct3)
{
	normalDirect[0] = direct1;
	normalDirect[1] = direct2;
	normalDirect[2] = direct3;
}

void OBB::SetLength(float length1, float length2, float length3)
{
	fLength[0] = length1;
	fLength[1] = length2;
	fLength[2] = length3;
}

void OBB::SetOBBAll(XMVECTOR position, XMVECTOR direct1, XMVECTOR direct2, XMVECTOR direct3, float length1, float length2, float length3)
{
	pos = position;

	normalDirect[0] = direct1;
	normalDirect[1] = direct2;
	normalDirect[2] = direct3;

	fLength[0] = length1;
	fLength[1] = length2;
	fLength[2] = length3;
}

XMVECTOR OBB::GetDirect(int elem)
{
	switch (elem)
	{
	case 0:
		return normalDirect[0];
	case 1:
		return normalDirect[1];
	case 2:
		return normalDirect[2];
	default:
		return {0,0,0};
	}
}

float OBB::GetLen_W(int elem)
{
	switch (elem)
	{
	case 0:
		return fLength[0];
	case 1:
		return fLength[1];
	case 2:
		return fLength[2];
	default:
		return 0;
	}
}

XMVECTOR OBB::GetPos_W()
{
	return pos;
}

