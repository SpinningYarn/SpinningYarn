#pragma once
#include "IScene.h"

//class StageManager;
class Animator;


class StageScene : public IScene
{
private:

public:
	StageScene(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager);
	virtual ~StageScene();

	virtual void UpdateScene() override;
	virtual void RenderScene() override;
	virtual void Initialize() override;

	int FrameCount;
	float AccCount;

	std::vector<Animator*> m_animatorList;

private:
	//StageManager* m_pStageManager;
};

