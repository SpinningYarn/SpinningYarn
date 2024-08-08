#include "GameMenu.h"
#include "IScene.h"
#include "MouseManager.h"
#include "SceneManager.h"
#include "StageManager.h"
#include "Shop.h"
#include "Inventory.h"
#include "HowtoPlay.h"
#include "../D2DEngine/D2DEngine.h"
#include "SoundManager.h"

GameMenu::GameMenu(const int objectNum, string objectName, SceneManager* pSceneManager)
	:Object(objectNum, objectName),
	m_iconSrcX(30), m_iconSrcY(19), m_iconDstX(158), m_iconDstY(147),
	m_containerSrcX(610), m_containerSrcY(334), m_containerDstX(1310), m_containerDstY(684),
	m_menuBoxSrcX(832), m_menuBoxSrcY(426), m_menuBoxDstX(1310), m_menuBoxDstY(684),
	m_boxIntervalX(0), m_boxIntervalY(129), m_isActivated(false), m_isPlayingHTP(false),
	m_closeButtonSrcX(1180), m_closeButtonSrcY(294), m_closeButtonDstX(1255), m_closeButtonDstY(384),
	m_localD2D(nullptr), m_localMouse(nullptr), m_mouseClickOnce(true),
	m_howToPlay(nullptr), m_localSceneManager(pSceneManager), m_localStageManager(nullptr),
	m_pShop(nullptr), m_pInventory(nullptr)
{
	this->renderOrder = SHOP_ORDER + 1;
	m_localD2D = D2DEngine::GetInstance();
	m_localMouse = MouseManager::GetInstance();
	m_localStageManager = StageManager::GetInstance();

	m_howToPlay = new HowtoPlay(0, "메뉴 내 게임방법");
	m_howToPlay->ScreenOn = false;
}

GameMenu::GameMenu(const int objectNum, const string& objectName, SceneManager* pSceneManager, const double posX, const double posY)
	:Object(objectNum, objectName, posX, posY),
	m_iconSrcX(posX), m_iconSrcY(posY), m_iconDstX(158), m_iconDstY(147),
	m_containerSrcX(610), m_containerSrcY(334), m_containerDstX(1310), m_containerDstY(684),
	m_menuBoxSrcX(832), m_menuBoxSrcY(426), m_menuBoxDstX(1310), m_menuBoxDstY(684),
	m_boxIntervalX(0), m_boxIntervalY(129), m_isActivated(false), m_isPlayingHTP(false),
	m_closeButtonSrcX(1180), m_closeButtonSrcY(294), m_closeButtonDstX(1255), m_closeButtonDstY(384),
	m_localD2D(nullptr), m_localMouse(nullptr), m_mouseClickOnce(true),
	m_howToPlay(nullptr), m_localSceneManager(pSceneManager), m_localStageManager(nullptr),
	m_pShop(nullptr), m_pInventory(nullptr)
{
	this->renderOrder = SHOP_ORDER + 1;
	m_localD2D = D2DEngine::GetInstance();
	m_localMouse = MouseManager::GetInstance();
	m_localStageManager = StageManager::GetInstance();

	m_howToPlay = new HowtoPlay(0, "메뉴 내 게임방법");
	m_howToPlay->ScreenOn = false;
}

GameMenu::~GameMenu()
{
	
}

void GameMenu::UpdateObject()
{
	OpenMenu();
}

void GameMenu::RenderObject()
{
	m_localD2D->DrawSprite(eObjectDefine::MENU_ICON, m_iconSrcX, m_iconSrcY);

	if (this->m_isActivated == true)
	{
		m_localD2D->DrawSprite(eObjectDefine::MENU_BACKGROUND_INTERFACE, m_containerSrcX, m_containerSrcY);
		m_localD2D->DrawSprite(eObjectDefine::MENU_RETURN_TO_START, m_menuBoxSrcX, m_menuBoxSrcY);
		m_localD2D->DrawSprite(eObjectDefine::MENU_GAMERULES, m_menuBoxSrcX + m_boxIntervalX, m_menuBoxSrcY + m_boxIntervalY);
		m_localD2D->DrawSprite(eObjectDefine::MENU_CLOSE, m_closeButtonSrcX, m_closeButtonSrcY);
	}

	if (this->m_isActivated == true && m_howToPlay->ScreenOn == true)
	{
		ShowHowtoPlay();
	}
}

