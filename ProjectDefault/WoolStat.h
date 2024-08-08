#pragma once

/// 실 종류
enum class WoolType
{
	// 임시로 써둔것
	SOFT,
	NORMAL,
	HARD,
	ROUGH,
};

enum class WoolSpcAbility
{
	ELASTICITY,		//탄력
	STIFF,			//뻣뻣
	SOFTNESS,		//부드러움
	HAIRLOSS,		//털빠짐
	LIGHTNESS,		//가벼움
	ROUGH,			//까끌
	NONE,			//없음
};

/// 실의 능력치
enum class WoolState
{
	// 보온성
	WARMTH,

	// 흡수성
	ABSORPTIVITY,
	
	// 통기성
	AERATION,

	// 가격
	PRICE,
};