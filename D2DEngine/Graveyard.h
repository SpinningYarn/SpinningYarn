#pragma once

/// �ҽ����� ����

/// ������ ���� ��

/// 2023.02.06

// 	/// ���ø��� ����Ҷ� ����� cpp�� �и��ϸ� ��ũ ������ ���ٴ� ���� ���� �Ұ����ϰ� ����� �����Ͽ���
// 	
// 	template <typename T>								// ���ø� ����
// 	Scene* GetScene(const T& sceneInfo)					// Ư�� �� �������� (���ø��� Ȱ���Ͽ� �پ��� ���� �޵���)
// 	{
// 		for (int i = 0; i < m_SceneList.size(); i++)
// 		{
// 			if ((m_SceneList[i]->GetSceneIndex() == sceneInfo) || (m_SceneList[i]->GetSceneName() == sceneInfo))	// �� �� �ϳ��� �����ϸ�
// 			{
// 				return m_SceneList[i];
// 			}
// 		}
// 		return nullptr;
// 	}
// 	
// 	template <typename T>								// ���ø� ����
// 	void DeleteScene(const T& sceneInfo)				// Ư�� �� ���� (���ø��� Ȱ���Ͽ� �پ��� ���� �޵���)
// 	{
// 		for (int i = 0; i < m_SceneList.size(); i++)
// 		{
// 			if (m_SceneList[i]->GetSceneName() == sceneInfo || m_SceneList[i]->GetSceneIndex() == sceneInfo)
// 			{
// 				m_SceneList.erase(m_SceneList.begin() + i);		// ���� �̸��� ��ġ�ϴ� ���� �ִٸ� �� �� ����
// 			}
// 		}
// 	}