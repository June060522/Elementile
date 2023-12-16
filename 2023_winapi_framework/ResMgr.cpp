#include "pch.h"
#include "ResMgr.h"
#include "PathMgr.h"
#include "Texture.h"
Texture* ResMgr::TexLoad(const wstring& _strKey, const wstring& _strRelativePath)
{
    // �� ã������ �װ� �����ֱ�
    Texture* pTex = TexFind(_strKey);
    if (nullptr != pTex)
        return pTex;

    // ó������ �����Ŵϱ�.. ��� ã�Ƽ�
    wstring strFilepath = PathMgr::GetInst()->GetResPath();
    strFilepath += _strRelativePath;
    // ������డ����..
    pTex = new Texture;
    pTex->Load(strFilepath); // �ؽ�ó ��ü�� �ε�..
    pTex->SetKey(_strKey); // Ű ��� �����صΰ�..
    pTex->SetRelativePath(_strRelativePath);
    m_mapTex.insert({ _strKey,pTex }); // �װŸ� �ʿ��ٰ� ����.
    return pTex;
}

Texture* ResMgr::TexFind(const wstring& _strKey)
{
    // ã�Ƽ� return
    auto iter = m_mapTex.find(_strKey);
    if (iter != m_mapTex.end())
    {
        return iter->second;
    }
    return nullptr;
}

void ResMgr::Release()
{
    // Texture
    map<wstring, Texture*>::iterator iter;
    for (iter = m_mapTex.begin(); iter != m_mapTex.end(); ++iter)
    {
        if (nullptr != iter->second)
            delete iter->second;
    }
    m_mapTex.clear();

    // SOUND
    map<wstring, tSoundInfo*>::iterator itersod;
    for (itersod = m_mapSod.begin(); itersod != m_mapSod.end(); ++itersod)
    {
        if (nullptr != itersod->second)
            delete itersod->second;
    }
    m_mapSod.clear();

    // �� ���� �� �� �ý��� �ݰ� ��ȯ
    m_pSystem->close();
    m_pSystem->release();
}

void ResMgr::Init()
{
    isOff = false;
    FMOD::System_Create(&m_pSystem); // �ý��� ���� �Լ�
    // ä�μ�, ���� ���
    if (m_pSystem != nullptr)
        m_pSystem->init((int)SOUND_CHANNEL::END, FMOD_INIT_NORMAL, nullptr);
}

void ResMgr::Update()
{
    if(isOff)
    {
        Volume(SOUND_CHANNEL::BGM, 0);
        Volume(SOUND_CHANNEL::EFFECT, 0);
    }
    else
    {
        Volume(SOUND_CHANNEL::BGM, 1);
        Volume(SOUND_CHANNEL::EFFECT, 1);
    }
}

void ResMgr::LoadSound(const wstring& _strKey, const wstring& _strReleativePath, bool _IsLoop)
{
    if (FindSound(_strKey))
        return;
    wstring strFilePath = PathMgr::GetInst()->GetResPath();
    strFilePath += _strReleativePath;

    // wstring to string
    std::string str;
    str.assign(strFilePath.begin(), strFilePath.end());

    // �������� ���� ����
    FMOD_MODE eMode = FMOD_LOOP_NORMAL; // �ݺ� ���
    if (!_IsLoop)
        eMode = FMOD_DEFAULT; // ���� 1���� ���

    tSoundInfo* ptSound = new tSoundInfo;
    ptSound->IsLoop = _IsLoop;
    // ���� ��ü�� ����� ���� system��.
                            //���ϰ��,  FMOD_MODE, NULL, &sound
    m_pSystem->createSound(str.c_str(), eMode, nullptr, &ptSound->pSound);
    m_mapSod.insert({ _strKey, ptSound });
}

void ResMgr::Play(const wstring& _strKey)
{
    tSoundInfo* ptSound = FindSound(_strKey);
    if (!ptSound)
        return;
    m_pSystem->update(); // play�Ҷ� update�� �ֱ������� ȣ���ؾ� ���尡 �������� ����.
    SOUND_CHANNEL eChannel = SOUND_CHANNEL::BGM;
    if (!ptSound->IsLoop)
        eChannel = SOUND_CHANNEL::EFFECT;
    // ���� ��� �Լ�. &channel�� � ä���� ���� ����Ǵ��� ������ �ѱ�
    m_pSystem->playSound(ptSound->pSound, nullptr, false, &m_pChannel[(UINT)eChannel]);

}

void ResMgr::Stop(SOUND_CHANNEL _eChannel)
{
    m_pChannel[(UINT)_eChannel]->stop();
}

void ResMgr::Volume(SOUND_CHANNEL _eChannel, float _fVol)
{
    // 0.0 ~ 1.0 ���� ����
    m_pChannel[(UINT)_eChannel]->setVolume(_fVol);
}

void ResMgr::Pause(SOUND_CHANNEL _eChannel, bool _Ispause)
{
    // bool���� true�� �Ͻ�����. ��, �� �Լ��� ������ Createsound�Ҷ� 
    // FMOD_MODE�� FMOD_LOOP_NORMAL �̾�� ��.
    m_pChannel[(UINT)_eChannel]->setPaused(_Ispause);
}

tSoundInfo* ResMgr::FindSound(const wstring& _strKey)
{
    map<wstring, tSoundInfo*>::iterator iter = m_mapSod.find(_strKey);

    if (iter == m_mapSod.end())
        return nullptr;
    return iter->second;
}
