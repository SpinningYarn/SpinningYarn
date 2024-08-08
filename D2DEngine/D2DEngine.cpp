#include "D2DEngine.h"
#pragma comment(lib, "windowscodecs.lib")

RECT rt;

D2DEngine::D2DEngine()
	:pD2DFactory(nullptr),
	pRenderTarget(nullptr),
	pBlackBrush(nullptr), pBlueBrush(nullptr), pRedBrush(nullptr), pGreenBrush(nullptr),
	pWICFactory(nullptr),
	pBitmap(nullptr),
	pFontFile(nullptr),
	pFontCollection(nullptr),
	mSpriteCount(0), mSpriteSheetCount(0),
	m_RenderTargetSize(D2D1_SIZE_F())
{

}

D2DEngine::~D2DEngine()
{
	
}

void D2DEngine::Initialize(HWND hWnd)
{
	HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	hr = S_OK;

	//Factory 객체 생성
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

	//IWICFactory 생성
	if (SUCCEEDED(hr))
	{
		hr = CoCreateInstance(
			CLSID_WICImagingFactory,
			NULL,
			CLSCTX_INPROC_SERVER,
			IID_IWICImagingFactory,
			reinterpret_cast<void**>(&pWICFactory)
		);
	}

	//WriteFactory 생성
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&pWriteFactory)
		);
	}

	//폰트 생성 과정
	if (SUCCEEDED(hr))
	{
		///생거진천체
		hr = pWriteFactory->CreateFontFileReference(
			L"Resources/Font/Saenggeo Jincheon.ttf",	//적용할 폰트 파일
			NULL,
			&pFontFile
		);

		hr = pWriteFactory->CreateFontSetBuilder(
			&pFontSetBuilder
		);

		hr = pFontSetBuilder->AddFontFile(pFontFile);
		hr = pFontSetBuilder->CreateFontSet(&pFontSet);

		hr = pWriteFactory->CreateFontCollectionFromFontSet(
			pFontSet,
			&pFontCollection
		);

		hr = pWriteFactory->CreateTextFormat(
			L"Saenggeo Jincheon",					//여기에 폰트 이름을 넣어주면 된다
			pFontCollection,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			20.0f,									//폰트 크기
			L"ko-kr",
			&pTextFormat							//위 정보를 담을 텍스트 포맷		//이걸 여러개 하면 되겠네
		);

		hr = pWriteFactory->CreateTextFormat(
			L"Saenggeo Jincheon",					//여기에 폰트 이름을 넣어주면 된다
			pFontCollection,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			30.0f,									//폰트 크기
			L"ko-kr",
			&pTextFormatLarger						//위 정보를 담을 텍스트 포맷		//이걸 여러개 하면 되겠네
		);

		///안동엄마까투리
		hr = pWriteFactory->CreateFontFileReference(
			L"Resources/Font/Katuri.ttf",
			NULL,
			&pFontFileKaturi
		);

		hr = pWriteFactory->CreateFontSetBuilder(
			&pFontSetBuilderKaturi
		);

		hr = pFontSetBuilderKaturi->AddFontFile(pFontFileKaturi);
		hr = pFontSetBuilderKaturi->CreateFontSet(&pFontSetKaturi);

		hr = pWriteFactory->CreateFontCollectionFromFontSet(
			pFontSetKaturi,
			&pFontCollectionKaturi
		);

		hr = pWriteFactory->CreateTextFormat(
			L"안동엄마까투리",					
			pFontCollectionKaturi,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			20.0f,									
			L"ko-kr",
			&pTextFormatKaturi
		);

		/// 엘리스 디지털배움체
		hr = pWriteFactory->CreateFontFileReference(
			L"Resources/Font/EliceDigitalBaeum_Bold.ttf",
			NULL,
			&pFontFileElice
		);

		hr = pWriteFactory->CreateFontSetBuilder(
			&pFontSetBuilderElice
		);

		hr = pFontSetBuilderElice->AddFontFile(pFontFileElice);
		hr = pFontSetBuilderElice->CreateFontSet(&pFontSetElice);

		hr = pWriteFactory->CreateFontCollectionFromFontSet(
			pFontSetElice,
			&pFontCollectionElice
		);

		hr = pWriteFactory->CreateTextFormat(
			L"엘리스 디지털배움체",
			pFontCollectionElice,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			20.0f,
			L"ko-kr",
			&pTextFormatElice
		);


		hr = pTextFormat->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
		hr = pTextFormat->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
	}		

	GetClientRect(hWnd, &rt);	//RenderTarget은 클라이언트 위에 그려야하니까
	//RenderTarget 생성			//소프트웨어 또는 하드웨어에 렌더링 여부 - 밑은 기본 렌더링 대상	 //렌더링 대상의 초기 크기(픽셀) 및 옵션 - 밑은 기본 크기  //렌더링 대상 참조
	pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rt.right, rt.bottom)), &pRenderTarget);

	//스프라이트 초기화
	mSpriteCount = 0;
	mSpriteInfos.clear();
	mSpriteSheets.clear();

	//브러쉬
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &pBlackBrush);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 0.0f, 0.0f), &pRedBrush);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 1.0f), &pBlueBrush);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 1.0f, 0.0f), &pGreenBrush);

}

