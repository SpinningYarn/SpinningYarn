#include "GameProcess.h"

#include "SceneManager.h"
#include "MainScene.h"
#include "IntroScene.h"
#include "StageScene.h"
#include "TalkingScene1.h"
#include "Scene_Spinning.h"
#include "Scene_Knitting.h"
#include "Scene_Average.h"
#include "TalkingScene2.h"

#include "ObjectManager.h"
#include "TimerManager.h"
#include "KeyManager.h"
#include "MouseManager.h"
#include "SoundManager.h"

#include "Object.h"
#include "eObjectDefine.h"


// Key 입력 테스트용 
double TestX;
double TestY;

GameProcess::GameProcess()
	: m_hWnd(0), m_pD2DEngine(nullptr), m_pMouserManager(nullptr), m_pSceneManager(nullptr), m_pObjectManager(nullptr), hCursor(nullptr)
{

}

GameProcess::~GameProcess()
{

}

//윈도우 크기 재설정
void GameProcess::RecalcWindowSize()
{
	RECT nowRect;
	DWORD _style = (DWORD)GetWindowLong(m_hWnd, GWL_STYLE);
	DWORD _exstyle = (DWORD)GetWindowLong(m_hWnd, GWL_EXSTYLE);

	GetWindowRect(m_hWnd, &nowRect);

	RECT newRect;
	newRect.left = 0;
	newRect.top = 0;
	newRect.right = 1920;
	newRect.bottom = 1080;

	AdjustWindowRectEx(&newRect, _style, NULL, _exstyle);

	// 클라이언트 영역보다 윈도 크기는 더 커야 한다. (외곽선, 타이틀 등)
	int _newWidth = (newRect.right - newRect.left);
	int _newHeight = (newRect.bottom - newRect.top);

	SetWindowPos(m_hWnd, HWND_NOTOPMOST, nowRect.left, nowRect.top,
		_newWidth, _newHeight, SWP_SHOWWINDOW);
}

HRESULT GameProcess::Initialize(HINSTANCE hInstance)
{
	// 윈도 초기화
	HRESULT _result = Initialize_Window(hInstance);

	// 그래픽스 엔진과 그 언저리를 초기화
	Initialize_GraphicsEngine();

	// 씬 시스템을 초기화
	Initialize_SceneSystem();

	// 스프라이트 전체를 로드하고 시작
	Initialize_Sprites();

	// 사운드 시스템을 초기화
	Initialize_Sounds();

	return _result;
}

