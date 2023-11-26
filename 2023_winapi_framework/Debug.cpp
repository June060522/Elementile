#include "pch.h"
#include "Debug.h"
#include "Scene.h"
#include "Core.h"

//����׿��̶� ������۸�X

Debug::Debug()
{
	wstring str = L"�� �ڵ������ ������";
	TextOut(Core::GetInst()->GetMainDC(),
		100, Core::GetInst()->GetResolution().y - 100,
		str.c_str(), str.length());
}

Debug::Debug(const wstring& _text)
{
	TextOut(Core::GetInst()->GetMainDC(), 
		100, Core::GetInst()->GetResolution().y - 100,
		_text.c_str(), _text.length());
}

Debug::Debug(const wstring& _text, const int& _posX, const int& _posY)
{
	TextOut(Core::GetInst()->GetMainDC(),
		_posX, _posY,
		_text.c_str(), _text.length());
}
