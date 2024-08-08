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
/// ���� ��
/// 
/// ���콺 ���� ������ ������ ���ư���.
/// ����, 3���� �̻��� ������ �� Ŭ����
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
	// ���� �������� �־�� �ϴ� (���ҽ�)
	
private:
	int SpinningCount;

	// �ð�����
	float m_AnimationTime;		// �ִϸ��̼� Time
	float m_SpriteTime;			// ��������Ʈ Time
	float m_AnimGaugeBallTime;	// Ball �ִϸ��̼� Time
	float m_AnimGaugeBallTime2;		// Ball �ִϸ��̼� Time
	float m_GaugeBallTime3;		// Ball �ִϸ��̼� Time

	// �ִϸ��̼�
	bool m_OnSucessFlag;		// ���� �� �̹��� ���
	bool m_OnSucessFlag1;		// ���� �� �̹��� ���
	bool m_OnFailFlag;			// ���� �� �̹��� ���
	bool m_OnFailFlag1;			// ���� �� �̹��� ���
	bool m_OutSucessFlag;		// �ð� ������ �̹��� ��Ȱ��
	bool m_OutFailFlag;			// �ð� ������ �̹��� ��Ȱ��

	bool m_OnGaugeBall1;		// 1�� ��ƿ �� �ִϸ��̼� Ȱ��
	bool m_OnGaugeBall2;		// 2�� ��ƿ �� �ִϸ��̼� Ȱ��
	bool m_OnGaugeBall3;		// 3�� ��ƿ �� �ִϸ��̼� Ȱ��
	bool m_OnGaugeBall4;		// 4�� ��ƿ �� �ִϸ��̼� Ȱ��
	bool m_OutGaugeBall1;		// 1�� ���� �� �ִϸ��̼� ��Ȱ��
	bool m_OutGaugeBall2;		// 2�� ���� �� �ִϸ��̼� ��Ȱ��
	bool m_OutGaugeBall3;		// 3�� ���� �� �ִϸ��̼� ��Ȱ��

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
	//����
	SpiderWeb* m_pSpiderWeb;
	LambsWool* m_pLambsWool;
	Cotton* m_pCotton;
	Burlap* m_pBurlap;
	Angora* m_pAngora;
	Cashmere* m_pCashmere;
	vector<IWool*> m_iwools;
	Scene_Knitting* m_pKntting;
};

