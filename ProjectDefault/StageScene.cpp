#include "StageScene.h"
#include "eObjectDefine.h"

#include "KeyManager.h"
#include "SoundManager.h"
#include "SceneManager.h"
#include "TimerManager.h"
#include "StageManager.h"
#include "../D2DEngine/D2DEngine.h"
#include "../D2DEngine/Animator.h"

Animator* Animator1 = new Animator();
Animator* Animator2 = new Animator();
Animator* Animator3 = new Animator();
Animator* Animator4 = new Animator();
Animator* Animator5 = new Animator();

StageScene::StageScene(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager)
	: IScene(sceneNum, sceneName, pSceneManager), FrameCount(0), AccCount(0)
{

}

StageScene::~StageScene()
{
	Animator1->ClearAnimation();
	Animator2->ClearAnimation();
	Animator3->ClearAnimation();
	Animator4->ClearAnimation();
	Animator5->ClearAnimation();

	delete Animator1;
	delete Animator2;
	delete Animator3;
	delete Animator4;
	delete Animator5;
}

void StageScene::UpdateScene()
{
	AccCount += TimerManager::GetInstance().GetDeltaTime();
	FrameCount++;
	switch (StageManager::GetInstance()->GetStageNum())
	{
		/// AccCount를 7.9로 한다
		/// 7.2		///어째서 컴퓨터 마다 다른것인가 
		case 1:
			SoundManager::GetInstance().PlayBGM(ChapterChangeBGM);
			AccCount += TimerManager::GetInstance().GetDeltaTime();
			FrameCount++;
			//if (AccCount >= 1)
			if (AccCount >= 7.2)
			//if (AccCount >= 10)
			{
				AccCount = 0;
				FrameCount = 0;
				SoundManager::GetInstance().StopBGM(ChapterChangeBGM);

				m_pSceneManager->SetNowScene("TalkingScene1");
			}
			break;
		case 2:
			SoundManager::GetInstance().PlayBGM(ChapterChangeBGM);

			AccCount += TimerManager::GetInstance().GetDeltaTime();
			FrameCount++;
			if (AccCount >= 7.5)
			{
				AccCount = 0;
				FrameCount = 0;
				SoundManager::GetInstance().StopBGM(ChapterChangeBGM);

				m_pSceneManager->SetNowScene("TalkingScene1");
			}
			break;
		case 3:
			SoundManager::GetInstance().PlayBGM(ChapterChangeBGM);

			AccCount += TimerManager::GetInstance().GetDeltaTime();
			FrameCount++;
			if (AccCount >= 7.5)
			{
				AccCount = 0;
				FrameCount = 0;
				SoundManager::GetInstance().StopBGM(ChapterChangeBGM);

				m_pSceneManager->SetNowScene("TalkingScene1");
			}
			break;
		case 4:
			SoundManager::GetInstance().PlayBGM(ChapterChangeBGM);

			AccCount += TimerManager::GetInstance().GetDeltaTime();
			FrameCount++;
			if (AccCount >= 7.5)
			{
				AccCount = 0;
				FrameCount = 0;
				SoundManager::GetInstance().StopBGM(ChapterChangeBGM);
		
				m_pSceneManager->SetNowScene("TalkingScene1");
			}
			break;
		case 5:
			SoundManager::GetInstance().PlayBGM(ChapterChangeBGM);

			AccCount += TimerManager::GetInstance().GetDeltaTime();
			FrameCount++;
			if (AccCount >= 7.5)
			{
				AccCount = 0;
				FrameCount = 0;
				SoundManager::GetInstance().StopBGM(ChapterChangeBGM);

				m_pSceneManager->SetNowScene("TalkingScene1");
			}
			break;
		default:
			break;
	}
}

void StageScene::RenderScene()
{
	switch (StageManager::GetInstance()->GetStageNum())
	{
		case 1:
			Animator1->PlayAnimation(0, 0, 3.8, 4);
			break;
		case 2:
			Animator2->PlayAnimation(0, 0, 3.8, 4);
			break;
		case 3:
			Animator3->PlayAnimation(0, 0, 3.8, 4);
			break;
		case 4:
			Animator4->PlayAnimation(0, 0, 3.8, 4);
			break;
		case 5:
			Animator5->PlayAnimation(0, 0, 3.8, 4);
			break;
		default:
			break;
	}
}



void StageScene::Initialize()
{
	//Stage 1
	for (int i = 0; i < 13; i++)
	{
		Animator1->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter1Title1, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 12; i++)
	{
		Animator1->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter1Title2, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 12; i++)
	{
		Animator1->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter1Title3, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 11; i++)
	{
		Animator1->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter1Title4, 0, 1080 * i, 1920, 1080, 1));
	}

	//Stage 2
	for (int i = 0; i < 13; i++)
	{
		Animator2->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter2Title1, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 12; i++)
	{
		Animator2->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter2Title2, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 12; i++)
	{
		Animator2->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter2Title3, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 11; i++)
	{
		Animator2->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter2Title4, 0, 1080 * i, 1920, 1080, 1));
	}

	//stage 3
	for (int i = 0; i < 13; i++)
	{
		Animator3->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter3Title1, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 12; i++)
	{
		Animator3->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter3Title2, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 12; i++)
	{
		Animator3->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter3Title3, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 11; i++)
	{
		Animator3->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter3Title4, 0, 1080 * i, 1920, 1080, 1));
	}

	//stage 4
	for (int i = 0; i < 13; i++)
	{
		Animator4->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter4Title1, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 12; i++)
	{
		Animator4->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter4Title2, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 12; i++)
	{
		Animator4->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter4Title3, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 11; i++)
	{
		Animator4->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter4Title4, 0, 1080 * i, 1920, 1080, 1));
	}

	//stage 5
	for (int i = 0; i < 13; i++)
	{
		Animator5->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter5Title1, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 12; i++)
	{
		Animator5->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter5Title2, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 12; i++)
	{
		Animator5->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter5Title3, 0, 1080 * i, 1920, 1080, 1));
	}
	for (int i = 0; i < 11; i++)
	{
		Animator5->AddAnimation(D2DEngine::GetInstance()->LoadSpriteFromSheet2(eObjectDefine::Chapter5Title4, 0, 1080 * i, 1920, 1080, 1));
	}
}
