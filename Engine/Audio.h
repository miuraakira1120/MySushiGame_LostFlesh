#pragma once
#include <string>

//-----------------------------------------------------------
//�T�E���h���Ǘ�����iXAudio�g�p�j
//-----------------------------------------------------------
namespace Audio
{
	//������
	void Initialize();

	/// <summary>
	/// �T�E���h�t�@�C��(.wav�j�����[�h
	/// </summary>
	/// <param name="fileName">�t�@�C����</param>
	/// <param name="loopFlg">�Đ��`��(true�Ŗ������[�v�Afalse�łP�x�̂ݍĐ�)</param>
	/// <param name="svNum">�����ɖ炷�ő吔�i�ȗ��j</param>
	/// <param name="volume">����</param>
	/// <returns>���łɓ������O�̃t�@�C�������[�h�ς݂̏ꍇ�́A�����̃f�[�^�̔ԍ���Ԃ�</returns>
	int Load(std::string fileName, bool loopFlg, float volume, int svNum = 1);

	//�Đ�
	//�����Fhandle	�炵�����T�E���h�̔ԍ�
	void Play(int ID);

	/// <summary>
	/// ����Ă鉹�y�̒�~���s���֐�
	/// </summary>
	/// <param name="ID">�~�߂����T�E���h�̔ԍ�</param>
	void Stop(int ID);

	/// <summary>
	/// �Đ��I���������ǂ����𒲂ׂ�֐�
	/// </summary>
	/// <param name="ID">�m�F�������T�E���h�̔ԍ�</param>
	/// <returns>�I�����Ă�����true</returns>
	bool IsEndPlayBack(int ID);

	/// <summary>
	/// �}�X�^�[�{�����[����ύX����
	/// </summary>
	/// <param name="vol">�ύX��̃}�X�^�[�{�����[��(0����100)</param>
	void SetMasterVolume(float vol);

	//���ׂĊJ��
	void Release();
	void AllRelease();
};
