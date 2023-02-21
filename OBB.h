#include <vector>
#include <DirectXMath.h>
#include <directxmath.h>

using namespace DirectX;

class OBB
{
	XMVECTOR Pos;				   // �ʒu
	XMVECTOR NormaDirect[3];	   // �����x�N�g��
	float fLength[3];              // �e�������̒���

public:
	XMVECTOR GetDirect(int elem);   // �w�莲�ԍ��̕����x�N�g�����擾
	float GetLen_W(int elem);       // �w�莲�����̒������擾
	XMVECTOR GetPos_W();            // �ʒu���擾
};