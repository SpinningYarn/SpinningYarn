#pragma once

/// 키 값들
// 나중에 필요한 키 값들 추가할 수 있다
enum class Key
{
	// 방향키
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

	// 마우스
	

	NUM_OF_KEY,
};


/// 키의 상태
enum class KeyState
{
	NONE,		// 안눌려 있는 상태
	TAP,		// 막 눌린 시점
	HOLD,		// 계속 눌린 상태
	AWAY,		// 막 뗀 시점

};