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
/// �׷��Ƚ� ����
/// </summary>

class D2DEngine
{
private:
	D2DEngine();
	~D2DEngine();
public:
	static D2DEngine* GetInstance()			//���� ����ƽ�̴�		Ŭ���� ����ƽ ���
	{
		static D2DEngine sD2DEngine;
		return &sD2DEngine;
	}
private:
	//Factory�� RenderTarget ���� ����
	ID2D1Factory* pD2DFactory;	//Direct2D���� ����ϴ� ���ҽ��� ������ �� �ִ� �������̽� ����
	ID2D1HwndRenderTarget* pRenderTarget = NULL;	//Factory�� ������ ���ҽ��� ��� �׸� ������ �������ִ� ����
	IDWriteFactory5* pWriteFactory;					//���ڿ��� ����ϱ� ���� Factory
	IDWriteTextFormat* pTextFormat;
	IDWriteTextFormat* pTextFormatLarger;
	IDWriteFontFile* pFontFile;						//��Ʈ ������ �ޱ� ���� ��ü
	IDWriteFontSetBuilder1* pFontSetBuilder;		//��Ʈ ���Ϸκ��� FontSet�� ����� ��ü
	IDWriteFontSet* pFontSet;						//��Ʈ �ݷ��ǿ� ��Ʈ ������ �־��ֱ� ����
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
	//��Ʈ�� ����
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
	//��������Ʈ ����
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

	//��Ʈ�� ��� ����
	wchar_t* ConvertCStoWCS(const char* origin);

	//�׸��� �׸��� ���� ���������� ����ϴ� �κ�
	int LoadSpriteSheet(const char* filepath, eObjectDefine eOD);
	int LoadSpriteSheet(const wchar_t* filepath, eObjectDefine eOD);
	DRSprite* LoadSpriteFromSheet(eObjectDefine eOD, int oriX, int oriY, int width, int height, int delayFrame);
	void DrawSprite(eObjectDefine eOD, float dstX, float dstY, float rotateScale = 0.0f);
	void DrawSpriteAlpha(eObjectDefine eOD, float dstX, float dstY, float opacity, float rotateScale = 0.0f);
	void DrawSpriteCut(eObjectDefine eOD, float dstX, float dstY, int cutY, float rotateScale = 0.0f);
	
	///�ӽ�
	D2DSprite* LoadSpriteFromSheet2(eObjectDefine eOD, int oriX, int oriY, int width, int height, int delayFrame);
	void DrawSprite(int index, int dstX, int dstY, vector<D2DSprite*> aniList, float rotateScale = 0.0f);

	void DrawText1(int posX, int posY, const char* txt);
	void DrawText2(int posX, int posY, const char* txt);
	void DrawText3(int posX, int posY, const char* txt);

	//
	void DrawSprite(DRSprite* sprite, int dstX, int dstY);
};

