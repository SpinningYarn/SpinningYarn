#pragma once

#include "IScene.h"
#include "../D2DEngine/D2DEngine.h"

class MouseManager;
class SpinningWheel;
class SpinningCenterPoint;
class SpinningOrderMemo;
class SpinningGaugeManager;
class StageManager;

class Shop;
class Inventory;
class Credit;
class GameMenu;

class IWool;
class SpiderWeb;
class LambsWool;
class Cotton;
class Burlap;
class Angora;
class Cashmere;
class Scene_Knitting;

/// <summary>
/// 물레 씬
/// 
/// 마우스 휠을 돌리면 물레가 돌아간다.
/// 만약, 3바퀴 이상을 돌리면 씬 클리어
/// 
/// 2023.02.06 YJHAll
/// </summary>
class Scene_Spinning : public IScene
{
public:
	Scene_Spinning(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager);
	virtual ~Scene_Spinning();

	virtual void UpdateScene() override;
	virtual void RenderScene() override;
	virtual void Initialize() override;

	void UpdateRotation();
	void UpdateShopAndCredits();
	void UpdateWrongCount();
	// 물레 씬에서만 있어야 하는 (리소스)
	
private:
	int SpinningCount;

	// 시간관련
	float m_AnimationTime;		// 애니메이션 Time
	float m_SpriteTime;			// 스프라이트 Time
	float m_AnimGaugeBallTime;	// Ball 애니메이션 Time
	float m_AnimGaugeBallTime2;		// Ball 애니메이션 Time
	float m_GaugeBallTime3;		// Ball 애니메이션 Time

	// 애니메이션
	bool m_OnSucessFlag;		// 성공 시 이미지 출력
	bool m_OnSucessFlag1;		// 성공 시 이미지 출력
	bool m_OnFailFlag;			// 실패 시 이미지 출력
	bool m_OnFailFlag1;			// 실패 시 이미지 출력
	bool m_OutSucessFlag;		// 시간 끝나면 이미지 비활성
	bool m_OutFailFlag;			// 시간 끝나면 이미지 비활성

	bool m_OnGaugeBall1;		// 1초 버틸 시 애니메이션 활성
	bool m_OnGaugeBall2;		// 2초 버틸 시 애니메이션 활성
	bool m_OnGaugeBall3;		// 3초 버틸 시 애니메이션 활성
	bool m_OnGaugeBall4;		// 4초 버틸 시 애니메이션 활성
	bool m_OutGaugeBall1;		// 1초 지날 시 애니메이션 비활성
	bool m_OutGaugeBall2;		// 2초 지날 시 애니메이션 비활성
	bool m_OutGaugeBall3;		// 3초 지날 시 애니메이션 비활성

private:
	///SomeResource* m_pResource;

	MouseManager* m_pMouserManager;
	D2DEngine* m_pD2DEngine;

	SpinningWheel* m_pWheel;
	SpinningCenterPoint* m_pCenterPoint;
	SpinningOrderMemo* m_pSpinningOrderMemo;
	SpinningGaugeManager* m_SpinningGaugeManager;
	StageManager* m_pStageManager;

private:
	Shop* m_pShop;
	Inventory* m_pInventory;
	Credit* m_pCredit;
	GameMenu* m_pGameMenu;

private:
	//재료들
	SpiderWeb* m_pSpiderWeb;
	LambsWool* m_pLambsWool;
	Cotton* m_pCotton;
	Burlap* m_pBurlap;
	Angora* m_pAngora;
	Cashmere* m_pCashmere;
	vector<IWool*> m_iwools;
	Scene_Knitting* m_pKntting;
};

