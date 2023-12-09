#pragma once
#include "Object.h"
class Texture;
class Image :
    public Object
{
public:
    Image(Texture* _tex, Vec2 _pos, Vec2 _scale);
public:
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
protected:
    Texture* m_pTex;
};

