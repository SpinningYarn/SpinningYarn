#include "IntroScene.h"
#include "SceneManager.h"
#include "MouseManager.h"
#include "SoundManager.h"
#include "../D2DEngine/D2DEngine.h"
#include "KeyManager.h"


IntroScene::IntroScene(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager)
	: IScene(sceneNum, sceneName, pSceneManager), IntroCount(0)
{
	m_pMouseManager = MouseManager::GetInstance();
}

IntroScene::~IntroScene()
{
}

void IntroScene::UpdateScene()
{
// 	if (KeyManager::GetInstance().GetKeyAndState(Key::SPACE) == KeyState::TAP)
// 	{
// 		m_pSceneManager->SetNowScene("KnittingScene");
// 	}

	SoundManager::GetInstance().PlayBGM(OpenningBGM);// , "Resources/Sound/BGM_Opening.wav");
	if (m_pMouseManager->GetLeftOneDownClickState())
	{
		IntroCount++;
	}
}

void IntroScene::RenderScene()
{
	if (IntroCount == 0)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::INTROCUTSCENE1, 0, 0);
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::INTROSCRIPT1, 0, 0);
	}
	if (IntroCount == 1)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::INTROCUTSCENE2, 0, 0);
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::INTROSCRIPT2, 0, 0);
	}
	if (IntroCount == 2)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::INTROCUTSCENE3, 0, 0);
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::INTROSCRIPT3, 0, 0);
	}
	if (IntroCount == 3)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::INTROCUTSCENE3, 0, 0);
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::INTROSCRIPT4, 0, 0);
	}
	if (IntroCount == 4)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::INTROCUTSCENE4, 0, 0);
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::INTROSCRIPT5, 0, 0);
	}
	if (IntroCount == 5)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::INTROCUTSCENE4, 0, 0);
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::INTROSCRIPT6, 0, 0);
	}
	if (IntroCount == 6)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::INTROCUTSCENE4, 0, 0);
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::INTROSCRIPT7, 0, 0);
	}
	if (IntroCount == 7)
	{
		m_pSceneManager->SetNowScene("StageScene");
		SoundManager::GetInstance().StopBGM(OpenningBGM);
		IntroCount = 0;
	}
}

void IntroScene::Initialize()
{
}
