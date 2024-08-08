#pragma once
#include "IScene.h"

class MouseManager;
class StageManager;

class EndingScene : public IScene
{
private:

public:
	EndingScene(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager);
	virtual ~EndingScene();

	virtual void UpdateScene() override;
	virtual void RenderScene() override;
	virtual void Initialize() override;
	void InitialMember();

private:
	int Count;

	bool EndingAni;
	bool AniCheck;

	int FrameCount;
	double AccCount;
	MouseManager* m_pMouseManager;
	StageManager* m_pStageManager;
	bool AnmationCheck;
};

