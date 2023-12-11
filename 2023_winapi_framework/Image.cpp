#include "pch.h"
#include "Image.h"
#include "Texture.h"
#include "KeyMgr.h"
#include "Debug.h"

Image::Image(Texture* _tex, Vec2 _pos, Vec2 _scale, Vec2 _vmenupos)
	:m_pTex(_tex)
{
	SetScale(_scale);
	SetPos(_pos);
}

void Image::Update()
{
	if (KeyMgr::GetInst()->GetKey(KEY_TYPE::LBUTTON) == KEY_STATE::DOWN)
	{
		POINT mousePos;
		Vec2 leftTop;
		Vec2 rightBottom;
		mousePos = KeyMgr::GetInst()->GetMousePos();
		leftTop = { GetPos().x - 35,GetPos().y - 35 };
		rightBottom = { GetPos().x + 35,GetPos().y + 35 };
		if (mousePos.x >= leftTop.x && mousePos.x <= rightBottom.x &&
			mousePos.y >= leftTop.y && mousePos.y <= rightBottom.y)
		{
			Function();
		}
	}
}

void Image::Render(HDC _dc)
{
	float width = m_pTex->GetWidth();
	float height = m_pTex->GetHeight();
	float left = GetPos().x - (width * (GetScale().x / 200.f));
	float top = GetPos().y - (height * (GetScale().y / 200.f));
	TransparentBlt(_dc, left, top,
		width * (GetScale().x / 100.f), height * (GetScale().y / 100.f),
		m_pTex->GetDC(), 0, 0,
		width, height, RGB(255, 0, 255));
}

void Image::Function()
{
}