HRESULT GameProcess::Initialize_Window(HINSTANCE hInstance)
{
	/// (내가 쓸 윈도를) 등록
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;		/// 윈도 프로시저
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wcex.hCursor = LoadCursor(hInstance, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = L"Spinning Yarn";
	wcex.hIconSm = NULL;

	RegisterClassExW(&wcex);

	/// (그 윈도를) 생성
	m_hWnd = CreateWindowW(L"Spinning Yarn", L"Spinning Yarn",
		(WS_OVERLAPPED | WS_SYSMENU),
		CW_USEDEFAULT, CW_USEDEFAULT,
		1920, 1080,
		NULL, NULL,
		hInstance, NULL);

	// 윈도 핸들이 가장 중요
	if (!m_hWnd)
	{
		return S_FALSE;
	}

	ShowWindow(m_hWnd, SW_SHOWNORMAL);
	UpdateWindow(m_hWnd);

	//윈도우 크기 재설정
	RecalcWindowSize();

	//마우스 커서 이미지 변경
	hCursor = LoadCursorFromFile(L"Resources/Items/MousePointBig.cur");
}

void GameProcess::Initialize_GraphicsEngine()
{
	m_pD2DEngine = D2DEngine::GetInstance();
	m_pD2DEngine->Initialize(m_hWnd);
	TimerManager::GetInstance().Initialize();
	KeyManager::GetInstance().Initialize();

	m_pMouserManager = MouseManager::GetInstance();

	m_pObjectManager = new ObjectManager();
}

void GameProcess::Initialize_SceneSystem()
{
	/// 씬 관련
	m_pSceneManager = new SceneManager();

	IScene* _MainScene = m_pSceneManager->CreateMainScene("Main Scene");
	_MainScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::MainScreen, "메인배경화면"));				// 기본 좌표 0,0
	_MainScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::HOWTOPLAY, "게임방법"));				// 기본 좌표 0,0

	_MainScene->Initialize();

	// 대화씬1(미니게임 전)
	IScene* _Talking1Scene = m_pSceneManager->CreateTalking1Scene("TalkingScene1");
	_Talking1Scene->Initialize();

	// 대화씬2(미니게임 후)
	IScene* _Talking2Scene = m_pSceneManager->CreateTalking2Scene("TalkingScene2");
	_Talking2Scene->Initialize();
	
	// 인트로 씬
	IScene* _IntroScene = m_pSceneManager->CreateIntroScene("IntroScene");
	_IntroScene->Initialize();

	// 스테이지 소제목 씬
	IScene* _StageScene = m_pSceneManager->CreateStageScene("StageScene");
	_StageScene->Initialize();


	// 평균값 구하는 씬을 만들어서 셋팅함(Average_Scene)
	IScene* _AverageScene = m_pSceneManager->CreateScene_Average("AverageScene");
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::AverageMainScreen, "평균씬 배경화면"));				// 기본 좌표 0,0
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::EMPTYBOX1, "빈박스1", 311, 191));
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::EMPTYBOX1, "빈박스2", 311, 588));		// x,y 좌표 설정해줌
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::AVERAGEBOX, "평균박스", 1397, 384));	// x,y 좌표 설정해줌

	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::STATBOX, "스탯박스"));
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::STATBOX2, "스탯박스2"));

	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::SPIDERWEB, "거미줄"));
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::LAMBSWOOL, "램스울"));
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::COTTON, "코튼"));
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::HEMP, "삼베실"));
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::ANGORA, "앙고라털"));
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::CASHMERE, "캐시미어"));

	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::CAT_HIT, "스프라이트 테스트", 1100, 100));
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::CREDIT, "소지금", 1664, 281));
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::NextSceneButton, "다음 단계", m_pSceneManager));
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::INVENTORY, "인벤토리", m_pSceneManager));
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::SHOP, "상점"));
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::MENU, "메뉴", m_pSceneManager));
	_AverageScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::SpinningOrderMemo, "메모장", 1529, 6));

	// 두 번째 씬을 만들어서 셋팅함 (물레 씬)
	IScene* _SpinningScene = m_pSceneManager->CreateScene_Spinning("SpinningScene");
	_SpinningScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::SpinningMainScreen, "방직 메인 씬"));
	_SpinningScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::SpinningCenterObject, "물레기준점", 1082, 432));
	_SpinningScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::SpinningWheel, "방직 물레", 872, 222));
	_SpinningScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::SpinningGuideLine, "가이드 라인 화살표", 1300, 270));
	_SpinningScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::SpinningGaugeBar, "게이지 바", 692, 117));
	_SpinningScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::SpinningGaugeBall, "게이지 볼", 704, 118));
	_SpinningScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::SpinningOrderMemo, "메모장", 1529, 6));

	_SpinningScene->AddObject(_AverageScene->GetSceneObject("소지금"));
	_SpinningScene->AddObject(_AverageScene->GetSceneObject("상점"));
	_SpinningScene->AddObject(_AverageScene->GetSceneObject("메뉴"));
	_SpinningScene->AddObject(_AverageScene->GetSceneObject("인벤토리"));
	_SpinningScene->AddObject(_AverageScene->GetSceneObject("다음 단계"));

	_SpinningScene->AddObject(_AverageScene->GetSceneObject("램스울"));
	_SpinningScene->AddObject(_AverageScene->GetSceneObject("삼베실"));
	_SpinningScene->AddObject(_AverageScene->GetSceneObject("앙고라털"));
	_SpinningScene->AddObject(_AverageScene->GetSceneObject("캐시미어"));
	_SpinningScene->AddObject(_AverageScene->GetSceneObject("거미줄"));
	_SpinningScene->AddObject(_AverageScene->GetSceneObject("코튼"));

	// 세 번째 씬을 만들어서 셋팅함 (직조 씬)
	IScene* _KnittingScene = m_pSceneManager->CreateScene_Knitting("KnittingScene");
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::KnttingMainScreen, "직조 배경화면"));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::DatumPoint, "기준점"));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::StartButton, "시작하기"));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::RESULT_PRODUCT, "완성품"));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::AnswerBoard, "정답판 대기소", -1500, -1000));		// 예외처리를 위함
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::AnswerBoard, "정답판1"));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::AnswerBoard, "정답판2", 80, 0));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::AnswerBoard, "정답판3", 160, 0));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::AnswerBoard, "정답판4", 240, 0));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::AnswerBoard, "정답판5", 320, 0));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::AnswerBoard, "정답판6", 400, 0));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::AnswerBoard, "정답판7", 480, 0));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::AnswerBoard, "정답판8", 560, 0));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::Needle, "바늘"));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::Dantto, "고양이"));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::DrawBoard, "출력판"));
	_KnittingScene->AddObject(m_pObjectManager->CreateObject(eObjectDefine::SpinningOrderMemo, "메모장", 1529, 6));

	_KnittingScene->AddObject(_AverageScene->GetSceneObject("소지금"));
	_KnittingScene->AddObject(_AverageScene->GetSceneObject("상점"));
	_KnittingScene->AddObject(_AverageScene->GetSceneObject("메뉴"));
	_KnittingScene->AddObject(_AverageScene->GetSceneObject("인벤토리"));
	_KnittingScene->AddObject(_AverageScene->GetSceneObject("다음 단계"));

	_KnittingScene->AddObject(_AverageScene->GetSceneObject("램스울"));
	_KnittingScene->AddObject(_AverageScene->GetSceneObject("삼베실"));
	_KnittingScene->AddObject(_AverageScene->GetSceneObject("앙고라털"));
	_KnittingScene->AddObject(_AverageScene->GetSceneObject("캐시미어"));
	_KnittingScene->AddObject(_AverageScene->GetSceneObject("거미줄"));
	_KnittingScene->AddObject(_AverageScene->GetSceneObject("코튼"));

	/// Ending Scene
	IScene* _EndingScene = m_pSceneManager->CreateEndingScene("EndingScene");

	_AverageScene->Initialize();
	_SpinningScene->Initialize();
	_KnittingScene->Initialize();
	_EndingScene->Initialize();


	/// 처음으로 동작할 씬을 지정 해 준다.
	m_pSceneManager->SetNowScene(0);
}

