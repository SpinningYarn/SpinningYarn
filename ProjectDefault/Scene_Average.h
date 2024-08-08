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
/// Ű���� �����̽��ٸ� �����鼭,  ���콺 ��/��Ŭ���� ������ �ϴ� ������ ���� ��
/// ���� ��ȹ�ڸ� �������״ٸ� �� Ŭ����
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

	//void PrintImage();		// �κ��丮�� �ִ� �������� Ŭ���ϸ� �̹����ڽ��� �������� ���� ����
	void PrintStat();
	
	void GetAverage();
	void CalcAveragePrice();	// �ҵ� ��հ� ���

	void StopWhen1stZero();
	void StopWhen2ndZero();

	void InactivateButton();

	int GetAverageWarmth();			//��հ� ��ȯ
	int GetAverageDurability();
	int GetAveragePermeability();
	int GetAveragePrice();
	int GetSum();

	void UpdateCurrentSpc();
	bool isStiff();
	bool isRough();
	bool isSoftness();

	// Ȯ����ư
	void Confirm();

	void ResetInfos();
	void ResetShopInven();
	void ToStage2();

	void UpdateShopAndCredits();
	
	// 1��° �ڽ��� ������Ʈ�� ��� ������ true�� �ǰ� true�϶� 2��° �ڽ��� ���� �Ѵ� 
	bool changeBox;
	// ��� �ڽ����� ������Ʈ�� �� ������ true�� ����� ��չڽ��� ����ϰ� �����
	bool averageCheck;

	bool MouseClickOnce;

private:
	int count;

	int m_averageWarmth;		//��� ���¼�
	int m_averageDurability;	//��� ������
	int m_averagePermeability;	//��� ��⼺
	int m_averagePrice;			//��հ���
	int m_sumEA;				//���� �ջ�
	bool m_CatOut;				//����� ����
	double m_CatTimer;			//���� �ִϸ��̼� �ѹ��� �ϰ� �ϱ� ���� Ÿ�̸�

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

	//����
	SpiderWeb* m_pSpiderWeb;
	LambsWool* m_pLambsWool;
	Cotton* m_pCotton;
	Burlap* m_pBurlap;
	Angora* m_pAngora;
	Cashmere* m_pCashmere;
	vector<IWool*> m_iwools;
};