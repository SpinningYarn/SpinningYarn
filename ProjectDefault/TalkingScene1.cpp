#include "TalkingScene1.h"
#include "eObjectDefine.h"
#include "SceneManager.h"
#include "MouseManager.h"
#include "SoundManager.h"
#include "../D2DEngine/D2DEngine.h"
#include "StageManager.h"


TalkingScene1::TalkingScene1(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager)
	: IScene(sceneNum, sceneName, pSceneManager), TalkCount(1)
	, isEffectStart(false)//, case1(false),case2(false), case3(false), case4(false), case5(false)
{
}

TalkingScene1::~TalkingScene1()
{
}

void TalkingScene1::UpdateScene()
{


	// , "Resources/Sound/BGM_Ingame.wav");
	if (m_pMouseManager->GetLeftOneDownClickState())
	{
		TalkCount++;
	}

	switch (m_pStageManager->GetStageNum())
	{
		case 1:
			if (TalkCount >= 11)
			{
				m_pSceneManager->SetNowScene("AverageScene");
				TalkCount = 1;
			}
			break;

		case 2:
			if (TalkCount >= 8)
			{
				m_pSceneManager->SetNowScene("AverageScene");
				TalkCount = 1;
			}
			break;

		case 3:
			if (TalkCount >= 10)
			{
				m_pSceneManager->SetNowScene("AverageScene");
				TalkCount = 1;
			}
			break;

		case 4:
			if (TalkCount >= 12)
			{
				m_pSceneManager->SetNowScene("AverageScene");
				TalkCount = 1;
			}
			break;

		case 5:
			if (TalkCount >= 11)
			{
				m_pSceneManager->SetNowScene("AverageScene");
				TalkCount = 1;
			}
			break;

		default:
			break;
	}

	OnUpdate();
}

void TalkingScene1::RenderScene()
{
	static bool case1Sound = false;
	static bool case2Sound = false;
	static bool case3Sound = false;
	static bool case4Sound = false;
	static bool case5Sound = false;

	D2DEngine::GetInstance()->DrawSprite(eObjectDefine::TALKINGBACKGROUND, 0, 0);

	switch (m_pStageManager->GetStageNum())
	{
		case 1:
			SoundManager::GetInstance().PlayBGM(IngameBGM);
			if (TalkCount == 1)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE1, 264, 622);
			}
			if (TalkCount == 2)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE2, 264, 622);
			}
			if (TalkCount == 3)
			{
				if (case1Sound == false)
				{
					SoundManager::GetInstance().PlaySounds(CustomerIn1);
					case1Sound = true;
				}

				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE3, 264, 622);
			}
			if (TalkCount == 4)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE4, 264, 622);
			}
			if (TalkCount == 5)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE5, 264, 622);
			}
			if (TalkCount == 6)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE6, 264, 622);
			}
			if (TalkCount == 7)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE7, 264, 622);
			}
			if (TalkCount == 8)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE8, 264, 622);
			}
			if (TalkCount == 9)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE9, 264, 622);
			}
			if (TalkCount == 10)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE10, 264, 622);
			}

			break;
		case 2:
			SoundManager::GetInstance().PlayBGM(IngameBGM);
			if (TalkCount == 1)
			{
				if (case2Sound == false)
				{
					SoundManager::GetInstance().PlaySounds(CustomerIn1);
					case2Sound = true;
				}

				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDSTAGE1, 264, 622);
			}
			if (TalkCount == 2)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDSTAGE2, 264, 622);
			}
			if (TalkCount == 3)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDSTAGE3, 264, 622);
			}
			if (TalkCount == 4)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDSTAGE4, 264, 622);
			}
			if (TalkCount == 5)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDSTAGE5, 264, 622);
			}
			if (TalkCount == 6)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDSTAGE6, 264, 622);
			}
			if (TalkCount == 7)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDSTAGE7, 264, 622);

			}

			break;
		case 3:
			D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDCHARACTER1, 0, 0);
			SoundManager::GetInstance().PlayBGM(IngameBGM);
			if (TalkCount == 1)
			{
				if (case3Sound == false)
				{
					SoundManager::GetInstance().PlaySounds(CustomerIn1);
					case3Sound = true;
				}
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE1, 264, 622);
			}
			if (TalkCount == 2)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE2, 264, 622);
			}
			if (TalkCount == 3)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE3, 264, 622);
			}
			if (TalkCount == 4)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE4, 264, 622);
			}
			if (TalkCount == 5)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE5, 264, 622);
			}
			if (TalkCount == 6)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE6, 264, 622);
			}
			if (TalkCount == 7)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE7, 264, 622);
			}
			if (TalkCount == 8)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE8, 264, 622);
			}
			if (TalkCount == 9)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE9, 264, 622);

			}
			break;
		case 4:

			// 4Ã©ÅÍ ½ÃÀÛ ºê±Ý ¹Ù²ñ
			//SoundManager::GetInstance().PlayBGM(Chapter4BGM);// , "Resources/Sound/BGM_Ingame2.wav");
			SoundManager::GetInstance().PlayBGM(Chapter4BGM);

			if (TalkCount == 1)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE1, 264, 622);
			}
			if (TalkCount == 2)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE2, 264, 622);
			}
			if (TalkCount == 3)
			{
				if (case4Sound == false)
				{
					SoundManager::GetInstance().PlaySounds(CustomerIn1);
					case4Sound = true;
				}
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE3, 264, 622);
			}
			if (TalkCount == 4)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE4, 264, 622);
			}
			if (TalkCount == 5)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE5, 264, 622);
			}
			if (TalkCount == 6)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE6, 264, 622);
			}
			if (TalkCount == 7)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE7, 264, 622);
			}
			if (TalkCount == 8)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE8, 264, 622);
			}
			if (TalkCount == 9)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE9, 264, 622);
			}
			if (TalkCount == 10)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE10, 264, 622);
			}
			if (TalkCount == 11)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE11, 264, 622);
			}
			break;
		case 5:
			SoundManager::GetInstance().PlayBGM(Chapter4BGM);


			if (TalkCount == 1)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE1, 264, 622);
			}
			if (TalkCount == 2)
			{
				if (case5Sound == false)
				{
					SoundManager::GetInstance().PlaySounds(CustomerIn1);// , "Resources/Sound/Effect/SE_CustomerIn_(shop-door-bell-6405.wav");
					case5Sound = true;
				}
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE2, 264, 622);
			}
			if (TalkCount == 3)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE3, 264, 622);
			}
			if (TalkCount == 4)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE4, 264, 622);
			}
			if (TalkCount == 5)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE5, 264, 622);
			}
			if (TalkCount == 6)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE6, 264, 622);
			}
			if (TalkCount == 7)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE7, 264, 622);
			}
			if (TalkCount == 8)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE8, 264, 622);
			}
			if (TalkCount == 9)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE9, 264, 622);
			}
			if (TalkCount == 10)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHCHARACTER1, 0, 0);
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE10, 264, 622);

			}
			break;
	}

}

void TalkingScene1::Initialize()
{
	m_pStageManager = StageManager::GetInstance();
	m_pMouseManager = MouseManager::GetInstance();
}
