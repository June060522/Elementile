#pragma once
class Scene;
class Debug
{
public:
	Debug();
	Debug(const wstring& _text);
	Debug(const wstring& _text, const int& _posX, const int& _posY);
};