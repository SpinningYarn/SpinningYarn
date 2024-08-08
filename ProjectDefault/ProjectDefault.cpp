#include <windows.h>
#include "GameProcess.h"
#include "../D2DEngine/D2DEngine.h"

///
/// 기본적인 형태의 Windows 프로그램 (유니코드 버전)
/// WinMain 디폴트

/// <summary>
/// 프로그램의 엔트리 포인트
/// </summary>
/// <param name="hInstance">인스턴스의 핸들 (어디에 쓸까요) </param>
/// <param name="hPrevInstance">이전 인스턴스의 핸들 (Win16의 잔재)</param>
/// <param name="lpCmdLine">프로그램 뒤에 붙이는 이낮</param>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow)
{
	GameProcess SpinningYarn;

	SpinningYarn.Initialize(hInstance);
	SpinningYarn.GameProgress();
	SpinningYarn.Finalize();

	return 0;
}

