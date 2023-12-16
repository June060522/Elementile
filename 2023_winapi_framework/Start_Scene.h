#pragma once
#include "Scene.h"
#include "KeyMgr.h"
class Texture;
class Start_Scene :
    public Scene
{
public:
    virtual void Init() override;
    virtual void Update() override;
    virtual void Render(HDC _dc) override;
    virtual void Release() override;
private:
    void StartScreenDoFade();
    void TitleMoveDotween();
    void ObjectRender(HDC _dc);
    void IconRender(HDC _dc);
    void UserLoginRender(HDC _dc);
private:
    Vec2 pos = Vec2(500, 350);
    vector<Object*> m_vObj;
    POINT mousePos;
    float deltaTime;
    const KEY_STATE& leftMouseButtonState = KeyMgr::GetInst()->GetKey(KEY_TYPE::LBUTTON);
    wstring m_Stage;

    Texture* m_pSoundOn;
    Texture* m_pSoundOff;
    Texture* m_pDoorOpen;
    Texture* m_pDoorClose;

    bool isIDSelect = true;

    Texture* m_pHelp;
};