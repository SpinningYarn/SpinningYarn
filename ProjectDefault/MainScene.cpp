#include "MainScene.h"
#include "eObjectDefine.h"

#include "SoundManager.h"
#include "SceneManager.h"
#include "MouseManager.h"
#include "../D2DEngine/D2DEngine.h"
#include "HowtoPlay.h"
#include "MainBackground.h"
#include "StageManager.h"

MainScene::MainScene(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager)
	: IScene(sceneNum, sceneName, pSceneManager), m_pMainBackground(nullptr), m_pMouseManager(nullptr), m_pHowtoPlay(nullptr),
	m_exitButtonSrcX(13), m_exitButtonSrcY(968), m_exitButtonDstX(113), m_exitButtonDstY(1068)
{
	
}

MainScene::~MainScene()
{

}

void MainScene::UpdateScene()
{
	OnUpdate();
	SoundManager::GetInstance().PlayBGM(MainBGM);//, "Resources/Sound/BGM_Title.wav");
	
	HowToPlay();

	if (!m_pHowtoPlay->ScreenOn)
	{
		GameStart();
		EndGame();
	}
}

void MainScene::RenderScene()
{
	OnRender();
}

void MainScene::Initialize()
{
	m_pMouseManager = MouseManager::GetInstance();
	m_pMainBackground = (MainBackground*)m_pSceneManager->GetScene("Main Scene")->GetSceneObject("메인배경화면");
	m_pHowtoPlay = (HowtoPlay*)m_pSceneManager->GetScene("Main Scene")->GetSceneObject("게임방법");
}

void MainScene::GameStart()
{
	if (m_pMouseManager->GetLeftOneDownClickState() == true
		&& 1326 <= m_pMouseManager->GetXPos()
		&& 1638 >= m_pMouseManager->GetXPos()
		&& 650 <= m_pMouseManager->GetYPos()
		&& 798 >= m_pMouseManager->GetYPos())
	{
	}
	if (m_pMouseManager->GetLeftOneUpClickState() == true
		&& 1326 <= m_pMouseManager->GetXPos()
		&& 1638 >= m_pMouseManager->GetXPos()
		&& 650 <= m_pMouseManager->GetYPos()
		&& 798 >= m_pMouseManager->GetYPos())
	{

		StageManager::GetInstance()->AddStage();
		StageManager::GetInstance()->StageInitialization(1);
		StageManager::GetInstance()->InitialShop();

		SoundManager::GetInstance().StopBGM(MainBGM);
		StageManager::GetInstance()->SetStage(1);
		m_pSceneManager->SetNowScene("IntroScene");
	}
}

void MainScene::HowToPlay()
{
	if (m_pMouseManager->GetLeftOneDownClickState() == true
		&& 1326 <= m_pMouseManager->GetXPos()
		&& 1638 >= m_pMouseManager->GetXPos()
		&& 842 <= m_pMouseManager->GetYPos()
		&& 990 >= m_pMouseManager->GetYPos())
	{
		m_pHowtoPlay->ScreenOn = true;
	}
}

void MainScene::EndGame()
{
	if (m_pMouseManager->GetLeftOneUpClickState() == true
		&& m_exitButtonSrcX <= m_pMouseManager->GetXPos()
		&& m_exitButtonSrcY <= m_pMouseManager->GetYPos()
		&& m_exitButtonDstX >= m_pMouseManager->GetXPos()
		&& m_exitButtonDstY >= m_pMouseManager->GetYPos())
	{
		PostQuitMessage(0);
	}
}

