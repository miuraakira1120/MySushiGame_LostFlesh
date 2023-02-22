#include <vector>
#include <DirectXMath.h>
#include <directxmath.h>

using namespace DirectX;

class OBB
{
	XMVECTOR pos;				   // �ʒu
	XMVECTOR normalDirect[3];	   // �����x�N�g��
	float fLength[3];              // �e�������̒���

public:
	void SetPos(XMVECTOR position);
	void SetNormalDirect(XMVECTOR direct1, XMVECTOR direct2, XMVECTOR direct3);
	void SetLength(float length1, float length2, float length3);
	/// <summary>
	/// OBB�̃Z�b�g����C�ɂ��֐�
	/// </summary>
	/// <param name="position">OBB����̈ʒu</param>
	/// <param name="direct1">OBB����̕����x�N�g��</param>
	/// <param name="direct2">OBB����̕����x�N�g��</param>
	/// <param name="direct3">OBB����̕����x�N�g��</param>
	/// <param name="length1">OBB����̕����̒���</param>
	/// <param name="length2">OBB����̕����̒���</param>
	/// <param name="length3">OBB����̕����̒���</param>
	void SetOBBAll(XMVECTOR position, XMVECTOR direct1, XMVECTOR direct2, XMVECTOR direct3, float length1, float length2, float length3);

	XMVECTOR GetDirect(int elem);   // �w�莲�ԍ��̕����x�N�g�����擾
	float GetLen_W(int elem);       // �w�莲�����̒������擾
	XMVECTOR GetPos_W();            // �ʒu���擾
};