#pragma once
#include "IScene.h"

class MouseManager;
class SoundManager;
class D2DEngine;

/// <summary>
/// 인트로 장면
/// 게임시작버튼을 누르면 나온다
/// </summary>
/// 
class IntroScene : public IScene
{
private:

public:
	IntroScene(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager);
	virtual ~IntroScene();

	virtual void UpdateScene() override;
	virtual void RenderScene() override;
	virtual void Initialize() override;

	int IntroCount;

private:

	MouseManager* m_pMouseManager;

};

