#pragma once

enum class eStageObjectDefine
{
	/// 주문 물품
	Doll,			// 인형
	Muffler,		// 목도리
	Bag,			// 가방
	Gloves,			// 장갑
	Sweater,		// 스웨터

	/// 섬유 특수 스탯
	Elasticity,		// 탄력
	Stiff,			// 뻣뻣
	Softness,		// 부드러움
	HairLoss,		// 털빠짐
	Lightness,		// 가벼움
	Rough,			// 까끌거림
	NoneSpecial		// 특수상태 없음
};