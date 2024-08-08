#pragma once
/// 공통으로 쓰이는 헤더를 모아놓음

#include <vector>
#include <string>

#define BACKGROUND_ORDER 0
#define UI_ORDER 10
#define OBJECT_ORDER 20
#define KNITTING_ORDER 21
#define CAT_ORDER 30
#define SHOP_ORDER 50

// nullptr이 아닐 때 Release해주는 함수 
// 이거 없으면 ㅁㅁㅁ가 nullptr이었습니다 오류가 떠서 체온이 오른다
// 근데 진짜 그게 nullptr이어서 문제가 생기는 경우일 땐 버그 못잡는다
// 그 경우엔 Release로 바꿔서해보던지 알잘딱
template<class Interface>
inline void SafeRelease(Interface** ppInterfaceToRelease)
{
	if (*ppInterfaceToRelease != NULL)
	{
		(*ppInterfaceToRelease)->Release();

		(*ppInterfaceToRelease) = NULL;
	}
}