//Draw 시작 다른 오브젝트들을 그리기 전에 시작해줘야함
void D2DEngine::BeginDraw()
{
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(1.0f, 1.0f, 1.0f));	//흰 화면으로 초기화
}

//Draw 종료 다른 오브젝트들을 그린 후에 마지막에 해줘야함
void D2DEngine::EndDraw()
{
	pRenderTarget->EndDraw();
}

//텍스트를 그리는 함수
//폰트 : 위에 CreateTextFormat 참조, 폰트 크기 : 20
void D2DEngine::DrawText(int posX, int posY, WCHAR* txt)
{
	D2D1_MATRIX_3X2_F normalTransform = D2D1::Matrix3x2F::Translation(0, 0);
	pRenderTarget->SetTransform(normalTransform);

	pRenderTarget->DrawText(txt, lstrlen(txt), pTextFormat,
		D2D1::RectF(posX, posY, posX + 100, posY + 10), pBlackBrush);
}

//글자를 출력하려면 이걸 사용해
void D2DEngine::DrawText(int posX, int posY, const char* txt)
{
	int len = strlen(txt) + 1;
	int bufferSize = MultiByteToWideChar(CP_ACP, 0, txt, len, NULL, 0);

	wchar_t* wt = new wchar_t[bufferSize];
	MultiByteToWideChar(CP_ACP, 0, txt, len, wt, bufferSize);

	D2D1_MATRIX_3X2_F normalTransform = D2D1::Matrix3x2F::Translation(0, 0);
	pRenderTarget->SetTransform(normalTransform);

	pRenderTarget->DrawText(wt, lstrlen(wt), pTextFormat,
		D2D1::RectF(posX, posY, posX + len * 10, posY + 15), pBlackBrush);
	//DrawRect(posX, posY, posX + len * 10, posY + 15);

	delete[] wt;
}

//int를 매개변수로 받아도 WCHAR로 형변환해서 출력하게
void D2DEngine::DrawText(int posX, int posY, int txt)
{
	int len = to_string(txt).size() + 1;

	wchar_t convertedInt[256];
	swprintf_s(convertedInt, L"%d", txt);

	D2D1_MATRIX_3X2_F normalTransform = D2D1::Matrix3x2F::Translation(0, 0);
	pRenderTarget->SetTransform(normalTransform);

	pRenderTarget->DrawText(convertedInt, lstrlen(convertedInt), pTextFormat,
		D2D1::RectF(posX, posY, posX + len * 20, posY + 15), pBlackBrush);
}