//스프라이트 추가될 일 있으면 여기다 추가해
//이미지 잘라서 써야할 일 있으면 오브젝트에서 LoadSpriteFromSheet를 따로 해줘도 될듯
void GameProcess::Initialize_Sprites()
{
	m_pD2DEngine = D2DEngine::GetInstance();

	// 타이틀 화면
	m_pD2DEngine->LoadSpriteSheet("Resources/Main/Title.png", eObjectDefine::MainScreen);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::MainScreen, 0, 0, 1920, 1080, 0);

	m_pD2DEngine->LoadSpriteSheet("Resources/HowtoPlay/GameRule_Background.png", eObjectDefine::HOWTOPLAY);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::HOWTOPLAY, 0, 0, 1400, 1000, 0);

	m_pD2DEngine->LoadSpriteSheet("Resources/HowtoPlay/next_Left_GameRule.png", eObjectDefine::HTPLEFT);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::HTPLEFT, 0, 0, 64, 88, 0);

	m_pD2DEngine->LoadSpriteSheet("Resources/HowtoPlay/next_Right_GameRule.png", eObjectDefine::HTPRIGHT);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::HTPRIGHT, 0, 0, 64, 88, 0);

	m_pD2DEngine->LoadSpriteSheet("Resources/HowtoPlay/Shop_x_GameRule.png", eObjectDefine::HTPEND);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::HTPEND, 0, 0, 100, 100, 0);

	m_pD2DEngine->LoadSpriteSheet("Resources/HowtoPlay/1page.png", eObjectDefine::GAMERULE1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::GAMERULE1, 0, 0, 1400, 1000, 0);

	m_pD2DEngine->LoadSpriteSheet("Resources/HowtoPlay/3page.png", eObjectDefine::GAMERULE2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::GAMERULE2, 0, 0, 1400, 1000, 0);

	m_pD2DEngine->LoadSpriteSheet("Resources/HowtoPlay/2page.png", eObjectDefine::GAMERULE3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::GAMERULE3, 0, 0, 1400, 1000, 0);


	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/knitting.png", eObjectDefine::KnttingMainScreen);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::KnttingMainScreen, 0, 0, 1920, 1080, 0);

	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/AnswerBoard.png", eObjectDefine::AnswerBoard);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::AnswerBoard, 0, 0, 80, 80, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/UP.png", eObjectDefine::AnswerBoardUP);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::AnswerBoardUP, 0, 0, 80, 80, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/DOWN.png", eObjectDefine::AnswerBoardDOWN);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::AnswerBoardDOWN, 0, 0, 80, 80, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/LEFT.png", eObjectDefine::AnswerBoardLEFT);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::AnswerBoardLEFT, 0, 0, 80, 80, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/RIGHT.png", eObjectDefine::AnswerBoardRIGHT);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::AnswerBoardRIGHT, 0, 0, 80, 80, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/AnswerO.png", eObjectDefine::AnswerO);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::AnswerO, 0, 0, 80, 80, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/AnswerX.png", eObjectDefine::AnswerX);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::AnswerX, 0, 0, 80, 80, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/StartButton.png", eObjectDefine::StartButton);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::StartButton, 0, 0, 128, 64, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/DatumPoint.png", eObjectDefine::DatumPoint);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::DatumPoint, 0, 0, 50, 50, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/Needle.png", eObjectDefine::Needle);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Needle, 0, 0, 1024, 64, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/KnittingWork_1.png", eObjectDefine::KnittingWork_1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::KnittingWork_1, 0, 0, 640, 480, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/KnittingWork_2.png", eObjectDefine::KnittingWork_2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::KnittingWork_2, 0, 0, 640, 400, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/KnittingWork_3.png", eObjectDefine::KnittingWork_3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::KnittingWork_3, 0, 0, 640, 400, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/KnittingWork_4.png", eObjectDefine::KnittingWork_4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::KnittingWork_4, 0, 0, 640, 400, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/KnittingWork_5.png", eObjectDefine::KnittingWork_5);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::KnittingWork_5, 0, 0, 640, 400, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/NextSceneButton.png", eObjectDefine::NextSceneButton);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::NextSceneButton, 0, 0, 128, 128, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/KeyNum.png", eObjectDefine::KeyNum);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::KeyNum, 0, 0, 802, 62, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/One.png", eObjectDefine::One);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::One, 0, 0, 180, 240, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/Two.png", eObjectDefine::Two);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Two, 0, 0, 180, 240, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Knitting/Three.png", eObjectDefine::Three);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Three, 0, 0, 180, 240, 1);

	/// Cat
	m_pD2DEngine->LoadSpriteSheet("Resources/Cat/Cat_Animation_InHit.png", eObjectDefine::Cat_Stand);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Cat_Stand, 4200, 0, 700, 700, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Cat/Cat_Animation_InHit.png", eObjectDefine::Cat_Wait);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Cat_Wait, 4900, 0, 700, 700, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Cat/Cat_Animation_InHit.png", eObjectDefine::CAT_CUT1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::CAT_CUT1, 0, 0, 700, 700, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Cat/cat_back.png", eObjectDefine::CAT_CUT2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::CAT_CUT2, 0, 0, 368, 677, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Cat/Cat_Animation_InHit.png", eObjectDefine::CAT_HIT);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::CAT_HIT, 0, 0, 6300, 700, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Cat/Cat_Animation_Out.png", eObjectDefine::CAT_OUT);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::CAT_HIT, 0, 0, 5600, 700, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Cat/Cat_Animation_InHit.png", eObjectDefine::CAT_WALKK);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::CAT_WALKK, 2800, 0, 700, 700, 1);

	/// Spinning
	m_pD2DEngine->LoadSpriteSheet("Resources/SpinningMainScreen.png", eObjectDefine::SpinningMainScreen);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningMainScreen, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Spinning/SpinningWheel_2.png", eObjectDefine::SpinningWheel);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningWheel, 0, 0, 420, 420, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Spinning/SpinningGuideLine.png", eObjectDefine::SpinningGuideLine);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningGuideLine, 0, 0, 78, 118, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Spinning/SpinningGaugeBar.png", eObjectDefine::SpinningGaugeBar);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningGaugeBar, 0, 0, 600, 64, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Spinning/SpinningLineRange.png", eObjectDefine::SpinningGaugeBarRange);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningGaugeBarRange, 0, 0, 120, 60, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Spinning/SpinningGaugeBall.png", eObjectDefine::SpinningGaugeBall);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningGaugeBall, 0, 0, 600, 64, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Order/OrderMemo.png", eObjectDefine::SpinningOrderMemo);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningOrderMemo, 0, 0, 384, 256, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Order/Customer1_Order.png", eObjectDefine::SpinningOrderMemoCustomer1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningOrderMemoCustomer1, 0, 0, 384, 256, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Order/Customer2_Order.png", eObjectDefine::SpinningOrderMemoCustomer2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningOrderMemoCustomer2, 0, 0, 384, 256, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Order/Customer3_Order.png", eObjectDefine::SpinningOrderMemoCustomer3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningOrderMemoCustomer3, 0, 0, 384, 256, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Order/Customer4_Order.png", eObjectDefine::SpinningOrderMemoCustomer4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningOrderMemoCustomer4, 0, 0, 384, 256, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Order/Customer5_Order.png", eObjectDefine::SpinningOrderMemoCustomer5);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningOrderMemoCustomer5, 0, 0, 384, 256, 0);
	// ball Animation
	m_pD2DEngine->LoadSpriteSheet("Resources/Spinning/Ball_Sprite1.png", eObjectDefine::SpinningBallAnim1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningBallAnim1, 0, 0, 720, 80, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Spinning/Ball_Sprite2.png", eObjectDefine::SpinningBallAnim2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningBallAnim2, 0, 0, 720, 80, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Spinning/Ball_Sprite3.png", eObjectDefine::SpinningBallAnim3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningBallAnim3, 0, 0, 720, 80, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Spinning/Ball.png", eObjectDefine::SpinningBall);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SpinningBall, 0, 0, 120, 80, 0);

	/// Average
	m_pD2DEngine->LoadSpriteSheet("Resources/Average/Background_007.png", eObjectDefine::AverageMainScreen);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::AverageMainScreen, 0, 0, 1920, 1080, 0);

	m_pD2DEngine->LoadSpriteSheet("Resources/Average/memo2.png", eObjectDefine::EMPTYBOX1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::EMPTYBOX1, 0, 0, 256, 256, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Average/memo2_NoCountVer2.png", eObjectDefine::AVERAGEBOX_NOCOUNT);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::AVERAGEBOX_NOCOUNT, 0, 0, 256, 256, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Average/Skill.png", eObjectDefine::SKILL_NOTE);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SKILL_NOTE, 0, 0, 301, 142, 0);

	m_pD2DEngine->LoadSpriteSheet("Resources/Average/box.png", eObjectDefine::STATBOX);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::STATBOX, 0, 0, 128, 128, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Average/box.png", eObjectDefine::STATBOX2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::STATBOX2, 0, 0, 128, 128, 0);

	m_pD2DEngine->LoadSpriteSheet("Resources/Average/Spinning.png", eObjectDefine::TOSPINNING);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::TOSPINNING, 0, 0, 128, 64, 0);

	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Shop.png", eObjectDefine::SHOP_ICON);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SHOP_ICON, 0, 0, 128, 128, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Money.png", eObjectDefine::CREDIT);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::CREDIT, 0, 0, 256, 64, 1);

	m_pD2DEngine->LoadSpriteSheet("Resources/Colossus.png", eObjectDefine::COLOSSUS);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::COLOSSUS, 0, 0, 566, 441, 1);

	m_pD2DEngine->LoadSpriteSheet("Resources/Katana.png", eObjectDefine::KATANA);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::KATANA, 0, 0, 237, 217, 1);

	m_pD2DEngine->LoadSpriteSheet("Resources/box.png", eObjectDefine::ITEM_BOX);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::ITEM_BOX, 0, 0, 128, 128, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/next.png", eObjectDefine::PAGING_BUTTON);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::PAGING_BUTTON, 0, 0, 64, 100, 1);

	m_pD2DEngine->LoadSpriteSheet("Resources/Items/Shop_SpidersWeb.png", eObjectDefine::SPIDERWEB);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SPIDERWEB, 0, 0, 100, 100, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Items/Shop_Ram.png", eObjectDefine::LAMBSWOOL);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::LAMBSWOOL, 0, 0, 100, 100, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Items/Shop_Cotton.png", eObjectDefine::COTTON);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::COTTON, 0, 0, 100, 100, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Items/Shop_Hemp.png", eObjectDefine::HEMP);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::HEMP, 0, 0, 100, 100, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Items/Shop_Rabbit.png", eObjectDefine::ANGORA);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::ANGORA, 0, 0, 100, 100, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Items/Shop_Cashmere.png", eObjectDefine::CASHMERE);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::CASHMERE, 0, 0, 100, 100, 1);

	m_pD2DEngine->LoadSpriteSheet("Resources/Items/Empty/SpiderWeb_Text.png", eObjectDefine::SPIDERWEB_EMPTY);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SPIDERWEB_EMPTY, 0, 0, 200, 200, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Items/Empty/Ram_Text.png", eObjectDefine::LAMBSWOOL_EMPTY);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::LAMBSWOOL_EMPTY, 0, 0, 200, 200, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Items/Empty/Cotton_Text.png", eObjectDefine::COTTON_EMPTY);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::COTTON_EMPTY, 0, 0, 200, 200, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Items/Empty/Hemp_Text.png", eObjectDefine::HEMP_EMPTY);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::HEMP_EMPTY, 0, 0, 200, 200, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Items/Empty/Angora_Text.png", eObjectDefine::ANGORA_EMPTY);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::ANGORA_EMPTY, 0, 0, 200, 200, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Items/Empty/Cashmere_Text.png", eObjectDefine::CASHMERE_EMPTY);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::CASHMERE_EMPTY, 0, 0, 200, 200, 1);

	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Color/red.png", eObjectDefine::BACK_RED);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::BACK_RED, 0, 0, 1920, 1080, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Color/blue.png", eObjectDefine::BACK_BLUE);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::BACK_BLUE, 0, 0, 1920, 1080, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Color/green.png", eObjectDefine::BACK_GREEN);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::BACK_GREEN, 0, 0, 1920, 1080, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Color/yellow.png", eObjectDefine::BACK_YELLOW);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::BACK_YELLOW, 0, 0, 1920, 1080, 1);

	m_pD2DEngine->LoadSpriteSheet("Resources/Main/Title_x.png", eObjectDefine::MAIN_EXIT);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::MAIN_EXIT, 0, 0, 100, 100, 1);

	/// 상점관련
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Shop_Memo.png", eObjectDefine::SHOP_BACK_BOX);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SHOP_BACK_BOX, 0, 0, 256, 256, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/ItemBox.png", eObjectDefine::SHOP_ITEM_ICON);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SHOP_ITEM_ICON, 0, 0, 128, 128, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Shop_Chain.png", eObjectDefine::SHOP_CHAIN);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SHOP_CHAIN, 0, 0, 128, 128, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Shop_Back.png", eObjectDefine::SHOP_BACKGROUND_INTERFACE);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SHOP_BACKGROUND_INTERFACE, 0, 0, 1000, 1000, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Unlock.png", eObjectDefine::SHOP_UNLOCK);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SHOP_UNLOCK, 0, 0, 100, 64, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/ShopX.png", eObjectDefine::SHOP_CLOSE);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SHOP_CLOSE, 0, 0, 100, 100, 1);

	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Shop_Ram_Text.png", eObjectDefine::SHOP_LAMBSWOOL_INFO);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SHOP_LAMBSWOOL_INFO, 0, 0, 200, 200, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Shop_Hemp_Text.png", eObjectDefine::SHOP_HEMP_INFO);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SHOP_HEMP_INFO, 0, 0, 200, 200, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Shop_Angora_Text.png", eObjectDefine::SHOP_ANGORA_INFO);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SHOP_ANGORA_INFO, 0, 0, 200, 200, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Shop_Cashmere_Text.png", eObjectDefine::SHOP_CASHMERE_INFO);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SHOP_CASHMERE_INFO, 0, 0, 200, 200, 1);

	/// 메뉴관련
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Menu/menu.png", eObjectDefine::MENU_ICON);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::MENU_ICON, 0, 0, 128, 128, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Menu/BackToStart.png", eObjectDefine::MENU_RETURN_TO_START);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::MENU_RETURN_TO_START, 0, 0, 256, 64, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Menu/GameRules.png", eObjectDefine::MENU_GAMERULES);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::MENU_GAMERULES, 0, 0, 256, 64, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Menu/Menu_Window.png", eObjectDefine::MENU_BACKGROUND_INTERFACE);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::MENU_BACKGROUND_INTERFACE, 0, 0, 700, 350, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Menu/Menu_x.png", eObjectDefine::MENU_CLOSE);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::MENU_CLOSE, 0, 0, 75, 90, 1);

	/// 미니게임 관련 (성공, 실패 등)
	// 애니메이션 시트
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Fail_Sheet.png", eObjectDefine::FailAnim);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FailAnim, 0, 0, 15360, 1080, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Sucess_Sheet.png", eObjectDefine::SucessAnim);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SucessAnim, 0, 0, 15360, 1080, 1);
	// Sprite
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Fail.png", eObjectDefine::Fail);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Fail, 0, 0, 1920, 1080, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/UI/Sucess.png", eObjectDefine::Sucess);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Sucess, 0, 0, 1920, 1080, 1);

	/// Talking(대사창들 입니다)
	// Stage1
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_1.png", eObjectDefine::FIRSTSTAGE1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE1, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_2.png", eObjectDefine::FIRSTSTAGE2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE2, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_3.png", eObjectDefine::FIRSTSTAGE3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE3, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_4.png", eObjectDefine::FIRSTSTAGE4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE4, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_5.png", eObjectDefine::FIRSTSTAGE5);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE5, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_6.png", eObjectDefine::FIRSTSTAGE6);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE6, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_7.png", eObjectDefine::FIRSTSTAGE7);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE7, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_8.png", eObjectDefine::FIRSTSTAGE8);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE8, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_9.png", eObjectDefine::FIRSTSTAGE9);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE9, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_10.png", eObjectDefine::FIRSTSTAGE10);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE10, 0, 0, 1208, 458, 0);
	// 미니게임 끝난후 대사
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_11.png", eObjectDefine::FIRSTSTAGE11);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE11, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_12.png", eObjectDefine::FIRSTSTAGE12);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE12, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_13.png", eObjectDefine::FIRSTSTAGE13);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE13, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_14.png", eObjectDefine::FIRSTSTAGE14);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE14, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer1/1_15.png", eObjectDefine::FIRSTSTAGE15);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTSTAGE15, 0, 0, 1208, 458, 0);

	// Stage2
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer2/2_1.png", eObjectDefine::SECONDSTAGE1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDSTAGE1, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer2/2_2.png", eObjectDefine::SECONDSTAGE2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDSTAGE2, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer2/2_3.png", eObjectDefine::SECONDSTAGE3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDSTAGE3, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer2/2_4.png", eObjectDefine::SECONDSTAGE4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDSTAGE4, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer2/2_5.png", eObjectDefine::SECONDSTAGE5);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDSTAGE5, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer2/2_6.png", eObjectDefine::SECONDSTAGE6);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDSTAGE6, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer2/2_7.png", eObjectDefine::SECONDSTAGE7);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDSTAGE7, 0, 0, 1208, 458, 0);
	// 미니게임 끝난후 대사
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer2/2_8.png", eObjectDefine::SECONDSTAGE8);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDSTAGE8, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer2/2_9.png", eObjectDefine::SECONDSTAGE9);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDSTAGE9, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer2/2_10.png", eObjectDefine::SECONDSTAGE10);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDSTAGE10, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer2/2_11.png", eObjectDefine::SECONDSTAGE11);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDSTAGE11, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer2/2_12.png", eObjectDefine::SECONDSTAGE12);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDSTAGE12, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer2/2_13.png", eObjectDefine::SECONDSTAGE13);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDSTAGE13, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer2/2_14.png", eObjectDefine::SECONDSTAGE14);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDSTAGE14, 0, 0, 1208, 458, 0);

	// Stage3
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_1.png", eObjectDefine::THIRDSTAGE1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE1, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_2.png", eObjectDefine::THIRDSTAGE2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE2, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_3.png", eObjectDefine::THIRDSTAGE3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE3, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_4.png", eObjectDefine::THIRDSTAGE4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE4, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_5.png", eObjectDefine::THIRDSTAGE5);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE5, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_6.png", eObjectDefine::THIRDSTAGE6);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE6, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_7.png", eObjectDefine::THIRDSTAGE7);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE7, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_8.png", eObjectDefine::THIRDSTAGE8);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE8, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_9.png", eObjectDefine::THIRDSTAGE9);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE9, 0, 0, 1208, 458, 0);
	// 미니게임 끝난후 대사
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_10.png", eObjectDefine::THIRDSTAGE10);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE10, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_11.png", eObjectDefine::THIRDSTAGE11);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE11, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_12.png", eObjectDefine::THIRDSTAGE12);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE12, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_13.png", eObjectDefine::THIRDSTAGE13);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE13, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_14.png", eObjectDefine::THIRDSTAGE14);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE14, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_15.png", eObjectDefine::THIRDSTAGE15);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE15, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer3/3_16.png", eObjectDefine::THIRDSTAGE16);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDSTAGE16, 0, 0, 1208, 458, 0);

	// Stage4
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_1.png", eObjectDefine::FOURTHSTAGE1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE1, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_2.png", eObjectDefine::FOURTHSTAGE2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE2, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_3.png", eObjectDefine::FOURTHSTAGE3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE3, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_4.png", eObjectDefine::FOURTHSTAGE4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE4, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_5.png", eObjectDefine::FOURTHSTAGE5);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE5, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_6.png", eObjectDefine::FOURTHSTAGE6);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE6, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_7.png", eObjectDefine::FOURTHSTAGE7);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE7, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_8.png", eObjectDefine::FOURTHSTAGE8);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE8, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_9.png", eObjectDefine::FOURTHSTAGE9);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE9, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_10.png", eObjectDefine::FOURTHSTAGE10);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE10, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_11.png", eObjectDefine::FOURTHSTAGE11);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE11, 0, 0, 1208, 458, 0);
	// 미니게임 끝난후 대사
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_12.png", eObjectDefine::FOURTHSTAGE12);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE12, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_13.png", eObjectDefine::FOURTHSTAGE13);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE13, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_14.png", eObjectDefine::FOURTHSTAGE14);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE14, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_15.png", eObjectDefine::FOURTHSTAGE15);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE15, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_16.png", eObjectDefine::FOURTHSTAGE16);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE16, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_17.png", eObjectDefine::FOURTHSTAGE17);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE17, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_18.png", eObjectDefine::FOURTHSTAGE18);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE18, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer4/4_19.png", eObjectDefine::FOURTHSTAGE19);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHSTAGE19, 0, 0, 1208, 458, 0);

	// Stage 5
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_1.png", eObjectDefine::FIFTHSTAGE1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE1, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_2.png", eObjectDefine::FIFTHSTAGE2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE2, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_3.png", eObjectDefine::FIFTHSTAGE3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE3, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_4.png", eObjectDefine::FIFTHSTAGE4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE4, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_5.png", eObjectDefine::FIFTHSTAGE5);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE5, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_6.png", eObjectDefine::FIFTHSTAGE6);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE6, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_7.png", eObjectDefine::FIFTHSTAGE7);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE7, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_8.png", eObjectDefine::FIFTHSTAGE8);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE8, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_9.png", eObjectDefine::FIFTHSTAGE9);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE9, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_10.png", eObjectDefine::FIFTHSTAGE10);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE10, 0, 0, 1208, 458, 0);
	// 미니게임 끝난후 대사
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_11.png", eObjectDefine::FIFTHSTAGE11);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE11, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_12.png", eObjectDefine::FIFTHSTAGE12);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE12, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_13.png", eObjectDefine::FIFTHSTAGE13);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE13, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_14.png", eObjectDefine::FIFTHSTAGE14);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE14, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_15.png", eObjectDefine::FIFTHSTAGE15);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE15, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_16.png", eObjectDefine::FIFTHSTAGE16);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE16, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_17.png", eObjectDefine::FIFTHSTAGE17);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE17, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_18.png", eObjectDefine::FIFTHSTAGE18);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE18, 0, 0, 1208, 458, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Customer5/5_19.png", eObjectDefine::FIFTHSTAGE19);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHSTAGE19, 0, 0, 1208, 458, 0);

	/// 스테이지 별 의뢰인들
	m_pD2DEngine->LoadSpriteSheet("Resources/BackGround.png", eObjectDefine::TALKINGBACKGROUND);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::TALKINGBACKGROUND, 0, 0, 1920, 1080, 0);
	// stage1
	m_pD2DEngine->LoadSpriteSheet("Resources/Character1/Character1_1.png", eObjectDefine::FIRSTCHARACTER1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTCHARACTER1, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Character1/Character1_2.png", eObjectDefine::FIRSTCHARACTER2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIRSTCHARACTER2, 0, 0, 1920, 1080, 0);
	// stage 2
	m_pD2DEngine->LoadSpriteSheet("Resources/Character2/Character2_1.png", eObjectDefine::SECONDCHARACTER1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDCHARACTER1, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Character2/Character2_2.png", eObjectDefine::SECONDCHARACTER2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::SECONDCHARACTER2, 0, 0, 1920, 1080, 0);
	// stage3
	m_pD2DEngine->LoadSpriteSheet("Resources/Character3/Character3_1.png", eObjectDefine::THIRDCHARACTER1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDCHARACTER1, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Character3/Character3_2.png", eObjectDefine::THIRDCHARACTER2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THIRDCHARACTER2, 0, 0, 1920, 1080, 0);
	// stage4
	m_pD2DEngine->LoadSpriteSheet("Resources/Character4/Character4_1.png", eObjectDefine::FOURTHCHARACTER1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHCHARACTER1, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Character4/Character4_2.png", eObjectDefine::FOURTHCHARACTER2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FOURTHCHARACTER2, 0, 0, 1920, 1080, 0);
	// stage5
	m_pD2DEngine->LoadSpriteSheet("Resources/Character5/Character5_1.png", eObjectDefine::FIFTHCHARACTER1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHCHARACTER1, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Character5/Character5_2.png", eObjectDefine::FIFTHCHARACTER2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::FIFTHCHARACTER2, 0, 0, 1920, 1080, 0);

	/// Intro
	// CutScene
	m_pD2DEngine->LoadSpriteSheet("Resources/Intro/Opening_1.png", eObjectDefine::INTROCUTSCENE1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::INTROCUTSCENE1, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Intro/Opening_2.png", eObjectDefine::INTROCUTSCENE2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::INTROCUTSCENE2, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Intro/Opening_3.png", eObjectDefine::INTROCUTSCENE3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::INTROCUTSCENE3, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Intro/Opening_4.png", eObjectDefine::INTROCUTSCENE4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::INTROCUTSCENE4, 0, 0, 1920, 1080, 0);

	// Script
	m_pD2DEngine->LoadSpriteSheet("Resources/Intro/Text/Opening_Text_1.png", eObjectDefine::INTROSCRIPT1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::INTROSCRIPT1, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Intro/Text/Opening_Text_2.png", eObjectDefine::INTROSCRIPT2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::INTROSCRIPT2, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Intro/Text/Opening_Text_3.png", eObjectDefine::INTROSCRIPT3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::INTROSCRIPT3, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Intro/Text/Opening_Text_4.png", eObjectDefine::INTROSCRIPT4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::INTROSCRIPT4, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Intro/Text/Opening_Text_5.png", eObjectDefine::INTROSCRIPT5);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::INTROSCRIPT5, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Intro/Text/Opening_Text_6.png", eObjectDefine::INTROSCRIPT6);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::INTROSCRIPT6, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Intro/Text/Opening_Text_7.png", eObjectDefine::INTROSCRIPT7);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::INTROSCRIPT7, 0, 0, 1920, 1080, 0);

	/// Chapter Sprite
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter1/Chapter1_Sheet1.png", eObjectDefine::Chapter1Title1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter1Title1, 0, 0, 1920, 14040, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter1/Chapter1_Sheet2.png", eObjectDefine::Chapter1Title2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter1Title2, 0, 0, 1920, 12960, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter1/Chapter1_Sheet3.png", eObjectDefine::Chapter1Title3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter1Title3, 0, 0, 1920, 12960, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter1/Chapter1_Sheet4.png", eObjectDefine::Chapter1Title4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter1Title4, 0, 0, 1920, 11880, 1);

	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter2/Chapter2_Sheet1.png", eObjectDefine::Chapter2Title1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter2Title1, 0, 0, 1920, 14040, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter2/Chapter2_Sheet2.png", eObjectDefine::Chapter2Title2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter2Title2, 0, 0, 1920, 12960, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter2/Chapter2_Sheet3.png", eObjectDefine::Chapter2Title3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter2Title3, 0, 0, 1920, 12960, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter2/Chapter2_Sheet4.png", eObjectDefine::Chapter2Title4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter2Title4, 0, 0, 1920, 11880, 1);

	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter3/Chapter3_Sheet1.png", eObjectDefine::Chapter3Title1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter3Title1, 0, 0, 1920, 14040, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter3/Chapter3_Sheet2.png", eObjectDefine::Chapter3Title2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter3Title2, 0, 0, 1920, 12960, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter3/Chapter3_Sheet3.png", eObjectDefine::Chapter3Title3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter3Title3, 0, 0, 1920, 12960, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter3/Chapter3_Sheet4.png", eObjectDefine::Chapter3Title4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter3Title4, 0, 0, 1920, 11880, 1);

	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter4/Chapter4_Sheet1.png", eObjectDefine::Chapter4Title1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter4Title1, 0, 0, 1920, 14040, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter4/Chapter4_Sheet2.png", eObjectDefine::Chapter4Title2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter4Title2, 0, 0, 1920, 12960, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter4/Chapter4_Sheet3.png", eObjectDefine::Chapter4Title3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter4Title3, 0, 0, 1920, 12960, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter4/Chapter4_Sheet4.png", eObjectDefine::Chapter4Title4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter4Title4, 0, 0, 1920, 11880, 1);

	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter5/Chapter5_Sheet1.png", eObjectDefine::Chapter5Title1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter5Title1, 0, 0, 1920, 14040, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter5/Chapter5_Sheet2.png", eObjectDefine::Chapter5Title2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter5Title2, 0, 0, 1920, 12960, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter5/Chapter5_Sheet3.png", eObjectDefine::Chapter5Title3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter5Title3, 0, 0, 1920, 12960, 1);
	m_pD2DEngine->LoadSpriteSheet("Resources/Chapter_sprite/Chapter5/Chapter5_Sheet4.png", eObjectDefine::Chapter5Title4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::Chapter5Title4, 0, 0, 1920, 11880, 1);

	/// Ending Scene
	m_pD2DEngine->LoadSpriteSheet("Resources/Ending_UI/Ending_1.png", eObjectDefine::EndingScene1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::EndingScene1, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Ending_UI/Ending_2.png", eObjectDefine::EndingScene2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::EndingScene2, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Ending_UI/Ending_3.png", eObjectDefine::EndingScene3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::EndingScene3, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Ending_UI/Ending_4.png", eObjectDefine::EndingScene4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::EndingScene4, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Ending_UI/Ending_5.png", eObjectDefine::EndingScene5);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::EndingScene5, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Ending_UI/Ending_6.png", eObjectDefine::EndingScene6);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::EndingScene6, 0, 0, 1920, 1080, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/Ending_UI/Ending_7.png", eObjectDefine::EndingScene7);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::EndingScene7, 0, 0, 1920, 1080, 0);

	/// Ending Sprite
	m_pD2DEngine->LoadSpriteSheet("Resources/EndingCredit/Credit_1.png", eObjectDefine::EndingSprite1);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::EndingSprite1, 0, 0, 1920, 12960, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/EndingCredit/Credit_2.png", eObjectDefine::EndingSprite2);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::EndingSprite2, 0, 0, 1920, 12960, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/EndingCredit/Credit_3.png", eObjectDefine::EndingSprite3);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::EndingSprite3, 0, 0, 1920, 12960, 0);
	m_pD2DEngine->LoadSpriteSheet("Resources/EndingCredit/Credit_4.png", eObjectDefine::EndingSprite4);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::EndingSprite4, 0, 0, 1920, 12960, 0);

	/// THANKYOU
	m_pD2DEngine->LoadSpriteSheet("Resources/EndingCredit/Credit_47.png", eObjectDefine::THANKYOU);
	m_pD2DEngine->LoadSpriteFromSheet(eObjectDefine::THANKYOU, 0, 0, 1920, 1080, 0);
}


