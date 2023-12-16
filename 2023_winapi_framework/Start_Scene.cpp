#include "pch.h"
#include "Start_Scene.h"
#include "Scene.h"
#include "SceneMgr.h"
#include "Dotween.h"
#include "Core.h"
#include "KeyMgr.h"
#include "DataManager.h"
#include "ResMgr.h"
#include "TimeMgr.h"
#include "UIText.h"
#include "ResMgr.h"
#include "Texture.h"
#include "ServerManager.h"

int StartdarknessLevel = 255;
float StartelapsedTime = -5.0f;
const float StartdarknessActivationTime = 5.0f;

float t = 2.5f;
        
void Start_Scene::Init()
{
	for (int i = (int)OBJECT_GROUP::END - 1; i >= 0; --i)
	{
		SceneMgr::GetInst()->GetCurScene()->GetGroupObject((OBJECT_GROUP)i).clear();
	}
	m_vObj.clear();

	m_vObj.push_back(new UIText(Vec2(475.f, 100.f), L"������Ÿ��"));
	int result = AddFontResource(L"Res\\Font\\��õ��������.ttf");

	for (size_t i = 0; i < m_vObj.size(); ++i)
		AddObject(m_vObj[i], OBJECT_GROUP::UI);

	/*m_Stage = L"Stage ";
	m_Stage += to_wstring(DataManager::GetInst()->GetLastStage());*/

	m_pSoundOn = ResMgr::GetInst()->TexLoad(L"Sound", L"Texture\\sound.bmp");
	m_pSoundOff = ResMgr::GetInst()->TexLoad(L"SoundOff", L"Texture\\soundoff.bmp");
	m_pDoorOpen = ResMgr::GetInst()->TexLoad(L"Door Open", L"Texture\\dooropen.bmp");
	m_pDoorClose = ResMgr::GetInst()->TexLoad(L"Door Close", L"Texture\\doorclose.bmp");
}

void Start_Scene::Update()
{
	StartScreenDoFade();
	Scene::Update();
	t += TimeMgr::GetInst()->GetDT();
	TitleMoveDotween();
	mousePos = KeyMgr::GetInst()->GetMousePos();

	if (leftMouseButtonState == KEY_STATE::DOWN)
	{
		if (mousePos.x >= 25 && mousePos.x <= 125
			&& mousePos.y >= 25 && mousePos.y <= 125)
		{
			ResMgr::GetInst()->SetSoundVol(!ResMgr::GetInst()->GetSoundVol());
		}
		else if (mousePos.x >= 1445 && mousePos.x <= 1505 &&
			mousePos.y >= 30 && mousePos.y <= 125)
		{
			ExitProcess(0);
		}
		else if(m_Stage != L"")
			SceneMgr::GetInst()->LoadScene(L"GameScene");

		if (mousePos.x >= 625 && mousePos.x <= 925 &&
			mousePos.y >= 500 && mousePos.y <= 550)
		{
			isIDSelect = true;
		}
		else if (mousePos.x >= 625 && mousePos.x <= 925 &&
			mousePos.y >= 600 && mousePos.y <= 650)
		{
			isIDSelect = false;
		}
		else if (mousePos.x >= 625 && mousePos.x <= 925 &&
			mousePos.y >= 700 && mousePos.y <= 750 && !ServerManager::GetInst()->GetplayerLogin())
		{
			ServerManager::GetInst()->Load();
			m_Stage += L"Stage ";
			m_Stage += to_wstring(DataManager::GetInst()->GetHighStage());
		}
	}
	if (!ServerManager::GetInst()->GetplayerLogin())
	{
		if (isIDSelect)
		{
			string s;
			s += ServerManager::GetInst()->GetplayerID();
			for (int i = (int)KEY_TYPE::Q; i <= (int)KEY_TYPE::M; i++)
			{
				//if (KeyMgr::GetInst()->GetKey((KEY_TYPE)i)) == KEY_STATE::DOWN)
				//s += (KEY_TYPE)i;
				if (KeyMgr::GetInst()->GetKey((KEY_TYPE)i) == KEY_STATE::DOWN && s.size() < 16)
					s += (char)KeyMgr::GetInst()->m_arrVKKey[i];
			}
			if (KeyMgr::GetInst()->GetKey(KEY_TYPE::BACK) == KEY_STATE::DOWN && s.size() > 0)
				s.erase(s.size() - 1);
			ServerManager::GetInst()->SetplayerID(s);
		}
		else
		{
			string s;
			s += ServerManager::GetInst()->GetplayerPassword();
			for (int i = (int)KEY_TYPE::Q; i <= (int)KEY_TYPE::M; i++)
			{
				//if (KeyMgr::GetInst()->GetKey((KEY_TYPE)i)) == KEY_STATE::DOWN)
				//s += (KEY_TYPE)i;
				if (KeyMgr::GetInst()->GetKey((KEY_TYPE)i) == KEY_STATE::DOWN && s.size() < 16)
					s += (char)KeyMgr::GetInst()->m_arrVKKey[i];
			}
			if (KeyMgr::GetInst()->GetKey(KEY_TYPE::BACK) == KEY_STATE::DOWN && s.size() > 0)
				s.erase(s.size() - 1);
			ServerManager::GetInst()->SetplayerPassword(s);
		}

	}
	ResMgr::GetInst()->Update();
}