//생거진천체 큰 크기
void D2DEngine::DrawTextLarge(int posX, int posY, const char* txt)
{
	int len = strlen(txt) + 1;
	int bufferSize = MultiByteToWideChar(CP_ACP, 0, txt, len, NULL, 0);

	wchar_t* wt = new wchar_t[bufferSize];
	MultiByteToWideChar(CP_ACP, 0, txt, len, wt, bufferSize);

	D2D1_MATRIX_3X2_F normalTransform = D2D1::Matrix3x2F::Translation(0, 0);
	pRenderTarget->SetTransform(normalTransform);

	pRenderTarget->DrawText(wt, lstrlen(wt), pTextFormatLarger,
		D2D1::RectF(posX, posY, posX + len * 15, posY + 15), pBlackBrush);
	//DrawRect(posX, posY, posX + len * 10, posY + 15);

	delete[] wt;
}

//생거진천체 큰 크기 int 형변환
void D2DEngine::DrawTextLarge(int posX, int posY, int txt)
{
	int len = to_string(txt).size() + 1;

	wchar_t convertedInt[256];
	swprintf_s(convertedInt, L"%d", txt);

	D2D1_MATRIX_3X2_F normalTransform = D2D1::Matrix3x2F::Translation(0, 0);
	pRenderTarget->SetTransform(normalTransform);

	pRenderTarget->DrawText(convertedInt, lstrlen(convertedInt), pTextFormatLarger,
		D2D1::RectF(posX, posY, posX + 100, posY + 10), pBlackBrush);
}

void D2DEngine::DrawTextInt(int posX, int posY, int txt)
{
	int len = to_string(txt).size() + 1;

	wchar_t convertedInt[256];
	swprintf_s(convertedInt, L"%d", txt);

	D2D1_MATRIX_3X2_F normalTransform = D2D1::Matrix3x2F::Translation(0, 0);
	pRenderTarget->SetTransform(normalTransform);

	pRenderTarget->DrawText(convertedInt, lstrlen(convertedInt), pTextFormat,
		D2D1::RectF(posX, posY, posX + 100, posY + 10), pBlackBrush);
}

//임시	//정리필요
void D2DEngine::DrawText1(int posX, int posY, const char* txt)
{
	int len = strlen(txt) + 1;
	int bufferSize = MultiByteToWideChar(CP_ACP, 0, txt, len, NULL, 0);

	wchar_t* wt = new wchar_t[bufferSize];
	MultiByteToWideChar(CP_ACP, 0, txt, len, wt, bufferSize);

	D2D1_MATRIX_3X2_F normalTransform = D2D1::Matrix3x2F::Translation(0, 0);
	pRenderTarget->SetTransform(normalTransform);

	pRenderTarget->DrawText(wt, lstrlen(wt), pTextFormat,
		D2D1::RectF(posX, posY, posX + len * 10, posY + 15), pRedBrush);

	delete[] wt;
}

void D2DEngine::DrawText2(int posX, int posY, const char* txt)
{
	int len = strlen(txt) + 1;
	int bufferSize = MultiByteToWideChar(CP_ACP, 0, txt, len, NULL, 0);

	wchar_t* wt = new wchar_t[bufferSize];
	MultiByteToWideChar(CP_ACP, 0, txt, len, wt, bufferSize);

	D2D1_MATRIX_3X2_F normalTransform = D2D1::Matrix3x2F::Translation(0, 0);
	pRenderTarget->SetTransform(normalTransform);

	pRenderTarget->DrawText(wt, lstrlen(wt), pTextFormatKaturi,
		D2D1::RectF(posX, posY, posX + 100, posY + 10), pBlackBrush);

	delete[] wt;
}

