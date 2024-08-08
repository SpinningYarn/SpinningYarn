#pragma once
#include <windows.h>
#include "Common.h"
#include "../D2DEngine/D2DEngine.h"

class SceneManager;		// 씬 매니저 전방 선언
class ObjectManager;	// 오브젝트 매니저 전방 선언
class MouseManager;



/// <summary>
/// 게임 진행의 가장 큰 단위
/// 프레임웍
/// 
/// 죄를 진 클래스 (종속성관리가 아직 잘 안돼있음)
/// 
/// 2023.02.06 YJHAll
/// </summary>
class GameProcess
{
public:
	GameProcess();						// 생성자
	~GameProcess();						// 소멸자

public:
	HRESULT Initialize(HINSTANCE hInstance);// 게임 진행 초기화

private:
	HRESULT Initialize_Window(HINSTANCE hInstance);
	void Initialize_GraphicsEngine();
	void Initialize_SceneSystem();
	void Initialize_Sprites();
	void Initialize_Sounds();

	void LoadResource();

public:
	void GameProgress();
private:
	void UpdateAll();						// 게임과 관련한 모든 것 업데이트
	void RenderAll();						// 게임과 관련한 모든 것 그리기

public:
	void Finalize();						// 게임 프로세스 종료


private:
	// win32
	HWND m_hWnd;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void RecalcWindowSize();

	// Game 관련
	
	// 싱글턴이든 뭐든 멤버로 그 객체의 포인터를 지니고 있는다.
	// 나중에 shared_pointer가 된다.
	D2DEngine* m_pD2DEngine;			// D2D 엔진을 가리키는 포인터
	SceneManager* m_pSceneManager;		// 씬 매니저를 가리키는 포인터
	MouseManager* m_pMouserManager;		// 마우스 매니저를 가리키는 포인터
	ObjectManager* m_pObjectManager;	// 오브젝트 매니저를 가리키는 포인터
	
	HCURSOR hCursor;
};