void Start_Scene::Render(HDC _dc)
{
	ObjectRender(_dc);
	IconRender(_dc);
	HFONT hFont = CreateFont(50, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"��õ��������");
	SelectObject(_dc, hFont);
	TextOut(_dc, 700, 500, m_Stage.c_str(), m_Stage.size());
	if(!ServerManager::GetInst()->GetplayerLogin())
		UserLoginRender(_dc);
	DeleteObject(hFont);
}

void Start_Scene::Release()
{
	Scene::Release();

	RemoveFontResource(L"Res\\Font\\��õ��������.ttf");
}

void Start_Scene::StartScreenDoFade()
{
	deltaTime += TimeMgr::GetInst()->GetDT();
	StartelapsedTime += deltaTime;

	if (StartelapsedTime <= 300.0f && StartdarknessLevel < 300)
	{
		StartdarknessLevel -= 1;
		if (deltaTime >= 5)
		{
			deltaTime = 0.f;
		}
	}
}

void Start_Scene::TitleMoveDotween()
{
	if (t >= 2.5f)
	{
		int x;
		for (size_t i = 0; i < m_vObj.size(); ++i)
		{
			SceneMgr::GetInst()->GetCurScene()->
				AddObject(new Dotween(m_vObj[i], Vec2(125 * (i + 1) / 2 + 400, 100), 1.f, DOTWEEN_TYPE::MOVE
				), OBJECT_GROUP::DOTWEEN);
			SceneMgr::GetInst()->GetCurScene()->
				AddObject(new Dotween(m_vObj[i], Vec2(125 * (i + 1) / 2 + 400, 120), 1.2f, 1, DOTWEEN_TYPE::MOVE
				), OBJECT_GROUP::DOTWEEN);
		}
		t = 0;
	}
}

void Start_Scene::ObjectRender(HDC _dc)
{
	RECT rcClient;
	GetClientRect(Core::GetInst()->GetHwnd(), &rcClient);

	// ��Ʈ ���� �� ���� ����
	HFONT hFont = CreateFont(200, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
		CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"��õ��������");
	SelectObject(_dc, hFont);

	StartdarknessLevel = max(StartdarknessLevel, 0);
	COLORREF bgColor = RGB(255 - StartdarknessLevel, 255 - StartdarknessLevel, 255 - StartdarknessLevel);
	HBRUSH hBrush = CreateSolidBrush(bgColor);
	FillRect(_dc, &rcClient, hBrush);
	DeleteObject(hBrush);

	SetTextColor(_dc, RGB(0, 0, 0));
	SetBkMode(_dc, TRANSPARENT);
	Scene::Render(_dc);
	DeleteObject(hFont);
}

