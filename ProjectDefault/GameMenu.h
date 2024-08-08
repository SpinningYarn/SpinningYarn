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
	//�������̽�
	float m_iconSrcX;				//������ ��ǥ
	float m_iconSrcY;
	float m_iconDstX;
	float m_iconDstY;

	float m_containerSrcX;			//�޴� ȭ�� ��ü�ڽ� ��ǥ
	float m_containerSrcY;
	float m_containerDstX;
	float m_containerDstY;

	float m_menuBoxSrcX;			//�޴� ���α�� ��ư ��ǥ
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
	bool m_isActivated;				//Ȱ��ȭ ����
	bool m_isPlayingHTP;			//���ӹ���� �����ְ� �ִ���

	HowtoPlay* m_howToPlay;
	Shop* m_pShop;
	Inventory* m_pInventory;
private:

};
