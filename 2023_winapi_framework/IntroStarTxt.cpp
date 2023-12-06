#include "pch.h"
#include "IntroStarTxt.h"
#include "TimeMgr.h"

IntroStarTxt::IntroStarTxt(int _iFontSize, Vec2 _vPos, wstring _wstr, int _iSetSize
    , float _fMaxTime, float _fWaitTime)
    :UIText(_vPos, _wstr)
    , m_iFontSize(_iFontSize)
    , m_iSetSize(_iSetSize)
    , m_fMaxTime(_fMaxTime)
    , m_fWaitTime(_fWaitTime)
    , m_fCurTime(0.f)
{
    m_ioriginval = m_iFontSize;
}

void IntroStarTxt::Update()
{
    m_fCurTime += TimeMgr::GetInst()->GetDT();
    if (m_fCurTime > m_fWaitTime)
    {
        m_iFontSize = m_ioriginval + (m_iSetSize - m_ioriginval) * ((m_fCurTime - m_fWaitTime) / m_fMaxTime);
    }
}

void IntroStarTxt::Render(HDC _dc)
{
    HFONT hFont = CreateFont(m_iFontSize, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
        CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH | FF_DONTCARE, L"인천교육소통");
    SelectObject(_dc, hFont);

    SetTextColor(_dc, RGB(255, 255, 0));

    TextOut(_dc, GetPos().x, GetPos().y, m_wstr.c_str(), wcslen(m_wstr.c_str()));

    DeleteObject(hFont);
}
