#include "IScene.h"
#include "Object.h"


IScene::IScene(const int sceneNum, std::string sceneName, SceneManager* pSceneManager)
	: m_Index(sceneNum), m_Name(sceneName), m_pSceneManager(pSceneManager), m_Ondraw(false)
{

}

IScene::~IScene()
{

}

void IScene::SortObjectList()
{
	if (m_SceneObjectList.size() > 0)
	{
		int i;
		int j;

		for (i = 0; i < m_SceneObjectList.size(); i++)
		{
			Object* iter = m_SceneObjectList[i];
			for (j = i - 1; j >= 0 && m_SceneObjectList[j]->renderOrder > iter->renderOrder; j--)
			{
				m_SceneObjectList[j + 1] = m_SceneObjectList[j];
			}
			m_SceneObjectList[j + 1] = iter;
		}
	}
}

bool IScene::GetOndraw()
{
	return m_Ondraw;
}

void IScene::SetOndrawTrue()
{
	m_Ondraw = true;
}

void IScene::SetOndrawFalse()
{
	m_Ondraw = false;
}

void IScene::OnUpdate()
{
	for (int i = 0; i < m_SceneObjectList.size(); i++)
	{
		m_SceneObjectList[i]->UpdateObject();
	}
}

void IScene::OnRender()
{
	SortObjectList();

	for (int i = 0; i < m_SceneObjectList.size(); i++)
	{
		m_SceneObjectList[i]->RenderObject();
	}
}

const int IScene::GetSceneIndex()
{
	return m_Index;
}

const std::string& IScene::GetSceneName()
{
	return m_Name;
}

void IScene::AddObject(Object* pObject)
{
	m_SceneObjectList.push_back(pObject);
}

Object* IScene::GetSceneObject(const int objectIndex)
{
	for (int i = 0; i < m_SceneObjectList.size(); i++)
	{
		if (m_SceneObjectList[i]->GetObjectIndex() == objectIndex)
		{
			return m_SceneObjectList[i];		// ���� ��ȣ�� ��ġ�ϴ� ������Ʈ�� �ִٸ� �� �� ����
		}
	}
	return nullptr;
}

Object* IScene::GetSceneObject(const std::string& objectName)
{
	for (int i = 0; i < m_SceneObjectList.size(); i++)
	{
		if (m_SceneObjectList[i]->GetObjectName() == objectName)
		{
			return m_SceneObjectList[i];		// ���� �̸��� ��ġ�ϴ� ������Ʈ�� �ִٸ� �� �� ����
		}
	}
	return nullptr;
}

void IScene::RemoveObject(const int objectIndex)
{
	for (int i = 0; i < m_SceneObjectList.size(); i++)
	{
		if (m_SceneObjectList[i]->GetObjectIndex() == objectIndex)
		{
			m_SceneObjectList.erase(m_SceneObjectList.begin() + i);		// ���� ��ȣ�� ��ġ�ϴ� ������Ʈ�� �ִٸ� �� �� ����
		}
	}
}

void IScene::RemoveObject(const std::string& objectName)
{
	for (int i = 0; i < m_SceneObjectList.size(); i++)
	{
		if (m_SceneObjectList[i]->GetObjectName() == objectName)
		{
			m_SceneObjectList.erase(m_SceneObjectList.begin() + i);		// ���� �̸��� ��ġ�ϴ� ������Ʈ�� �ִٸ� �� �� ����
		}
	}
}