void D2DEngine::DrawText3(int posX, int posY, const char* txt)
{
	int len = strlen(txt) + 1;
	int bufferSize = MultiByteToWideChar(CP_ACP, 0, txt, len, NULL, 0);

	wchar_t* wt = new wchar_t[bufferSize];
	MultiByteToWideChar(CP_ACP, 0, txt, len, wt, bufferSize);

	D2D1_MATRIX_3X2_F normalTransform = D2D1::Matrix3x2F::Translation(0, 0);
	pRenderTarget->SetTransform(normalTransform);

	pRenderTarget->DrawText(wt, lstrlen(wt), pTextFormatElice,
		D2D1::RectF(posX, posY, posX + 100, posY + 10), pBlackBrush);

	delete[] wt;
}
//

//테두리만 있는 RECT
void D2DEngine::DrawRect(int srcX, int srcY, int dstX, int dstY)
{
	D2D1_RECT_F rectF1 = D2D1::RectF(srcX, srcY, dstX, dstY);
	D2D1_MATRIX_3X2_F normalTransform = D2D1::Matrix3x2F::Translation(0, 0);

	pRenderTarget->SetTransform(normalTransform);
	pRenderTarget->DrawRectangle(D2D1::RectF(rectF1.left, rectF1.top, rectF1.right, rectF1.bottom), pRedBrush);
}

//선 그리기
//마지막 매개변수가 굵기
void D2DEngine::DrawLine(int srcX, int srcY, int dstX, int dstY, float width)
{
	D2D1_POINT_2F src;
	D2D1_POINT_2F dst;

	src.x = srcX;
	src.y = srcY;
	dst.x = dstX;
	dst.y = dstY;

	D2D1_MATRIX_3X2_F normalTransform = D2D1::Matrix3x2F::Translation(0, 0);
	pRenderTarget->SetTransform(normalTransform);

	pRenderTarget->DrawLine(src, dst, pBlackBrush, width);
}

//테두리만 있는 타원 그리기
void D2DEngine::DrawEllipse(int posX, int posY, int radius)
{
	D2D1_ELLIPSE d2del;
	d2del.point.x = posX;
	d2del.point.y = posY;
	d2del.radiusX = radius;
	d2del.radiusY = radius;
	
	D2D1_MATRIX_3X2_F normalTransform = D2D1::Matrix3x2F::Translation(0, 0);
	pRenderTarget->SetTransform(normalTransform);

	pRenderTarget->DrawEllipse(d2del, pRedBrush, 1.0f);
}

