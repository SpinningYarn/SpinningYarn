#include "TalkingScene2.h"
#include "eObjectDefine.h"
#include "SceneManager.h"
#include "MouseManager.h"
#include "SoundManager.h"
#include "../D2DEngine/D2DEngine.h"
#include "StageManager.h"
#include "SpinningGaugeManager.h"
#include "eSound.h"

TalkingScene2::TalkingScene2(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager)
	: IScene(sceneNum, sceneName, pSceneManager), TalkCount(1)
{
	
}

TalkingScene2::~TalkingScene2()
{
}

void TalkingScene2::UpdateScene()
{
	if (m_pMouseManager->GetLeftOneDownClickState())
	{
		TalkCount++;
	}
	switch (m_pStageManager->GetStageNum())
	{
		case 1:
			if (TalkCount >= 6)
			{
				SoundManager::GetInstance().StopBGM(IngameBGM);

				/// Stage 넘어가기전 player 소지금 정산
				// 더할 Tip 금액 정산
				m_pStageManager->TipMoneyCalc();
				m_pStageManager->DecreaseTipMoney(m_pStageManager->GetTimMoneyDecreaseRate());	// 
				// Player 소지금 정산
				m_pStageManager->IncreaseMoney(m_pStageManager->GetStageNum(), m_pStageManager->GetTipMoney());

				/// Stage 증가 (1 -> 2)
				m_pStageManager->AddStage();
				m_pStageManager->StageInitialization(m_pStageManager->GetStageNum());

				TalkCount = 1;
				m_pSceneManager->SetNowScene("StageScene");
			}
			break;

		case 2:
			if (TalkCount >= 8)
			{
				SoundManager::GetInstance().StopBGM(IngameBGM);

				/// Stage 넘어가기전 player 소지금 정산
				// 더할 Tip 금액 정산
				m_pStageManager->TipMoneyCalc();
				m_pStageManager->DecreaseTipMoney(m_pStageManager->GetTimMoneyDecreaseRate());	// 
				// Player 소지금 정산
				m_pStageManager->IncreaseMoney(m_pStageManager->GetStageNum(), m_pStageManager->GetTipMoney());

				/// Stage 증가 (2 -> 3)
				m_pStageManager->AddStage();
				m_pStageManager->StageInitialization(m_pStageManager->GetStageNum());

				SpinningGaugeManager::GetInstance()->SetRandomPos();
				m_pSceneManager->SetNowScene("StageScene");
				TalkCount = 1;
			}
			break;

		case 3:
			if (TalkCount >= 8)
			{
				SoundManager::GetInstance().StopBGM(IngameBGM);
				/// Stage 넘어가기전 player 소지금 정산
				// 더할 Tip 금액 정산
				m_pStageManager->TipMoneyCalc();
				m_pStageManager->DecreaseTipMoney(m_pStageManager->GetTimMoneyDecreaseRate());	// 
				// Player 소지금 정산
				m_pStageManager->IncreaseMoney(m_pStageManager->GetStageNum(), m_pStageManager->GetTipMoney());

				/// Stage 증가 (3 -> 4)
				m_pStageManager->AddStage();
				m_pStageManager->StageInitialization(m_pStageManager->GetStageNum());

				m_pSceneManager->SetNowScene("StageScene");
				TalkCount = 1;
			}
			break;

		case 4:
			if (TalkCount >= 9)
			{
				SoundManager::GetInstance().StopBGM(Chapter4BGM);

				/// Stage 넘어가기전 player 소지금 정산
				// 더할 Tip 금액 정산
				m_pStageManager->TipMoneyCalc();
				m_pStageManager->DecreaseTipMoney(m_pStageManager->GetTimMoneyDecreaseRate());	// 
				// Player 소지금 정산
				m_pStageManager->IncreaseMoney(m_pStageManager->GetStageNum(), m_pStageManager->GetTipMoney());

				/// Stage 증가 (4 -> 5)
				m_pStageManager->AddStage();
				m_pStageManager->StageInitialization(m_pStageManager->GetStageNum());
				m_pSceneManager->SetNowScene("StageScene");
				TalkCount = 1;
			}
			break;

		case 5:
			if (TalkCount >= 10)
			{
				SoundManager::GetInstance().StopBGM(Chapter4BGM);				
				/// Stage 넘어가기전 player 소지금 정산
				// 더할 Tip 금액 정산
				
				m_pSceneManager->SetNowScene("EndingScene");
				TalkCount = 1;
			}
			break;

		default:
			break;
	}
}

