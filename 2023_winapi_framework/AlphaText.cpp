#include "pch.h"
#include "AlphaText.h"

AlphaText::AlphaText(Vec2 _vPos, wstring _wstr) : UIText(_vPos, _wstr) {

}

void AlphaText::SetAlpha(float alpha) {
    m_alpha = alpha;
}
