#include "KeyManager.h"
#include "TimerManager.h"
#include "SoundManager.h"

/// 전역으로 AsyncKeyState 값들 선언
// 나중에 필요한 키 값들 추가할 수 있다
int g_arrVK[(int)Key::NUM_OF_KEY] =
{
	// 방향키
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
	// 마우스 클릭
};

KeyManager::KeyManager()
{
}

KeyManager::~KeyManager()
{
}

// 싱글톤
KeyManager& KeyManager::GetInstance()
{
	static KeyManager keyManager;

	return keyManager;
}


/// 초기화
void KeyManager::Initialize()
{
	// Key 값/상태 vector 초기화
	for (int i = 0; i < (int)Key::NUM_OF_KEY; ++i)
	{
		// 상태 : NONE / 전프레임에 눌린적 없음으로 초기화
		m_vecKey.push_back(tKeyInfo{ KeyState::NONE, false });
	}
}


/// 키 입력 업데이트
void KeyManager::Update()
{
	for (int i = 0; i < (int)Key::NUM_OF_KEY; ++i)
	{
		// 해당 키가 지금 눌려 있다면
		if (GetAsyncKeyState(g_arrVK[i]) & 0x0001)
		{
			// 이전프레임 O, 현재 O
			if (m_vecKey[i].ePrevPush)
			{
				m_vecKey[i].estate = KeyState::HOLD;
			}
			// 이전프레임 X, 현재 O
			else
			{
				m_vecKey[i].estate = KeyState::TAP;
			}

			m_vecKey[i].ePrevPush = true;
		}
		else
		{
			// 이전프레임 O, 현재 X
			if (m_vecKey[i].ePrevPush)
			{
				m_vecKey[i].estate = KeyState::AWAY;
			}
			// 이전프레임 X, 현재 X
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

/// 키의 값/상태를 반환하는 함수
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


