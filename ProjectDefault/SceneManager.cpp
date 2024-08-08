#include "SceneManager.h"
#include "IScene.h"
#include "MainScene.h"
#include "IntroScene.h"
#include "StageScene.h"
#include "TalkingScene1.h"
#include "Scene_Spinning.h"
#include "Scene_Knitting.h"
#include "Scene_Average.h"
#include "TalkingScene2.h"
#include "EndingScene.h"

SceneManager::SceneManager()
	: m_SceneIndex(0) // 씬 인덱스 시작번호 0으로 초기화
	, m_pNowScene(nullptr)
{
	
}

SceneManager::~SceneManager()
{

}

void SceneManager::Update()
{
	if (m_pNowScene->GetOndraw() == true)
	{
		m_pNowScene->UpdateScene();
	}
}

void SceneManager::Render()
{
	if (m_pNowScene->GetOndraw() == true)
	{
		m_pNowScene->RenderScene();
	}
}

/// MainScene(타이틀)
IScene* SceneManager::CreateMainScene(const std::string& sceneName)
{
	IScene* newScene = new MainScene(m_SceneIndex, sceneName, this);	// 새로운 씬 생성, 첫 씬의 인덱스는 0
	m_SceneList.push_back(newScene);						// 씬 리스트에 새로만든 씬 넣음
	m_SceneIndex++;											// 씬 번호 ++
	return newScene;
}

/// IntroScene(인트로)
IScene* SceneManager::CreateIntroScene(const std::string& sceneName)
{
	IScene* newScene = new IntroScene(m_SceneIndex, sceneName, this);	// 새로운 씬 생성, 첫 씬의 인덱스는 0
	m_SceneList.push_back(newScene);						// 씬 리스트에 새로만든 씬 넣음
	m_SceneIndex++;											// 씬 번호 ++
	return newScene;
}

/// StageScene(스테이지 바뀔때 소제목)
IScene* SceneManager::CreateStageScene(const std::string& sceneName)
{
	IScene* newScene = new StageScene(m_SceneIndex, sceneName, this);	// 새로운 씬 생성, 첫 씬의 인덱스는 0
	m_SceneList.push_back(newScene);						// 씬 리스트에 새로만든 씬 넣음
	m_SceneIndex++;											// 씬 번호 ++
	return newScene;
}

/// TalkingScene1(미니게임전 손님대화)
IScene* SceneManager::CreateTalking1Scene(const std::string& sceneName)
{
	IScene* newScene = new TalkingScene1(m_SceneIndex, sceneName, this);	// 새로운 씬 생성, 첫 씬의 인덱스는 0
	m_SceneList.push_back(newScene);						// 씬 리스트에 새로만든 씬 넣음
	m_SceneIndex++;											// 씬 번호 ++
	return newScene;
}


/// 평균구하는 씬
IScene* SceneManager::CreateScene_Average(const std::string& sceneName)
{
	IScene* newScene = new Scene_Average(m_SceneIndex, sceneName, this);	// 새로운 씬 생성, 첫 씬의 인덱스는 0
	m_SceneList.push_back(newScene);						// 씬 리스트에 새로만든 씬 넣음
	m_SceneIndex++;											// 씬 번호 ++
	return newScene;
}

IScene* SceneManager::CreateScene_Spinning(const std::string& sceneName)
{
	IScene* newScene = new Scene_Spinning(m_SceneIndex, sceneName, this);	// 새로운 씬 생성, 첫 씬의 인덱스는 0
	m_SceneList.push_back(newScene);						// 씬 리스트에 새로만든 씬 넣음
	m_SceneIndex++;											// 씬 번호 ++
	return newScene;
}

IScene* SceneManager::CreateScene_Knitting(const std::string& sceneName)
{
	IScene* newScene = new Scene_Knitting(m_SceneIndex, sceneName, this);	// 새로운 씬 생성, 첫 씬의 인덱스는 0
	m_SceneList.push_back(newScene);						// 씬 리스트에 새로만든 씬 넣음
	m_SceneIndex++;											// 씬 번호 ++
	return newScene;
}

/// TalkingScene2(미니게임후 손님 대화)
IScene* SceneManager::CreateTalking2Scene(const std::string& sceneName)
{
	IScene* newScene = new TalkingScene2(m_SceneIndex, sceneName, this);	// 새로운 씬 생성, 첫 씬의 인덱스는 0
	m_SceneList.push_back(newScene);						// 씬 리스트에 새로만든 씬 넣음
	m_SceneIndex++;											// 씬 번호 ++
	return newScene;
}

/// EndingScene
IScene* SceneManager::CreateEndingScene(const std::string& sceneName)
{
	IScene* newScene = new EndingScene(m_SceneIndex, sceneName, this);	// 새로운 씬 생성, 첫 씬의 인덱스는 0
	m_SceneList.push_back(newScene);						// 씬 리스트에 새로만든 씬 넣음
	m_SceneIndex++;											// 씬 번호 ++
	return newScene;
}


IScene* SceneManager::GetScene(const int sceneNum)			// 씬 번호 인자로 넣어 씬 불러오기
{
	for (int i = 0; i < m_SceneList.size(); i++)
	{
		if (m_SceneList[i]->GetSceneIndex() == sceneNum)
		{
			return m_SceneList[i];							
		}
	}
	return nullptr;											// Num이 인덱스와 일치하면 인덱스에 맞는 씬 리턴
}

IScene* SceneManager::GetScene(const std::string& sceneName)	// 씬 이름 인자로 넣어 씬 불러오기
{
	for (int i = 0; i < m_SceneList.size(); i++)
	{
		if (m_SceneList[i]->GetSceneName() == sceneName)
		{
			return m_SceneList[i];
		}
	}
	return nullptr;											// Num이 인덱스와 일치하면 인덱스에 맞는 씬 리턴
}

void SceneManager::DeleteScene(const int sceneNum)
{
	for (int i = 0; i < m_SceneList.size(); i++)
	{
		if (m_SceneList[i]->GetSceneIndex() == sceneNum)
		{
			m_SceneList.erase(m_SceneList.begin() + i);		// 인덱스와 일치하는 씬이 있다면 그 씬 삭제
		}
	}
}

void SceneManager::DeleteScene(const std::string& sceneName)
{
	for (int i = 0; i < m_SceneList.size(); i++)
	{
		if (m_SceneList[i]->GetSceneName() == sceneName)
		{
			m_SceneList.erase(m_SceneList.begin() + i);		// 인자 이름과 일치하는 씬이 있다면 그 씬 삭제
		}
	}
}

IScene* SceneManager::GetNowScene()
{
	return m_pNowScene;
}

int SceneManager::GetSceneSize()
{
	return m_SceneList.size();
}

void SceneManager::SetNowScene(const int sceneNum)
{
	// 해당 씬이 처음이 아니라면 그리기 종료
	if (m_pNowScene!=nullptr)
	{
		m_pNowScene->SetOndrawFalse();
	}

	// 새로운 씬 그리기 시작
	m_pNowScene = GetScene(sceneNum);
	m_pNowScene->SetOndrawTrue();
}

void SceneManager::SetNowScene(const std::string& sceneName)
{
	// 해당 씬이 처음이 아니라면 그리기 종료
	if (m_pNowScene != nullptr)
	{
		m_pNowScene->SetOndrawFalse();
	}

	// 새로운 씬 그리기 시작
	m_pNowScene = GetScene(sceneName);
	m_pNowScene->SetOndrawTrue();
}
