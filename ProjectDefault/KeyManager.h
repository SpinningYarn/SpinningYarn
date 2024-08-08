#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include "Key.h"

extern double TestX;
extern double TestY;

class SoundManager;

/// ����ü Key.h�� �ִ� KeyState���� �����´�
struct tKeyInfo
{
	KeyState estate;

	// ���� �����ӿ� ���� ���¿���
	bool ePrevPush;
};


/// �������� Key�Ŵ��� ����
class KeyManager
{
	// �̱������·� ����� ����  
	// ������ �Ҹ��ڸ� private�� �����صд�
private:
	KeyManager();
	~KeyManager();

	// vector�ȿ� Ű�� ����������, 
	// ���� �����ӿ� ���ȴ����� Ȯ���ϴ� bool ������ �־�д�
	std::vector<tKeyInfo> m_vecKey;

	SoundManager* m_pSoundManager;
public:
	// �̱���
	static KeyManager& GetInstance();

	// �ʱ�ȭ
	void Initialize();

	// ������Ʈ
	void Update();

	// Ű���� �޾ƿ� �� Ű�� ���� ���¸� ��Ÿ���� �Լ�
	/// Ű ��/����
	KeyState GetKeyAndState(Key _eKey);

	// �����̽��� ������ ����
	int GetKnittingKey();

};

