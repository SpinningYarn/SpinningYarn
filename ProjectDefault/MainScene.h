#pragma once
#include "IScene.h"

class MouseManager;
class D2DEngine;
class MainBackground;
class HowtoPlay;

/// <summary>
/// 게임 메인 화면
/// 
/// 필요한 버튼들
/// 게임 시작 버튼
/// 게임 설명 버튼
/// 게임 종료 버튼
/// </summary>

class MainScene : public IScene
{
public:
	MainScene(const int sceneNum, const std::string& sceneName, SceneManager* pSceneManager);
	virtual ~MainScene();

	virtual void UpdateScene() override;
	virtual void RenderScene() override;
	virtual void Initialize() override;

	void GameStart();
	void HowToPlay();
	void EndGame();

private:
	HowtoPlay* m_pHowtoPlay;
	MainBackground* m_pMainBackground;
	MouseManager* m_pMouseManager;

	float m_exitButtonSrcX;
	float m_exitButtonSrcY;
	float m_exitButtonDstX;
	float m_exitButtonDstY;
};

