#pragma once
#include "Object.h"
using namespace std;

class D2DEngine;
class MouseManager;
class SceneManager;
class StageManager;
class Shop;
class Inventory;
class HowtoPlay;

class GameMenu : public Object
{
public:
	GameMenu(const int objectNum, string objectName, SceneManager* pSceneManager);
	GameMenu(const int objectNum, const string& objectName, SceneManager* pSceneManager, const double posX, const double posY);
	~GameMenu();

	virtual void UpdateObject() override;
	virtual void RenderObject() override;

	void OpenMenu();
	void CloseMenu();

	void onClickHowToPlay();
	void ShowHowtoPlay();
	void ReturnToMain();

	bool GetActivated();

private:
	D2DEngine* m_localD2D;
	MouseManager* m_localMouse;
	SceneManager* m_localSceneManager;
	StageManager* m_localStageManager;
	bool m_mouseClickOnce;
private:
	//인터페이스
	float m_iconSrcX;				//아이콘 좌표
	float m_iconSrcY;
	float m_iconDstX;
	float m_iconDstY;

	float m_containerSrcX;			//메뉴 화면 전체박스 좌표
	float m_containerSrcY;
	float m_containerDstX;
	float m_containerDstY;

	float m_menuBoxSrcX;			//메뉴 내부기능 버튼 좌표
	float m_menuBoxSrcY;
	float m_menuBoxDstX;
	float m_menuBoxDstY;

	float m_boxIntervalX;
	float m_boxIntervalY;

	float m_closeButtonSrcX;
	float m_closeButtonSrcY;
	float m_closeButtonDstX;
	float m_closeButtonDstY;

private:
	bool m_isActivated;				//활성화 여부
	bool m_isPlayingHTP;			//게임방법을 보여주고 있는지

	HowtoPlay* m_howToPlay;
	Shop* m_pShop;
	Inventory* m_pInventory;
private:

};