//그림 리소스를 로드해주는 함수	//이름은 LoadBitmap이지만 png처럼 다른 종류도 상관없음
HRESULT D2DEngine::LoadBitmapFromFile(ID2D1RenderTarget* pRenderTarget, IWICImagingFactory* pIWICFactory, PCWSTR uri, UINT destinationWidth, UINT destinationHeight, ID2D1Bitmap** ppBitmap)
{
	HRESULT hr = S_OK;

	IWICBitmapDecoder* pDecoder = NULL;
	IWICBitmapFrameDecode* pSource = NULL;
	IWICStream* pStream = NULL;
	IWICFormatConverter* pConverter = NULL;
	IWICBitmapScaler* pScaler = NULL;

	hr = pIWICFactory->CreateDecoderFromFilename(
		uri,
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr))
	{
		hr = pDecoder->GetFrame(0, &pSource);
	}
	if (SUCCEEDED(hr))
	{
		hr = pIWICFactory->CreateFormatConverter(&pConverter);
	}
	if (SUCCEEDED(hr))
	{
		if (destinationWidth != 0 || destinationHeight != 0)
		{
			UINT originalWidth, originalHeight;
			hr = pSource->GetSize(&originalWidth, &originalHeight);
			if (SUCCEEDED(hr))
			{
				if (destinationWidth == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationHeight) / static_cast<FLOAT>(originalHeight);
					destinationWidth = static_cast<UINT>(scalar * static_cast<FLOAT>(originalWidth));
				}
				else if (destinationHeight == 0)
				{
					FLOAT scalar = static_cast<FLOAT>(destinationWidth) / static_cast<FLOAT>(originalWidth);
					destinationHeight = static_cast<UINT>(scalar * static_cast<FLOAT>(originalHeight));
				}

				hr = pIWICFactory->CreateBitmapScaler(&pScaler);
				if (SUCCEEDED(hr))
				{
					hr = pScaler->Initialize(
						pSource,
						destinationWidth,
						destinationHeight,
						WICBitmapInterpolationModeCubic
					);
				}
				if (SUCCEEDED(hr))
				{
					hr = pConverter->Initialize(
						pScaler,
						GUID_WICPixelFormat32bppPBGRA,
						WICBitmapDitherTypeNone,
						NULL,
						0.f,
						WICBitmapPaletteTypeMedianCut
					);
				}
			}
		}
		else
		{
			hr = pConverter->Initialize(
				pSource,
				GUID_WICPixelFormat32bppPBGRA,
				WICBitmapDitherTypeNone,
				NULL,
				0.f,
				WICBitmapPaletteTypeMedianCut
			);
		}
	}

	if (SUCCEEDED(hr))
	{
		hr = pRenderTarget->CreateBitmapFromWicBitmap(
			pConverter,
			NULL,
			ppBitmap
		);
	}

	SafeRelease(&pDecoder);
	SafeRelease(&pSource);
	SafeRelease(&pConverter);
	SafeRelease(&pStream);
	SafeRelease(&pScaler);
 	return hr;
}

wchar_t* D2DEngine::ConvertCStoWCS(const char* origin)
{
	size_t newsize = strlen(origin) + 1;
	wchar_t* wcstring = new wchar_t[newsize];

	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, origin, _TRUNCATE);

	return wcstring;
}

///노란색 주석 사이가 실질적으로 사용되는 부분
//그림을 그리기 전에 그림파일을 불러주는 부분 //오브젝트라면 오브젝트의 이름을 넣어줌
int D2DEngine::LoadSpriteSheet(const char* filepath, eObjectDefine eOD)
{
	wchar_t* wcstring = this->ConvertCStoWCS(filepath);
	int result = LoadSpriteSheet(wcstring, eOD);

	delete[] wcstring;

	return result;
}

int D2DEngine::LoadSpriteSheet(const wchar_t* filepath, eObjectDefine eOD)
{
	HRESULT hr;
	ID2D1Bitmap* pNewBitmap;

	hr = LoadBitmapFromFile(
		pRenderTarget,
		pWICFactory,
		filepath,
		0,
		0,
		&pNewBitmap
	);

	if (SUCCEEDED(hr))
	{
		mSpriteSheets.insert(pair<int, ID2D1Bitmap*>(static_cast<int>(eOD), pNewBitmap));

		return static_cast<int>(eOD);
	}
	
	return -1;
}

//스프라이트 시트에 오브젝트 이름으로 넣어줌 //LoadSpriteSheet 다음에 해줘야함
DRSprite* D2DEngine::LoadSpriteFromSheet(eObjectDefine eOD, int oriX, int oriY, int width, int height, int delayFrame)
{
	D2DSprite* _newSprite = new D2DSprite(static_cast<int>(eOD), oriX, oriY, mSpriteCount, width, height,
		0, 0, 0, delayFrame, RECT(), RECT(), 1);
	mSpriteInfos.push_back(_newSprite);
	mSpriteCount++;

	return _newSprite;
}

D2DSprite* D2DEngine::LoadSpriteFromSheet2(eObjectDefine eOD, int oriX, int oriY, int width, int height, int delayFrame)
{
	D2DSprite* _newSprite = new D2DSprite(static_cast<int>(eOD), oriX, oriY, mSpriteCount, width, height,
		0, 0, 0, delayFrame, RECT(), RECT(), 1);

	return _newSprite;
}

