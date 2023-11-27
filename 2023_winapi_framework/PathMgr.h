#pragma once
class PathMgr
{
	SINGLE(PathMgr);
public:
	void Init();
public:
	const wchar_t* GetResPath() const 
	{ return m_strResPath; }
private:
	wchar_t m_strResPath[255];
};

