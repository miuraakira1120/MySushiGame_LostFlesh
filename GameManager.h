#pragma once

class Pause;

namespace GameManager
{
	/// <summary>
	/// ‰Šú‰»
	/// </summary>
	void Initialize();

	/// <summary>
	/// XV
	/// </summary>
	void Update();

	/// <summary>
	/// •`‰æ
	/// </summary>
	void Draw();

	//‰ğ•ú
	void Release();

	/// <summary>
	/// ŠÔ‚ª“®‚¢‚Ä‚¢‚é‚©
	/// </summary>
	/// <returns></returns>
	bool GetIsTimeMoving();
	
	/// <summary>
	/// ŠÔ‚ğ“®‚©‚·‚©‚Ç‚¤‚©
	/// </summary>
	/// <param name="flag"></param>
	void SetTimeMoving(bool flag);

	/// <summary>
	/// ŠÔ‚ª“®‚¢‚Ä‚¢‚½‚ç’â~‚µA~‚Ü‚Á‚Ä‚¢‚½‚ç“®‚©‚·
	/// </summary>
	void TimeMovingReverse();

	/// <summary>
	/// Pause‚ÌêŠ‚Ìİ’è
	/// </summary>
	/// <param name="pos"></param>
	void SetPausePos(XMFLOAT3 pos);
};

