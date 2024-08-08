#pragma once

/// 소스들의 무덤

/// 죽으면 가는 곳

/// 2023.02.06

// 	/// 템플릿을 사용할때 헤더와 cpp를 분리하면 링크 에러가 난다는 글을 봐서 불가피하게 헤더에 선언하였음
// 	
// 	template <typename T>								// 템플릿 선언
// 	Scene* GetScene(const T& sceneInfo)					// 특정 씬 가져오기 (템플릿을 활용하여 다양한 변수 받도록)
// 	{
// 		for (int i = 0; i < m_SceneList.size(); i++)
// 		{
// 			if ((m_SceneList[i]->GetSceneIndex() == sceneInfo) || (m_SceneList[i]->GetSceneName() == sceneInfo))	// 둘 중 하나에 만족하면
// 			{
// 				return m_SceneList[i];
// 			}
// 		}
// 		return nullptr;
// 	}
// 	
// 	template <typename T>								// 템플릿 선언
// 	void DeleteScene(const T& sceneInfo)				// 특정 씬 삭제 (템플릿을 활용하여 다양한 변수 받도록)
// 	{
// 		for (int i = 0; i < m_SceneList.size(); i++)
// 		{
// 			if (m_SceneList[i]->GetSceneName() == sceneInfo || m_SceneList[i]->GetSceneIndex() == sceneInfo)
// 			{
// 				m_SceneList.erase(m_SceneList.begin() + i);		// 인자 이름과 일치하는 씬이 있다면 그 씬 삭제
// 			}
// 		}
// 	}