void TalkingScene2::RenderScene()
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
			D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTCHARACTER2, 0, 0);
			if (TalkCount == 1)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE11, 264, 622);
			}
			if (TalkCount == 2)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE12, 264, 622);
			}
			if (TalkCount == 3)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE13, 264, 622);
			}
			if (TalkCount == 4)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE14, 264, 622);
			}
			if (TalkCount == 5)
			{
				if (case1Sound == false)
				{
					SoundManager::GetInstance().PlaySounds(CustomerBye1);
					case1Sound = true;
				}
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIRSTSTAGE15, 264, 622);
			}
			break;
		case 2:
			D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDCHARACTER2, 0, 0);
			if (TalkCount == 1)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDSTAGE8, 264, 622);
			}
			if (TalkCount == 2)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDSTAGE9, 264, 622);
			}
			if (TalkCount == 3)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDSTAGE10, 264, 622);
			}
			if (TalkCount == 4)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDSTAGE11, 264, 622);
			}
			if (TalkCount == 5)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDSTAGE12, 264, 622);
			}
			if (TalkCount == 6)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDSTAGE13, 264, 622);
			}
			if (TalkCount == 7)
			{
				if (case2Sound == false)
				{
					SoundManager::GetInstance().PlaySounds(CustomerBye1);

					case2Sound = true;
				}
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::SECONDSTAGE14, 264, 622);
			}
			break;
		case 3:
			D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDCHARACTER2, 0, 0);
			if (TalkCount == 1)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE10, 264, 622);
			}
			if (TalkCount == 2)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE11, 264, 622);
			}
			if (TalkCount == 3)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE12, 264, 622);
			}
			if (TalkCount == 4)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE13, 264, 622);
			}
			if (TalkCount == 5)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE14, 264, 622);
			}
			if (TalkCount == 6)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE15, 264, 622);
			}
			if (TalkCount == 7)
			{
				if (case3Sound == false)
				{
					SoundManager::GetInstance().PlaySounds(CustomerBye1);
					case3Sound = true;
				}
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::THIRDSTAGE16, 264, 622);
			}
			break;
		case 4:
			D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHCHARACTER2, 0, 0);
			if (TalkCount == 1)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE12, 264, 622);
			}
			if (TalkCount == 2)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE13, 264, 622);
			}
			if (TalkCount == 3)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE14, 264, 622);
			}
			if (TalkCount == 4)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE15, 264, 622);
			}
			if (TalkCount == 5)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE16, 264, 622);
			}
			if (TalkCount == 6)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE17, 264, 622);
			}
			if (TalkCount == 7)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE18, 264, 622);
			}
			if (TalkCount == 8)
			{
				if (case4Sound == false)
				{
					SoundManager::GetInstance().PlaySounds(CustomerBye1);
					case4Sound = true;
				}
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FOURTHSTAGE19, 264, 622);
			}
			break;
		case 5:
			D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHCHARACTER2, 0, 0);
			if (TalkCount == 1)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE11, 264, 622);
			}
			if (TalkCount == 2)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE12, 264, 622);
			}
			if (TalkCount == 3)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE13, 264, 622);
			}
			if (TalkCount == 4)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE14, 264, 622);
			}
			if (TalkCount == 5)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE15, 264, 622);
			}
			if (TalkCount == 6)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE16, 264, 622);
			}
			if (TalkCount == 7)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE17, 264, 622);
			}
			if (TalkCount == 8)
			{
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE18, 264, 622);
			}
			if (TalkCount == 9)
			{
				if (case5Sound == false)
				{
					SoundManager::GetInstance().PlaySounds(CustomerBye1);
					case5Sound = true;
				}
				D2DEngine::GetInstance()->DrawSprite(eObjectDefine::FIFTHSTAGE19, 264, 622);
			}
			break;
	}
}

void TalkingScene2::Initialize()
{
	m_pStageManager = StageManager::GetInstance();
	m_pMouseManager = MouseManager::GetInstance();
}
