#include "pch.h"
#include "Image.h"
#include "Texture.h"

Image::Image(Texture* _tex, Vec2 _pos, Vec2 _scale)
	:m_pTex(_tex)
{
	SetScale(_scale);
	SetPos(_pos);
}

void Image::Update()
{
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
