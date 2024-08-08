#pragma once

#include <windows.h>
#include <d2d1.h>
#include <wincodec.h>       
#include <map>
#include <dwrite.h>
#include <dwrite_3.h>
#include "D2DSprite.h"
#include "../ProjectDefault/Common.h"
#include "../ProjectDefault/Object.h"
#include "../ProjectDefault/eObjectDefine.h"
#pragma comment(lib, "D2D1.lib")
#pragma comment(lib, "dwrite.lib")
using namespace std;

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define HINST_THISCOMPONENT ((HINSTANCE)&__ImageBase)

/// <summary>
/// 그래픽스 엔진
/// </summary>

class D2DEngine
{
private:
	D2DEngine();
	~D2DEngine();
public:
	static D2DEngine* GetInstance()			//지역 스태틱이다		클래스 스태틱 멤버
	{
		static D2DEngine sD2DEngine;
		return &sD2DEngine;
	}
private:
	//Factory와 RenderTarget 변수 선언
	ID2D1Factory* pD2DFactory;	//Direct2D에서 사용하는 리소스를 생성할 수 있는 인터페이스 제공
	ID2D1HwndRenderTarget* pRenderTarget = NULL;	//Factory로 생성한 리소스를 어디에 그릴 것인지 지정해주는 역할
	IDWriteFactory5* pWriteFactory;					//문자열을 출력하기 위한 Factory
	IDWriteTextFormat* pTextFormat;
	IDWriteTextFormat* pTextFormatLarger;
	IDWriteFontFile* pFontFile;						//폰트 파일을 받기 위한 객체
	IDWriteFontSetBuilder1* pFontSetBuilder;		//폰트 파일로부터 FontSet을 만드는 객체
	IDWriteFontSet* pFontSet;						//폰트 콜렉션에 폰트 정보를 넣어주기 위한
	IDWriteFontCollection1* pFontCollection;
	ID2D1SolidColorBrush* pBlackBrush = NULL;
	ID2D1SolidColorBrush* pRedBrush = NULL;
	ID2D1SolidColorBrush* pBlueBrush = NULL;
	ID2D1SolidColorBrush* pGreenBrush = NULL;

	IDWriteTextFormat* pTextFormatKaturi;
	IDWriteFontFile* pFontFileKaturi;
	IDWriteFontSetBuilder1* pFontSetBuilderKaturi;
	IDWriteFontCollection1* pFontCollectionKaturi;
	IDWriteFontSet* pFontSetKaturi;

	IDWriteTextFormat* pTextFormatElice;
	IDWriteFontFile* pFontFileElice;
	IDWriteFontSetBuilder1* pFontSetBuilderElice;
	IDWriteFontCollection1* pFontCollectionElice;
	IDWriteFontSet* pFontSetElice;

private:
	//비트맵 관련
	IWICImagingFactory* pWICFactory;
	ID2D1Bitmap* pBitmap;

	HRESULT LoadBitmapFromFile(
		ID2D1RenderTarget* pRenderTarget,
		IWICImagingFactory* pIWICFactory,
		PCWSTR uri,
		UINT destinationWidth,
		UINT destinationHeight,
		ID2D1Bitmap** ppBitmap
	);

private:
	//스프라이트 관련
	int mSpriteCount;
	int mSpriteSheetCount;
	vector<D2DSprite*> mSpriteInfos;
	map<int, ID2D1Bitmap*> mSpriteSheets;

	D2D1_SIZE_F m_RenderTargetSize;
	vector<DRSprite*> m_SpritePool;

public:
	void Initialize(HWND hWnd);
	void BeginDraw();
	void EndDraw();
	void Release();

	void DrawText(int posX, int posY, WCHAR* txt);
	void DrawText(int posX, int posY, const char* txt);
	void DrawText(int posX, int posY, int txt);
	void DrawTextLarge(int posX, int posY, const char* txt);
	void DrawTextLarge(int posX, int posY, int txt);
	void DrawTextInt(int posX, int posY, int txt);

	void DrawRect(int srcX, int srcY, int dstX, int dstY);
	void DrawLine(int srcX, int srcY, int dstX, int dstY, float width);
	void DrawEllipse(int posX, int posY, int radius);

	//비트맵 출력 과정
	wchar_t* ConvertCStoWCS(const char* origin);

	//그림을 그리기 위해 실질적으로 사용하는 부분
	int LoadSpriteSheet(const char* filepath, eObjectDefine eOD);
	int LoadSpriteSheet(const wchar_t* filepath, eObjectDefine eOD);
	DRSprite* LoadSpriteFromSheet(eObjectDefine eOD, int oriX, int oriY, int width, int height, int delayFrame);
	void DrawSprite(eObjectDefine eOD, float dstX, float dstY, float rotateScale = 0.0f);
	void DrawSpriteAlpha(eObjectDefine eOD, float dstX, float dstY, float opacity, float rotateScale = 0.0f);
	void DrawSpriteCut(eObjectDefine eOD, float dstX, float dstY, int cutY, float rotateScale = 0.0f);
	
	///임시
	D2DSprite* LoadSpriteFromSheet2(eObjectDefine eOD, int oriX, int oriY, int width, int height, int delayFrame);
	void DrawSprite(int index, int dstX, int dstY, vector<D2DSprite*> aniList, float rotateScale = 0.0f);

	void DrawText1(int posX, int posY, const char* txt);
	void DrawText2(int posX, int posY, const char* txt);
	void DrawText3(int posX, int posY, const char* txt);

	//
	void DrawSprite(DRSprite* sprite, int dstX, int dstY);
};

