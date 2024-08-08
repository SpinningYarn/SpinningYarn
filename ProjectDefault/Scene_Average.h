#pragma once
#include "IScene.h"
#include "WoolStat.h"
#include <iostream>
//#include "common.h"
using namespace std;

class StageManager;
class MouseManager;
class Inventory;
class Shop;
class Credit;
class GameMenu;

class IWool;
class SpiderWeb;
class LambsWool;
class Cotton;
class Burlap;
class Angora;
class Cashmere;

class StatBox;
class StatBox2;

/// <summary>
/// 키보드 스페이스바를 누르면서,  마우스 좌/우클릭을 적절히 하는 복잡한 게임 씬
/// 뭔가 기획자를 만족시켰다면 씬 클리어
/// </summary>

class Scene_Average : public IScene
{
private:


public:
	Scene_Average(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager);
	virtual ~Scene_Average();

	virtual void UpdateScene() override;
	virtual void RenderScene() override;
	virtual void Initialize() override;

	//void PrintImage();		// 인벤토리에 있는 아이콘을 클릭하면 이미지박스에 아이콘을 띄우는 역할
	void PrintStat();
	
	void GetAverage();
	void CalcAveragePrice();	// 소득 평균값 계산

	void StopWhen1stZero();
	void StopWhen2ndZero();

	void InactivateButton();

	int GetAverageWarmth();			//평균값 반환
	int GetAverageDurability();
	int GetAveragePermeability();
	int GetAveragePrice();
	int GetSum();

	void UpdateCurrentSpc();
	bool isStiff();
	bool isRough();
	bool isSoftness();

	// 확정버튼
	void Confirm();

	void ResetInfos();
	void ResetShopInven();
	void ToStage2();

	void UpdateShopAndCredits();
	
	// 1번째 박스에 오브젝트가 들어 있으면 true가 되고 true일때 2번째 박스에 들어가게 한다 
	bool changeBox;
	// 어느 박스에나 오브젝트가 들어가 있으면 true로 만들고 평균박스에 출력하게 만든다
	bool averageCheck;

	bool MouseClickOnce;

private:
	int count;

	int m_averageWarmth;		//평균 보온성
	int m_averageDurability;	//평균 내구성
	int m_averagePermeability;	//평균 통기성
	int m_averagePrice;			//평균가격
	int m_sumEA;				//개수 합산
	bool m_CatOut;				//고양이 퇴장
	double m_CatTimer;			//퇴장 애니메이션 한번만 하게 하기 위한 타이머

	WoolSpcAbility m_currentSpc1;
	WoolSpcAbility m_currentSpc2;
	WoolSpcAbility m_currentSpc3;
	WoolSpcAbility m_currentSpc4;

	StatBox* m_pStatBox;
	StatBox2* m_pStatBox2;

	StageManager* m_pStageManager;
	MouseManager* m_pMouseManager;
	Inventory* m_pInventory;
	Shop* m_pShop;
	Credit* m_pCredit;
	GameMenu* m_pGameMenu;

	//재료들
	SpiderWeb* m_pSpiderWeb;
	LambsWool* m_pLambsWool;
	Cotton* m_pCotton;
	Burlap* m_pBurlap;
	Angora* m_pAngora;
	Cashmere* m_pCashmere;
	vector<IWool*> m_iwools;
};