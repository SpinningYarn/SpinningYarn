#pragma once
#include <windows.h>
#include "Common.h"
#include "../D2DEngine/D2DEngine.h"

class SceneManager;		// �� �Ŵ��� ���� ����
class ObjectManager;	// ������Ʈ �Ŵ��� ���� ����
class MouseManager;



/// <summary>
/// ���� ������ ���� ū ����
/// �����ӿ�
/// 
/// �˸� �� Ŭ���� (���Ӽ������� ���� �� �ȵ�����)
/// 
/// 2023.02.06 YJHAll
/// </summary>
class GameProcess
{
public:
	GameProcess();						// ������
	~GameProcess();						// �Ҹ���

public:
	HRESULT Initialize(HINSTANCE hInstance);// ���� ���� �ʱ�ȭ

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
	void UpdateAll();						// ���Ӱ� ������ ��� �� ������Ʈ
	void RenderAll();						// ���Ӱ� ������ ��� �� �׸���

public:
	void Finalize();						// ���� ���μ��� ����


private:
	// win32
	HWND m_hWnd;

	static LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	void RecalcWindowSize();

	// Game ����
	
	// �̱����̵� ���� ����� �� ��ü�� �����͸� ���ϰ� �ִ´�.
	// ���߿� shared_pointer�� �ȴ�.
	D2DEngine* m_pD2DEngine;			// D2D ������ ����Ű�� ������
	SceneManager* m_pSceneManager;		// �� �Ŵ����� ����Ű�� ������
	MouseManager* m_pMouserManager;		// ���콺 �Ŵ����� ����Ű�� ������
	ObjectManager* m_pObjectManager;	// ������Ʈ �Ŵ����� ����Ű�� ������
	
	HCURSOR hCursor;
};

