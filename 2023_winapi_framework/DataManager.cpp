#include "pch.h"
#include "DataManager.h"
#include "ServerManager.h"

void DataManager::Init()
{
    LoadData();
}

void DataManager::SaveData() 
{
    if (m_lastStage > m_highStage)
    {
        ServerManager::GetInst()->Save();
        m_highStage = m_lastStage;
    }
    ServerManager::GetInst()->SetplayerScore(m_highStage);
}

void DataManager::LoadData() 
{
    m_highStage = ServerManager::GetInst()->GetplayerScore();
    m_lastStage = m_highStage;
}