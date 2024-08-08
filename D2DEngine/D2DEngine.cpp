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

	//Factory ��ü ����
	hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pD2DFactory);

	//IWICFactory ����
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

	//WriteFactory ����
	if (SUCCEEDED(hr))
	{
		hr = DWriteCreateFactory(
			DWRITE_FACTORY_TYPE_SHARED,
			__uuidof(IDWriteFactory),
			reinterpret_cast<IUnknown**>(&pWriteFactory)
		);
	}

	//��Ʈ ���� ����
	if (SUCCEEDED(hr))
	{
		///������õü
		hr = pWriteFactory->CreateFontFileReference(
			L"Resources/Font/Saenggeo Jincheon.ttf",	//������ ��Ʈ ����
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
			L"Saenggeo Jincheon",					//���⿡ ��Ʈ �̸��� �־��ָ� �ȴ�
			pFontCollection,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			20.0f,									//��Ʈ ũ��
			L"ko-kr",
			&pTextFormat							//�� ������ ���� �ؽ�Ʈ ����		//�̰� ������ �ϸ� �ǰڳ�
		);

		hr = pWriteFactory->CreateTextFormat(
			L"Saenggeo Jincheon",					//���⿡ ��Ʈ �̸��� �־��ָ� �ȴ�
			pFontCollection,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			30.0f,									//��Ʈ ũ��
			L"ko-kr",
			&pTextFormatLarger						//�� ������ ���� �ؽ�Ʈ ����		//�̰� ������ �ϸ� �ǰڳ�
		);

		///�ȵ�����������
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
			L"�ȵ�����������",					
			pFontCollectionKaturi,
			DWRITE_FONT_WEIGHT_NORMAL,
			DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL,
			20.0f,									
			L"ko-kr",
			&pTextFormatKaturi
		);

		/// ������ �����й��ü
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
			L"������ �����й��ü",
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

	GetClientRect(hWnd, &rt);	//RenderTarget�� Ŭ���̾�Ʈ ���� �׷����ϴϱ�
	//RenderTarget ����			//����Ʈ���� �Ǵ� �ϵ��� ������ ���� - ���� �⺻ ������ ���	 //������ ����� �ʱ� ũ��(�ȼ�) �� �ɼ� - ���� �⺻ ũ��  //������ ��� ����
	pD2DFactory->CreateHwndRenderTarget(D2D1::RenderTargetProperties(), D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rt.right, rt.bottom)), &pRenderTarget);

	//��������Ʈ �ʱ�ȭ
	mSpriteCount = 0;
	mSpriteInfos.clear();
	mSpriteSheets.clear();

	//�귯��
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 0.0f), &pBlackBrush);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1.0f, 0.0f, 0.0f), &pRedBrush);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 0.0f, 1.0f), &pBlueBrush);
	pRenderTarget->CreateSolidColorBrush(D2D1::ColorF(0.0f, 1.0f, 0.0f), &pGreenBrush);

}

//Draw ���� �ٸ� ������Ʈ���� �׸��� ���� �����������
void D2DEngine::BeginDraw()
{
	pRenderTarget->BeginDraw();
	pRenderTarget->Clear(D2D1::ColorF(1.0f, 1.0f, 1.0f));	//�� ȭ������ �ʱ�ȭ
}

//Draw ���� �ٸ� ������Ʈ���� �׸� �Ŀ� �������� �������
void D2DEngine::EndDraw()
{
	pRenderTarget->EndDraw();
}

//�ؽ�Ʈ�� �׸��� �Լ�
//��Ʈ : ���� CreateTextFormat ����, ��Ʈ ũ�� : 20
void D2DEngine::DrawText(int posX, int posY, WCHAR* txt)
{
	D2D1_MATRIX_3X2_F normalTransform = D2D1::Matrix3x2F::Translation(0, 0);
	pRenderTarget->SetTransform(normalTransform);

	pRenderTarget->DrawText(txt, lstrlen(txt), pTextFormat,
		D2D1::RectF(posX, posY, posX + 100, posY + 10), pBlackBrush);
}

//���ڸ� ����Ϸ��� �̰� �����
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

//int�� �Ű������� �޾Ƶ� WCHAR�� ����ȯ�ؼ� ����ϰ�
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

//������õü ū ũ��
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

//������õü ū ũ�� int ����ȯ
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

//�ӽ�	//�����ʿ�
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

//�׵θ��� �ִ� RECT
void D2DEngine::DrawRect(int srcX, int srcY, int dstX, int dstY)
{
	D2D1_RECT_F rectF1 = D2D1::RectF(srcX, srcY, dstX, dstY);
	D2D1_MATRIX_3X2_F normalTransform = D2D1::Matrix3x2F::Translation(0, 0);

	pRenderTarget->SetTransform(normalTransform);
	pRenderTarget->DrawRectangle(D2D1::RectF(rectF1.left, rectF1.top, rectF1.right, rectF1.bottom), pRedBrush);
}

//�� �׸���
//������ �Ű������� ����
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

//�׵θ��� �ִ� Ÿ�� �׸���
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

//�׸� ���ҽ��� �ε����ִ� �Լ�	//�̸��� LoadBitmap������ pngó�� �ٸ� ������ �������
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

///����� �ּ� ���̰� ���������� ���Ǵ� �κ�
//�׸��� �׸��� ���� �׸������� �ҷ��ִ� �κ� //������Ʈ��� ������Ʈ�� �̸��� �־���
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

//��������Ʈ ��Ʈ�� ������Ʈ �̸����� �־��� //LoadSpriteSheet ������ �������
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

//���������� �׸��� �׸��� �Լ��� ���� �κ�
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

//�߶� �׸��� �Լ� �Ӹ�������
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

//�ִϸ��̼ǿ�
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

//������ ������ �� �ִ� Sprite �Լ�	//������ �Ű������� ���� //0.0 ~ 1.0 ���� ���� ��������
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
	//���α׷� ���� �� ��ü ����
	SafeRelease(&pD2DFactory);
	SafeRelease(&pWICFactory);
	SafeRelease(&pRedBrush);
	SafeRelease(&pBlackBrush);
	SafeRelease(&pBlueBrush);
	SafeRelease(&pGreenBrush);
	SafeRelease(&pRenderTarget);

	CoUninitialize();
}