#pragma once
#include "IScene.h"

class MouseManager;
class StageManager;

/// <summary>
/// 미니게임 끝난후 손님과 대화하는 씬
/// </summary>
class TalkingScene2 : public IScene
{
public:
	TalkingScene2(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager);
	virtual ~TalkingScene2();

	virtual void UpdateScene() override;
	virtual void RenderScene() override;
	virtual void Initialize() override;

private:
	int TalkCount;

	MouseManager* m_pMouseManager;
	StageManager* m_pStageManager;
};

