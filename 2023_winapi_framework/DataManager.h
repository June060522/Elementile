#pragma once
class DataManager
{
	SINGLE(DataManager);
public:
	void Init();
public:
	void SaveData();
	void LoadData();
public:
	const void SetLastStage(int _val) { m_lastStage = _val; }
	const void SetHighStage(int _val) { m_highStage = _val; }
	const short& GetLastStage() const { return m_lastStage; }
	const short& GetHighStage() const { return m_highStage; }
private:
	short m_lastStage;
	short m_highStage;
};