//실질적으로 그림을 그리는 함수의 시작 부분
void D2DEngine::DrawSprite(eObjectDefine eOD, float dstX, float dstY, float rotateScale)
{
	D2DSprite* _D2DSprite = nullptr;

	for (int i = 0; i < mSpriteInfos.size(); i++)
	{
		if (static_cast<int>(eOD) == (mSpriteInfos[i]->m_SheetIndex))
		{
			_D2DSprite = mSpriteInfos[i];
		}
	}

	if (_D2DSprite != NULL)
	{
		float centerPosX = (float)dstX + (float)_D2DSprite->Width / 2.0f;
		float centerPosY = (float)dstY + (float)_D2DSprite->Height / 2.0f;

		D2D1_MATRIX_3X2_F rotationTransform = D2D1::Matrix3x2F::Rotation(rotateScale, D2D1::Point2F(centerPosX, centerPosY));
		pRenderTarget->SetTransform(rotationTransform);

		ID2D1Bitmap* _sheet = mSpriteSheets[_D2DSprite->m_SheetIndex];
		if (_sheet != NULL)
		{
			pRenderTarget->DrawBitmap(
				_sheet,
				D2D1::RectF((float)dstX, (float)dstY, (float)(dstX + _D2DSprite->Width), (float)(dstY + _D2DSprite->Height)),
				1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				D2D1::RectF(_D2DSprite->m_OriX, _D2DSprite->m_OriY, _D2DSprite->m_OriX + (float)_D2DSprite->Width, _D2DSprite->m_OriY + (float)_D2DSprite->Height)
			);
		}
		
	}

}

//잘라서 그리는 함수 머리아프다
void D2DEngine::DrawSpriteCut(eObjectDefine eOD, float dstX, float dstY, int cutY, float rotateScale)
{
	D2DSprite* _D2DSprite = nullptr;
	for (int i = 0; i < mSpriteInfos.size(); i++)
	{
		if (static_cast<int>(eOD) == (mSpriteInfos[i]->m_SheetIndex))
		{
			_D2DSprite = mSpriteInfos[i];
		}
	}

	if (_D2DSprite != NULL)
	{
		float centerPosX = (float)dstX + (float)_D2DSprite->Width / 2.0f;
		float centerPosY = (float)dstY + (float)_D2DSprite->Height / 2.0f;

		D2D1_MATRIX_3X2_F rotationTransform = D2D1::Matrix3x2F::Rotation(rotateScale, D2D1::Point2F(centerPosX, centerPosY));
		pRenderTarget->SetTransform(rotationTransform);

		ID2D1Bitmap* _sheet = mSpriteSheets[_D2DSprite->m_SheetIndex];
		if (_sheet != NULL)
		{
			pRenderTarget->DrawBitmap(
				_sheet,
				D2D1::RectF((float)dstX, (float)dstY, (float)(dstX + _D2DSprite->Width), (float)(dstY + cutY)),
				1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				D2D1::RectF(_D2DSprite->m_OriX, _D2DSprite->m_OriY, _D2DSprite->m_OriX + (float)_D2DSprite->Width, (float)_D2DSprite->Height)
			);
		}
	}
}

//애니메이션용
void D2DEngine::DrawSprite(int index, int dstX, int dstY, vector<D2DSprite*> aniList, float rotateScale)
{
	D2DSprite* _D2DSprite = nullptr;
	_D2DSprite = aniList[index];

	if (_D2DSprite != NULL)
	{
		float centerPosX = (float)dstX + (float)_D2DSprite->Width / 2.0f;
		float centerPosY = (float)dstY + (float)_D2DSprite->Height / 2.0f;

		D2D1_MATRIX_3X2_F rotationTransform = D2D1::Matrix3x2F::Rotation(rotateScale, D2D1::Point2F(centerPosX, centerPosY));
		pRenderTarget->SetTransform(rotationTransform);

		ID2D1Bitmap* _sheet = mSpriteSheets[_D2DSprite->m_SheetIndex];
		if (_sheet != NULL)
		{
			pRenderTarget->DrawBitmap(
				_sheet,
				D2D1::RectF((float)dstX, (float)dstY, (float)(dstX + _D2DSprite->Width), (float)(dstY + _D2DSprite->Height)),
				1.0f,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				D2D1::RectF(_D2DSprite->m_OriX, _D2DSprite->m_OriY, _D2DSprite->m_OriX + (float)_D2DSprite->Width, _D2DSprite->m_OriY + (float)_D2DSprite->Height)
			);
		}
	}
}

