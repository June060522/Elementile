#include "pch.h"
#include "Debug.h"
#include "Scene.h"
#include "Core.h"
Debug::Debug(const HDC& _dc, const Scene*& _curScene, const wstring& _text)
{
	TextOut(_dc, 0, Core::GetInst()->GetResolution().y - 100,_text.c_str(), _text.length());
}
