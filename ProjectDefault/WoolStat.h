#pragma once

/// �� ����
enum class WoolType
{
	// �ӽ÷� ��а�
	SOFT,
	NORMAL,
	HARD,
	ROUGH,
};

enum class WoolSpcAbility
{
	ELASTICITY,		//ź��
	STIFF,			//����
	SOFTNESS,		//�ε巯��
	HAIRLOSS,		//�к���
	LIGHTNESS,		//������
	ROUGH,			//���
	NONE,			//����
};

/// ���� �ɷ�ġ
enum class WoolState
{
	// ���¼�
	WARMTH,

	// �����
	ABSORPTIVITY,
	
	// ��⼺
	AERATION,

	// ����
	PRICE,
};