//메뉴켜
void GameMenu::OpenMenu()
{
	if (m_localMouse->GetLeftButtonDownState() == true
		&& m_mouseClickOnce == true
		&& m_iconSrcX <= m_localMouse->GetXPos()
		&& m_iconSrcY <= m_localMouse->GetYPos()
		&& m_iconDstX >= m_localMouse->GetXPos()
		&& m_iconDstY >= m_localMouse->GetYPos()
		)
	{
		m_mouseClickOnce = false;
	}

	if (m_localMouse->GetLeftButtonUpState() == true
		&& m_mouseClickOnce == false
		&& m_iconSrcX <= m_localMouse->GetXPos()
		&& m_iconSrcY <= m_localMouse->GetYPos()
		&& m_iconDstX >= m_localMouse->GetXPos()
		&& m_iconDstY >= m_localMouse->GetYPos()
		)
	{
		this->m_isActivated = true;

		m_mouseClickOnce = true;
	}
}

//메뉴꺼
void GameMenu::CloseMenu()
{
	if (m_howToPlay->ScreenOn == false)
	{
		if (m_localMouse->GetLeftButtonDownState() == true
			&& m_mouseClickOnce == true
			&& m_closeButtonSrcX <= m_localMouse->GetXPos()
			&& m_closeButtonSrcY <= m_localMouse->GetYPos()
			&& m_closeButtonDstX >= m_localMouse->GetXPos()
			&& m_closeButtonDstY >= m_localMouse->GetYPos()
			)
		{
			m_mouseClickOnce = false;
		}

		if (m_localMouse->GetLeftButtonUpState() == true
			&& m_mouseClickOnce == false
			&& m_closeButtonSrcX <= m_localMouse->GetXPos()
			&& m_closeButtonSrcY <= m_localMouse->GetYPos()
			&& m_closeButtonDstX >= m_localMouse->GetXPos()
			&& m_closeButtonDstY >= m_localMouse->GetYPos()
			)
		{
			this->m_isActivated = false;

			m_mouseClickOnce = true;
		}
	}
}

//게임방법을 띄우는 함수가 발동됐을 때 게임방법을 그려줌
void GameMenu::onClickHowToPlay()
{
	if (this->m_isActivated == true)
	{
		if (m_localMouse->GetLeftButtonDownState() == true
			&& m_mouseClickOnce == true
			&& m_menuBoxSrcX <= m_localMouse->GetXPos()
			&& m_menuBoxSrcY + m_boxIntervalY <= m_localMouse->GetYPos()
			&& m_menuBoxDstX >= m_localMouse->GetXPos()
			&& m_menuBoxDstY + m_boxIntervalY >= m_localMouse->GetYPos()
			)
		{
			m_mouseClickOnce = false;
		}

		if (m_localMouse->GetLeftButtonUpState() == true
			&& m_mouseClickOnce == false
			&& m_menuBoxSrcX <= m_localMouse->GetXPos()
			&& m_menuBoxSrcY + m_boxIntervalY <= m_localMouse->GetYPos()
			&& m_menuBoxDstX >= m_localMouse->GetXPos()
			&& m_menuBoxDstY + m_boxIntervalY >= m_localMouse->GetYPos()
			)
		{
			int a = 10;
			m_howToPlay->ScreenOn = true;

			m_mouseClickOnce = true;
		}
	}
}

//게임 방법 띄우는 함수
void GameMenu::ShowHowtoPlay()
{
	//if (m_howToPlay->ScreenOn = true)
	//{
		m_howToPlay->DrawHowtoPlay();
		m_howToPlay->Pages();
		m_howToPlay->ExitWindow();
		m_howToPlay->ChangePages();
	//}
}

//메인 화면으로 돌아가는 함수
void GameMenu::ReturnToMain()
{
	
	if (this->m_isActivated == true)
	{
		if (m_localMouse->GetLeftButtonDownState() == true
			&& m_mouseClickOnce == true
			&& m_menuBoxSrcX <= m_localMouse->GetXPos()
			&& m_menuBoxSrcY <= m_localMouse->GetYPos()
			&& m_menuBoxDstX >= m_localMouse->GetXPos()
			&& m_menuBoxDstY >= m_localMouse->GetYPos()
			)
		{
			m_mouseClickOnce = false;
		}

		if (m_localMouse->GetLeftButtonUpState() == true
			&& m_mouseClickOnce == false
			&& m_menuBoxSrcX <= m_localMouse->GetXPos()
			&& m_menuBoxSrcY <= m_localMouse->GetYPos()
			&& m_menuBoxDstX >= m_localMouse->GetXPos()
			&& m_menuBoxDstY >= m_localMouse->GetYPos()
			)
		{
			m_localSceneManager->SetNowScene("Main Scene");
			m_mouseClickOnce = true;
			this->m_isActivated = false;

			SoundManager::GetInstance().StopBGM(IngameBGM);
			SoundManager::GetInstance().StopBGM(Chapter4BGM);
		}
	}
}

bool GameMenu::GetActivated()
{
	return this->m_isActivated;
}
