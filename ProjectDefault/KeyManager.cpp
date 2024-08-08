#include "KeyManager.h"
#include "TimerManager.h"
#include "SoundManager.h"

/// �������� AsyncKeyState ���� ����
// ���߿� �ʿ��� Ű ���� �߰��� �� �ִ�
int g_arrVK[(int)Key::NUM_OF_KEY] =
{
	// ����Ű
	VK_LEFT,
	VK_RIGHT,
	VK_UP,
	VK_DOWN,

	'A',
	'W',
	'S',
	'D',
	VK_SPACE,
	'R',
	'P',
	'M'
	// ���콺 Ŭ��
};

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

// �̱���
KeyManager& KeyManager::GetInstance()
{
	static KeyManager keyManager;

	return keyManager;
}


/// �ʱ�ȭ
void KeyManager::Initialize()
{
	// Key ��/���� vector �ʱ�ȭ
	for (int i = 0; i < (int)Key::NUM_OF_KEY; ++i)
	{
		// ���� : NONE / �������ӿ� ������ �������� �ʱ�ȭ
		m_vecKey.push_back(tKeyInfo{ KeyState::NONE, false });
	}
}


/// Ű �Է� ������Ʈ
void KeyManager::Update()
{
	for (int i = 0; i < (int)Key::NUM_OF_KEY; ++i)
	{
		// �ش� Ű�� ���� ���� �ִٸ�
		if (GetAsyncKeyState(g_arrVK[i]) & 0x0001)
		{
			// ���������� O, ���� O
			if (m_vecKey[i].ePrevPush)
			{
				m_vecKey[i].estate = KeyState::HOLD;
			}
			// ���������� X, ���� O
			else
			{
				m_vecKey[i].estate = KeyState::TAP;
			}

			m_vecKey[i].ePrevPush = true;
		}
		else
		{
			// ���������� O, ���� X
			if (m_vecKey[i].ePrevPush)
			{
				m_vecKey[i].estate = KeyState::AWAY;
			}
			// ���������� X, ���� X
			else
			{
				m_vecKey[i].estate = KeyState::NONE;
			}

			m_vecKey[i].ePrevPush = false;
		}
	}
	if (KeyManager::GetInstance().GetKeyAndState(Key::LEFT) == KeyState::TAP)
	{
		TestX -= 100.0f * TimerManager::GetInstance().GetDeltaTime();
	}
	if (KeyManager::GetInstance().GetKeyAndState(Key::RIGHT) == KeyState::TAP)
	{
		TestX += 100.0f * TimerManager::GetInstance().GetDeltaTime();
	}
	if (KeyManager::GetInstance().GetKeyAndState(Key::UP) == KeyState::TAP)
	{
		TestY -= 100.0f * TimerManager::GetInstance().GetDeltaTime();
	}
	if (KeyManager::GetInstance().GetKeyAndState(Key::DOWN) == KeyState::TAP)
	{
		TestY += 100.0f * TimerManager::GetInstance().GetDeltaTime();
	}
}

/// Ű�� ��/���¸� ��ȯ�ϴ� �Լ�
KeyState KeyManager::GetKeyAndState(Key _eKey)
{
	return m_vecKey[(int)_eKey].estate;
}

int KeyManager::GetKnittingKey()
{
	if (KeyManager::GetInstance().GetKeyAndState(Key::W) == KeyState::TAP)
	{
		return 1;
	}
	else if (KeyManager::GetInstance().GetKeyAndState(Key::UP) == KeyState::TAP)
	{
		return 1;
	}
	else if (KeyManager::GetInstance().GetKeyAndState(Key::S) == KeyState::TAP)
	{
		return 2;
	}
	else if (KeyManager::GetInstance().GetKeyAndState(Key::DOWN) == KeyState::TAP)
	{
		return 2;
	}
	else if (KeyManager::GetInstance().GetKeyAndState(Key::A) == KeyState::TAP)
	{
		return 3;
	}
	else if (KeyManager::GetInstance().GetKeyAndState(Key::LEFT) == KeyState::TAP)
	{
		return 3;
	}
	else if (KeyManager::GetInstance().GetKeyAndState(Key::D) == KeyState::TAP)
	{
		return 4;
	}
	else if (KeyManager::GetInstance().GetKeyAndState(Key::RIGHT) == KeyState::TAP)
	{
		return 4;
	}
	else if (KeyManager::GetInstance().GetKeyAndState(Key::SPACE) == KeyState::TAP)
	{
		return 5;
	}
	else if (KeyManager::GetInstance().GetKeyAndState(Key::R) == KeyState::TAP)
	{
		return 6;
	}
	else if (KeyManager::GetInstance().GetKeyAndState(Key::P) == KeyState::TAP)
	{
		return 7;
	}
}


