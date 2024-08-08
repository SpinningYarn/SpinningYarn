#pragma once

/// <summary>
/// Spinning Gauge�� ���� ����, ������ �����ϴ� ��
/// 
/// 2023.02.15 KIM
/// </summary>
class SpinningGaugeManager
{
public:
	static SpinningGaugeManager* GetInstance();

private:
	static SpinningGaugeManager* m_pInstance;

private:
	SpinningGaugeManager();
	~SpinningGaugeManager();

private:
	// Gauge Bar Stat
	const int m_MaxGaugeBar = 1200;		// Gauge Bar �ִ� ��ġ
	const int m_Preheat = 180;			// ���� ��ġ (1 ~ 30%)
	const int m_Overload = 541;			// ������ ��ġ (91 ~ 100%)
	const int m_Percent10Gauge = 60;	// 10% �� �Ÿ�
	int m_GaugeBarCount;				// Gauge Bar ī��Ʈ

	// Gauge Bar Pos
	int m_GauageBarPosX;
	int m_GauageBarPosY;

public:
	// Gauge Ball Pos
	int m_GauageBallPosX;
	int m_GauageBallPosY;

private:
	// Gauge count
	int m_GauageNumCount;

	// ���� ������
	float m_RandomGauge;			// ���� �� ����
	int m_RandomGaugeTimeCount;		// ���� ������ 1�ʰ� ī��Ʈ�� ����
	float m_AlphaValue;				// ���� ���� Render ���� ��
	bool m_IsRandomCount;			// ���� ���� ī��Ʈ �Ǵ�

	// �ִϸ��̼� �Ǵ�
	bool m_FailAnimation;
	bool m_SucessAnimation;
	bool m_BallAnimation;

public:
	/// ����
	void SetGauageBarPos(int posX, int posY);	// Gauage Bar ��ǥ ����
	void SetGauageBallPos(int posX, int posY);	// Gauage Ball ��ǥ ����
	void SetRandomPos();		// ���� ��ǥ ���� (������ġ�� ������ġ ���� - 120)
	void SetFailAnimation(bool state);		// ���� Object �ִϸ��̼� ����
	void SetSucessAnimation(bool state);		// ���� Object �ִϸ��̼� ����
	void SetBallAnimation(bool state);		// Ball Object �ִϸ��̼� ����

	/// ��ɵ�
	void CountIncrease(int num);	// Gauge�� �����̰� �Ǵ��� ī��Ʈ �� ����
	void RandomPosCounting();		// ������ǥ�� ������� 1�ʿ� 1����
	void RandomPosCountInit();		// ���� ī���� �ʱ�ȭ
	void RandomIsCountChage(bool isRandom);		// ���� ī��Ʈ ���� ��ȯ
	void RandomGaugeAlphaValue(float value);	// ���� ���� Render ���� ��ȯ
	
	/// ��ȯ
	int GetGauageCount();		// ��� ī��Ʈ�ߴ���
	int GetMaxGaugeBar();		// Gauge �ִ� ũ��
	int GetPreheatSize();		// ���� size
	int GetOverloadSize();		// ���� size
	int GetPercent10Gauge();	// 10% ��ġ
	float GetRandomGaugePosX();	// ���� ��ǥ ��ȯ
	int GetRandomTimeCount();	// ���� Ÿ�� ī��Ʈ ��ȯ
	bool GetRandomIsCount();	// ���� ī��Ʈ ���� ��ȯ
	float GetRandomGaugeAlphaValue();	// ���� ���� Render ���� ��ȯ
	bool IsFailAnimation();			// ���� Object �ִϸ��̼�
	bool IsSucessAnimation();			// ���� Object �ִϸ��̼�
	bool IsBallAnimation();		// Ball Object �ִϸ��̼�
private:
};

