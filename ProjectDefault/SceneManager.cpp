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
	: m_SceneIndex(0) // �� �ε��� ���۹�ȣ 0���� �ʱ�ȭ
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

/// MainScene(Ÿ��Ʋ)
IScene* SceneManager::CreateMainScene(const std::string& sceneName)
{
	IScene* newScene = new MainScene(m_SceneIndex, sceneName, this);	// ���ο� �� ����, ù ���� �ε����� 0
	m_SceneList.push_back(newScene);						// �� ����Ʈ�� ���θ��� �� ����
	m_SceneIndex++;											// �� ��ȣ ++
	return newScene;
}

/// IntroScene(��Ʈ��)
IScene* SceneManager::CreateIntroScene(const std::string& sceneName)
{
	IScene* newScene = new IntroScene(m_SceneIndex, sceneName, this);	// ���ο� �� ����, ù ���� �ε����� 0
	m_SceneList.push_back(newScene);						// �� ����Ʈ�� ���θ��� �� ����
	m_SceneIndex++;											// �� ��ȣ ++
	return newScene;
}

/// StageScene(�������� �ٲ� ������)
IScene* SceneManager::CreateStageScene(const std::string& sceneName)
{
	IScene* newScene = new StageScene(m_SceneIndex, sceneName, this);	// ���ο� �� ����, ù ���� �ε����� 0
	m_SceneList.push_back(newScene);						// �� ����Ʈ�� ���θ��� �� ����
	m_SceneIndex++;											// �� ��ȣ ++
	return newScene;
}

/// TalkingScene1(�̴ϰ����� �մԴ�ȭ)
IScene* SceneManager::CreateTalking1Scene(const std::string& sceneName)
{
	IScene* newScene = new TalkingScene1(m_SceneIndex, sceneName, this);	// ���ο� �� ����, ù ���� �ε����� 0
	m_SceneList.push_back(newScene);						// �� ����Ʈ�� ���θ��� �� ����
	m_SceneIndex++;											// �� ��ȣ ++
	return newScene;
}


/// ��ձ��ϴ� ��
IScene* SceneManager::CreateScene_Average(const std::string& sceneName)
{
	IScene* newScene = new Scene_Average(m_SceneIndex, sceneName, this);	// ���ο� �� ����, ù ���� �ε����� 0
	m_SceneList.push_back(newScene);						// �� ����Ʈ�� ���θ��� �� ����
	m_SceneIndex++;											// �� ��ȣ ++
	return newScene;
}

IScene* SceneManager::CreateScene_Spinning(const std::string& sceneName)
{
	IScene* newScene = new Scene_Spinning(m_SceneIndex, sceneName, this);	// ���ο� �� ����, ù ���� �ε����� 0
	m_SceneList.push_back(newScene);						// �� ����Ʈ�� ���θ��� �� ����
	m_SceneIndex++;											// �� ��ȣ ++
	return newScene;
}

IScene* SceneManager::CreateScene_Knitting(const std::string& sceneName)
{
	IScene* newScene = new Scene_Knitting(m_SceneIndex, sceneName, this);	// ���ο� �� ����, ù ���� �ε����� 0
	m_SceneList.push_back(newScene);						// �� ����Ʈ�� ���θ��� �� ����
	m_SceneIndex++;											// �� ��ȣ ++
	return newScene;
}

/// TalkingScene2(�̴ϰ����� �մ� ��ȭ)
IScene* SceneManager::CreateTalking2Scene(const std::string& sceneName)
{
	IScene* newScene = new TalkingScene2(m_SceneIndex, sceneName, this);	// ���ο� �� ����, ù ���� �ε����� 0
	m_SceneList.push_back(newScene);						// �� ����Ʈ�� ���θ��� �� ����
	m_SceneIndex++;											// �� ��ȣ ++
	return newScene;
}

/// EndingScene
IScene* SceneManager::CreateEndingScene(const std::string& sceneName)
{
	IScene* newScene = new EndingScene(m_SceneIndex, sceneName, this);	// ���ο� �� ����, ù ���� �ε����� 0
	m_SceneList.push_back(newScene);						// �� ����Ʈ�� ���θ��� �� ����
	m_SceneIndex++;											// �� ��ȣ ++
	return newScene;
}


IScene* SceneManager::GetScene(const int sceneNum)			// �� ��ȣ ���ڷ� �־� �� �ҷ�����
{
	for (int i = 0; i < m_SceneList.size(); i++)
	{
		if (m_SceneList[i]->GetSceneIndex() == sceneNum)
		{
			return m_SceneList[i];							
		}
	}
	return nullptr;											// Num�� �ε����� ��ġ�ϸ� �ε����� �´� �� ����
}

IScene* SceneManager::GetScene(const std::string& sceneName)	// �� �̸� ���ڷ� �־� �� �ҷ�����
{
	for (int i = 0; i < m_SceneList.size(); i++)
	{
		if (m_SceneList[i]->GetSceneName() == sceneName)
		{
			return m_SceneList[i];
		}
	}
	return nullptr;											// Num�� �ε����� ��ġ�ϸ� �ε����� �´� �� ����
}

void SceneManager::DeleteScene(const int sceneNum)
{
	for (int i = 0; i < m_SceneList.size(); i++)
	{
		if (m_SceneList[i]->GetSceneIndex() == sceneNum)
		{
			m_SceneList.erase(m_SceneList.begin() + i);		// �ε����� ��ġ�ϴ� ���� �ִٸ� �� �� ����
		}
	}
}

void SceneManager::DeleteScene(const std::string& sceneName)
{
	for (int i = 0; i < m_SceneList.size(); i++)
	{
		if (m_SceneList[i]->GetSceneName() == sceneName)
		{
			m_SceneList.erase(m_SceneList.begin() + i);		// ���� �̸��� ��ġ�ϴ� ���� �ִٸ� �� �� ����
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
	// �ش� ���� ó���� �ƴ϶�� �׸��� ����
	if (m_pNowScene!=nullptr)
	{
		m_pNowScene->SetOndrawFalse();
	}

	// ���ο� �� �׸��� ����
	m_pNowScene = GetScene(sceneNum);
	m_pNowScene->SetOndrawTrue();
}

void SceneManager::SetNowScene(const std::string& sceneName)
{
	// �ش� ���� ó���� �ƴ϶�� �׸��� ����
	if (m_pNowScene != nullptr)
	{
		m_pNowScene->SetOndrawFalse();
	}

	// ���ο� �� �׸��� ����
	m_pNowScene = GetScene(sceneName);
	m_pNowScene->SetOndrawTrue();
}
