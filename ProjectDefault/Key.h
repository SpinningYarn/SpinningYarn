#pragma once

/// Ű ����
// ���߿� �ʿ��� Ű ���� �߰��� �� �ִ�
enum class Key
{
	// ����Ű
	LEFT,
	RIGHT,
	UP,
	DOWN,

	A,
	W,
	S,
	D,
	SPACE,
	R,
	P,
	M,

	// ���콺
	

	NUM_OF_KEY,
};


/// Ű�� ����
enum class KeyState
{
	NONE,		// �ȴ��� �ִ� ����
	TAP,		// �� ���� ����
	HOLD,		// ��� ���� ����
	AWAY,		// �� �� ����

};