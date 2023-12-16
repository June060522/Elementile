#pragma once
#include "fmod.hpp"
#pragma comment(lib, "fmod_vc")
enum class SOUND_CHANNEL
{
	BGM, EFFECT, END
};
struct tSoundInfo
{
	FMOD::Sound* pSound; // ���� ���� �޸�
	bool IsLoop;
};
class Texture;
class ResMgr
{
	SINGLE(ResMgr);
public:
	Texture* TexLoad(const wstring& _strKey,
		const wstring& _strRelativePath);
	Texture* TexFind(const wstring& _strKey);
	void Release();
private:
	map<wstring, Texture*> m_mapTex;
	FMOD::System* m_pSystem; // ���� �ý���
	map<wstring, tSoundInfo*> m_mapSod;
	FMOD::Channel* m_pChannel[(UINT)SOUND_CHANNEL::END]; // ����� ä��
public:
	void Init();
	void Update();
	void LoadSound(const wstring& _strKey, const wstring& _strReleativePath, bool _IsLoop);
	void Play(const wstring& _strKey);
	void Stop(SOUND_CHANNEL _eChannel);
	void Volume(SOUND_CHANNEL _eChannel, float _fVol);
	void Pause(SOUND_CHANNEL _eChannel, bool _Ispause);
public:
	const bool& GetSoundVol() { return isOff; }
	void SetSoundVol(bool _val) { isOff = _val; }
private:
	tSoundInfo* FindSound(const wstring& _strKey);
	bool isOff;
};

