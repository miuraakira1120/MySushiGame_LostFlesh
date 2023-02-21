#include "OBB.h"

XMVECTOR OBB::GetDirect(int elem)
{
	switch (elem)
	{
	case 0:
		return NormaDirect[0];
	case 1:
		return NormaDirect[1];
	case 2:
		return NormaDirect[2];
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
	return Pos;
}

