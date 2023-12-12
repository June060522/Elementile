#pragma once
#include "Object.h"
class StagePanel;
class Texture;
class StageIcon :
    public Object
{
public:
    StageIcon(Vec2 _vPos, Vec2 _vScale, int _iStage, StagePanel* _pStagePanel);
public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;

private:
    int m_iStage;
    StagePanel* m_pStagePanel;

    Texture* m_pLevelBorder;
    Texture* m_pLevelBorderX;
};