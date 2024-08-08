#pragma once
#include <iostream>
#include <Windows.h>
#include <vector>
#include "Key.h"

extern double TestX;
extern double TestY;

class SoundManager;

/// 구조체 Key.h에 있는 KeyState값을 가져온다
struct tKeyInfo
{
	KeyState estate;

	// 이전 프레임에 눌린 상태였나
	bool ePrevPush;
};


/// 본격적인 Key매니저 시작
class KeyManager
{
	// 싱글톤형태로 만들기 위해  
	// 생성자 소멸자를 private에 선언해둔다
private:
	KeyManager();
	~KeyManager();

	// vector안에 키의 상태정보랑, 
	// 이전 프레임에 눌렸는지를 확인하는 bool 변수를 넣어둔다
	std::vector<tKeyInfo> m_vecKey;

	SoundManager* m_pSoundManager;
public:
	// 싱글톤
	static KeyManager& GetInstance();

	// 초기화
	void Initialize();

	// 업데이트
	void Update();

	// 키값을 받아와 그 키의 현재 상태를 나타내는 함수
	/// 키 값/상태
	KeyState GetKeyAndState(Key _eKey);

	// 스페이스를 누르면 리턴
	int GetKnittingKey();

};

