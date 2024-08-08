#pragma once
#include "IScene.h"

class MouseManager;
class StageManager;

/// <summary>
/// 미니게임 시작전에 손님과 대화하는 씬
/// </summary>

class TalkingScene1 : public IScene
{
public:
	TalkingScene1(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager);
	virtual ~TalkingScene1();

	virtual void UpdateScene() override;
	virtual void RenderScene() override;
	virtual void Initialize() override;

private:
	bool isEffectStart;
	int TalkCount;

	//bool case1;
	//bool case2;
	//bool case3;
	//bool case4;
	//bool case5;

	//SoundManager* m_pSoundManager;
	MouseManager* m_pMouseManager;
	StageManager* m_pStageManager;
};