// 사운드 초기화(여기에 사운드들을 생성한다)
void GameProcess::Initialize_Sounds()
{
	SoundManager::GetInstance().SystemInitialize();

	SoundManager::GetInstance().CreateBGM("Resources/Sound/BGM_Title.wav", MainBGM, true);
	SoundManager::GetInstance().CreateBGM("Resources/Sound/BGM_Ingame_(50%).wav", IngameBGM, true);
	SoundManager::GetInstance().CreateBGM("Resources/Sound/BGM_Ingame2(50%).wav", Chapter4BGM, true);
	SoundManager::GetInstance().CreateBGM("Resources/Sound/BGM_Ending.wav", EndingBGM, true);
	SoundManager::GetInstance().CreateBGM("Resources/Sound/BGM_Opening(50%).wav", OpenningBGM, true);
	SoundManager::GetInstance().CreateBGM("Resources/Sound/MerryGoRound/SE_Wheeling.wav", MerryGoRound, true);
	SoundManager::GetInstance().CreateBGM("Resources/Sound/Chapter_Change.wav", ChapterChangeBGM, false);

	SoundManager::GetInstance().CreateSound("Resources/Sound/SE_ButtonClick_(Mouse Click by HunteR4708 Id-256455.wav", Click, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/Effect/SE_Next.wav", NextScene, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/Click/SE_DialogClick.wav", DialogSound, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/SE_Unlock_75%.wav", UnlockItem, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/Effect/SE_Wrong_(CARTOON-BING-VOCAL1.wav", KnittingFail, false);

	SoundManager::GetInstance().CreateSound("Resources/Sound/Knitting/SE_Knit_Reverse.wav", BackLine, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/Knitting/SE_Knit1.wav", Knitting1, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/Knitting/SE_Knit2.wav", Knitting2, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/Knitting/SE_Knit3.wav", Knitting3, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/Knitting/SE_Knit4.wav", Knitting4, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/Knitting/SE_Knit5.wav", Knitting5, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/Knitting/SE_Knit6.wav", Knitting6, false);
	

	SoundManager::GetInstance().CreateSound("Resources/Sound/Cat/SE_Cat_Meow Short by skymary Id-412017.wav", Nyangko1, false);	// 여러개야함
	SoundManager::GetInstance().CreateSound("Resources/Sound/Cat/SE_Cat_Meowing by lextrack Id-333916.wav", Nyangko2, false);	// 여러개야함
	SoundManager::GetInstance().CreateSound("Resources/Sound/Cat/SE_Cat_Meowing X5 by peridactyloptrix Id-214759.wav", Nyangko3, false);	// 여러개야함
	
	SoundManager::GetInstance().CreateSound("Resources/Sound/SE_Cat Purr_50%.wav", NyangkoClick, false);

	SoundManager::GetInstance().CreateSound("Resources/Sound/Cat/interrupt/SE_Cat_Shake(shakes-02-22688.wav", NyangkoPunch1, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/Cat/interrupt/SE_Cat_Shake(tbox-of-matches-30413.wav", NyangkoPunch1, false);

	SoundManager::GetInstance().CreateSound("Resources/Sound/Effect/SE_Correct_(vol.8 예능자막 관련 Sound Pack_2.wav", Success, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/Effect/SE_TryAgain_(vol.8 예능자막 관련 Sound Pack_6.wav", Fail, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/MerryGoRound/SE_FiberDrag.wav", Drag, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/MerryGoRound/SE_FiberDrop(Water Click by Mafon2 Id-371274).wav", Drop, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/Effect/SE_CustomerIn_(shop-door-bell-6405.wav", CustomerIn1, false);
	SoundManager::GetInstance().CreateSound("Resources/Sound/Effect/SE_CustomerPay_(CASINO-CHIPS-TOSS-MANY1.wav", CustomerBye1, false);

}

void GameProcess::LoadResource()
{

}

void GameProcess::GameProgress()
{
	/// 무한루프 (안에 메시지 루프와 게임 루프 등이 포함됨)
	TimerManager::GetInstance().StartUpdate();

	/// 메시지 루프
	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) break;
			DispatchMessage(&msg);
		}
		else
		{
			// 메시지 처리 등을 하지 않을 때 (시간이 남을 때)

			/// 게임 루프 본체
			UpdateAll();
			RenderAll();

			SoundManager::GetInstance().SoundUpdate();
			MouseManager::GetInstance()->OneClickEnd();
			TimerManager::GetInstance().EndUpdate();
			TimerManager::GetInstance().StartUpdate();
		}
	}
}

