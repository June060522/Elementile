#include "pch.h"
#include "ReIcon.h"
#include "SceneMgr.h"

ReIcon::ReIcon(Texture* _tex, Vec2 _pos, Vec2 _scale)
	:Image(_tex, _pos, _scale)
{
}

void ReIcon::Function()
{
	SceneMgr::GetInst()->LoadScene(L"GameScene");
}
