#include "EndingScene.h"
#include "eSound.h"
#include "eObjectDefine.h"
#include "SceneManager.h"
#include "MouseManager.h"
#include "SoundManager.h"
#include "../D2DEngine/D2DEngine.h"
#include "../D2DEngine/Animator.h"
#include "TimerManager.h"
#include "StageManager.h"

Animator* Credit = new Animator();

EndingScene::EndingScene(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager)
	: IScene(sceneNum, sceneName, pSceneManager), Count(0), FrameCount(0), AccCount(0), AnmationCheck(false)
{
}

EndingScene::~EndingScene()
{
	Credit->ClearAnimation();

	delete Credit;
}

void EndingScene::UpdateScene()
{
	if (m_pMouseManager->GetLeftOneDownClickState())
	{
		Count++;
	}

	if (Count == 9)
	{
		SoundManager::GetInstance().StopBGM(EndingBGM);
		m_pSceneManager->SetNowScene("Main Scene");
		StageManager::GetInstance()->AddStage();
		StageManager::GetInstance()->StageInitialization(1);
		StageManager::GetInstance()->InitialShop();
		InitialMember();
	}

	if (Count == 7 && AnmationCheck == false)
	{
		AccCount += TimerManager::GetInstance().GetDeltaTime();
		if (AccCount >= 4 && AnmationCheck == false)
		{
			AnmationCheck = true;
		}
	}

}

void EndingScene::RenderScene()
{
	if (Count == 0)
	{
		SoundManager::GetInstance().PlayBGM(EndingBGM);//, "Resources/Sound/BGM_Ending.wav");
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::EndingScene1, 0, 0);
	}
	if (Count == 1)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::EndingScene2, 0, 0);

	}
	if (Count == 2)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::EndingScene3, 0, 0);

	}
	if (Count == 3)
	{

		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::EndingScene4, 0, 0);
	}
	if (Count == 4)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::EndingScene5, 0, 0);

	}
	if (Count == 5)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::EndingScene6, 0, 0);

	}
	if (Count == 6)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::EndingScene7, 0, 0);

	}
	if (Count == 7)
	{
		if (AnmationCheck == false)
		{
			Credit->PlayAnimation(0, 0, 5, 5);
		}
		if (AnmationCheck == true)
		{
			D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THANKYOU, 0, 0);
		}
	}
	if (Count == 8)
	{
		D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THANKYOU, 0, 0);
	}

}

void EndingScene::Initialize()
{
	m_pStageManager = StageManager::GetInstance();
	m_pMouseManager = MouseManager::GetInstance();

	for (int i = 0; i < 12; i++)
	{
		Credit->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::EndingSprite1, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 12; i++)
	{
		Credit->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::EndingSprite2, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 12; i++)
	{
		Credit->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::EndingSprite3, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 12; i++)
	{
		Credit->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::EndingSprite4, 0, 1080 * i, 1920, 1080, 1));
	}
}

void EndingScene::InitialMember()
{
	Count = 0;
	FrameCount = 0;
	AccCount = 0;
	AnmationCheck = false;
}