void GameProcess::UpdateAll()
{
	KeyManager::GetInstance().Update();
	m_pMouserManager->Update();
	m_pSceneManager->Update();

	SetCursor(hCursor);				//화면 밖으로 갔다오면 초기화되서 업데이트에 넣어놨음
}

void GameProcess::RenderAll()
{
	m_pD2DEngine->BeginDraw();

	/// 이렇게 넣는게 좋을 듯 ? 
	m_pSceneManager->Render();

	m_pD2DEngine->EndDraw();
}

void GameProcess::Finalize()
{
	m_pD2DEngine->Release();
}

/// 윈도 메시지를 처리 할 메시지 프로시저
// 가능하면, 메시지 프로시저를 만들어서 작동하게 한다.
LRESULT CALLBACK GameProcess::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_MOUSEMOVE:
		{
			MouseManager::GetInstance()->Initialize(lParam);
			MouseManager::GetInstance()->GetLeftButtonUpChangeState(false);
			MouseManager::GetInstance()->GetRightButtonUpChangeState(false);
		}
		break;

		case WM_LBUTTONDOWN:
		{
			MouseManager::GetInstance()->GetLeftButtonDownChangeState(true);
			MouseManager::GetInstance()->GetLeftButtonUpChangeState(false);
		}
		break;

		case WM_LBUTTONUP:
		{
			MouseManager::GetInstance()->GetLeftButtonDownChangeState(false);
			MouseManager::GetInstance()->GetLeftButtonUpChangeState(true);
		}
		break;

		case WM_RBUTTONDOWN:
		{
			MouseManager::GetInstance()->GetRightButtonDownChangeState(true);
			MouseManager::GetInstance()->GetRightButtonUpChangeState(false);
		}
		break;

		case WM_RBUTTONUP:
		{
			MouseManager::GetInstance()->GetRightButtonDownChangeState(false);
			MouseManager::GetInstance()->GetRightButtonUpChangeState(true);
		}
		break;

		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

		default:
		{
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	return 0;
}