//투명도를 조절할 수 있는 Sprite 함수	//마지막 매개변수가 투명도 //0.0 ~ 1.0 낮을 수록 투명해짐
void D2DEngine::DrawSpriteAlpha(eObjectDefine eOD, float dstX, float dstY, float opacity, float rotateScale)
{
	D2DSprite* _D2DSprite = nullptr;

	for (int i = 0; i < mSpriteInfos.size(); i++)
	{
		if (static_cast<int>(eOD) == (mSpriteInfos[i]->m_SheetIndex))
		{
			_D2DSprite = mSpriteInfos[i];
		}
	}

	if (_D2DSprite != NULL)
	{
		float centerPosX = (float)dstX + (float)_D2DSprite->Width / 2.0f;
		float centerPosY = (float)dstY + (float)_D2DSprite->Height / 2.0f;

		D2D1_MATRIX_3X2_F rotationTransform = D2D1::Matrix3x2F::Rotation(rotateScale, D2D1::Point2F(centerPosX, centerPosY));
		pRenderTarget->SetTransform(rotationTransform);

		ID2D1Bitmap* _sheet = mSpriteSheets[_D2DSprite->m_SheetIndex];
		if (_sheet != NULL)
		{
			pRenderTarget->DrawBitmap(
				_sheet,
				D2D1::RectF((float)dstX, (float)dstY, (float)(dstX + _D2DSprite->Width), (float)(dstY + _D2DSprite->Height)),
				opacity,
				D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				D2D1::RectF(_D2DSprite->m_OriX, _D2DSprite->m_OriY, _D2DSprite->m_OriX + (float)_D2DSprite->Width, _D2DSprite->m_OriY + (float)_D2DSprite->Height)
			);
		}
	}
}

/// 

void D2DEngine::DrawSprite(DRSprite* sprite, int dstX, int dstY)
{
	D2DSprite* _D2DSprite = dynamic_cast<D2DSprite*>(sprite);

	_D2DSprite->KeyColor = RGB(0, 0, 0);

	if (_D2DSprite != NULL)
	{
		ID2D1Bitmap* _sheet = mSpriteSheets[_D2DSprite->m_SheetIndex];
		if (_sheet != NULL)
		{
			D2D1_SIZE_F size = pBitmap->GetSize();

			pRenderTarget->DrawBitmap(_sheet,
				D2D1::RectF((float)dstX, (float)dstY, (float)(dstX + _D2DSprite->Width), (float)(dstY + _D2DSprite->Height)),
				1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR,
				D2D1::RectF((float)_D2DSprite->m_OriX, (float)_D2DSprite->m_OriY, (float)(_D2DSprite->m_OriX + _D2DSprite->Width), (float)(_D2DSprite->m_OriY + _D2DSprite->Height))
			);
		}
	}
}

void D2DEngine::Release()
{
	//프로그램 종료 전 객체 제거
	SafeRelease(&pD2DFactory);
	SafeRelease(&pWICFactory);
	SafeRelease(&pRedBrush);
	SafeRelease(&pBlackBrush);
	SafeRelease(&pBlueBrush);
	SafeRelease(&pGreenBrush);
	SafeRelease(&pRenderTarget);

	CoUninitialize();
}