void Start_Scene::IconRender(HDC _dc)
{
	if (!ResMgr::GetInst()->GetSoundVol())
	{
		float width = m_pSoundOn->GetWidth();
		float height = m_pSoundOn->GetHeight();
		Vec2 pos = { 75,75 };
		Vec2 scale = { 20,20 };
		float left = pos.x - (width * (scale.x / 200.f));
		float top = pos.y - (height * (scale.y / 200.f));
		TransparentBlt(_dc, left, top,
			width * (scale.x / 100.f), height * (scale.y / 100.f),
			m_pSoundOn->GetDC(), 0, 0,
			width, height, RGB(255, 0, 255));
	}
	else
	{
		float width = m_pSoundOff->GetWidth();
		float height = m_pSoundOff->GetHeight();
		Vec2 pos = { 75,75 };
		Vec2 scale = { 20,20 };
		float left = pos.x - (width * (scale.x / 200.f));
		float top = pos.y - (height * (scale.y / 200.f));
		TransparentBlt(_dc, left, top,
			width * (scale.x / 100.f), height * (scale.y / 100.f),
			m_pSoundOff->GetDC(), 0, 0,
			width, height, RGB(255, 0, 255));
	}
	POINT mousePos = KeyMgr::GetInst()->GetMousePos();
	if (mousePos.x >= 1445 && mousePos.x <= 1505 &&
		mousePos.y >= 30 && mousePos.y <= 125)
	{
		float width = m_pDoorOpen->GetWidth();
		float height = m_pDoorOpen->GetHeight();
		Vec2 pos = { 1475,75 };
		Vec2 scale = { 20,20 };
		float left = pos.x - (width * (scale.x / 200.f));
		float top = pos.y - (height * (scale.y / 200.f));
		TransparentBlt(_dc, left, top,
			width * (scale.x / 100.f), height * (scale.y / 100.f),
			m_pDoorOpen->GetDC(), 0, 0,
			width, height, RGB(255, 0, 255));
	}
	else
	{
		float width = m_pDoorClose->GetWidth();
		float height = m_pDoorClose->GetHeight();
		Vec2 pos = { 1475,75 };
		Vec2 scale = { 20,20 };
		float left = pos.x - (width * (scale.x / 200.f));
		float top = pos.y - (height * (scale.y / 200.f));
		TransparentBlt(_dc, left, top,
			width * (scale.x / 100.f), height * (scale.y / 100.f),
			m_pDoorClose->GetDC(), 0, 0,
			width, height, RGB(255, 0, 255));
	}
}

void Start_Scene::UserLoginRender(HDC _dc)
{
	if (StartdarknessLevel < 150)
	{
		// ���� ���� ���� ������� ������ �����մϴ�.
		int alpha = 255 - StartdarknessLevel;
		alpha = max(0, alpha);  // ���� ���� ������ ���� �ʵ��� �����մϴ�.

		// �ð��� ���� õõ�� ���ϴ� ���� ���� ����Ͽ� �ؽ�Ʈ ������ �����մϴ�.
		COLORREF textColor = RGB(255, 255, 255);
		textColor = RGB(GetRValue(textColor), GetGValue(textColor), GetBValue(textColor)) | (alpha << 17);

		HFONT hFont = CreateFont(25, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
			CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"��õ��������");
		SelectObject(_dc, hFont);

		// �ؽ�Ʈ ������ �����մϴ�.
		SetTextColor(_dc, textColor);

		// �ؽ�Ʈ�� õõ�� ��Ÿ������ ���̵��մϴ�.
		float fadeSpeed = 0.5f;  // ���̵� �ӵ��� �����մϴ�.

		// Ư�� ������ ���� darknessLevel�� ������ŵ�ϴ�.
		if (StartdarknessLevel < 230) {
			StartdarknessLevel += static_cast<int>(fadeSpeed);  // ���̵� �ӵ���ŭ darknessLevel�� ���ҽ�ŵ�ϴ�.
		}

		Rectangle(_dc, 625, 500, 925, 550);
		if (ServerManager::GetInst()->GetplayerID() == "")
			TextOut(_dc, 635, 510, L"���̵� �Է��� �ּ���.", 13);
		else
		{
			string s = ServerManager::GetInst()->GetplayerID();
			wstring ws = L"";
			ws.assign(s.begin(), s.end());
			TextOut(_dc, 635, 510, ws.c_str(), ws.length());
		}

		Rectangle(_dc, 625, 600, 925, 650);
		if (ServerManager::GetInst()->GetplayerPassword() == "")
			TextOut(_dc, 635, 610, L"��й�ȣ�� �Է��� �ּ���.", 14);
		else
		{
			string s = ServerManager::GetInst()->GetplayerPassword();
			wstring ws = L"";
			ws.assign(s.begin(), s.end());
			TextOut(_dc, 635, 610, ws.c_str(), ws.length());
		}

		Rectangle(_dc, 625, 700, 925, 750);
		TextOut(_dc, 750, 710, L"�α���", 3);

		DeleteObject(hFont);
	}
}





