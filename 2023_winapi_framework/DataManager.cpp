#include "pch.h"
#include "DataManager.h"

void DataManager::Init()
{
    LoadData();
}

void DataManager::SaveData() {
    ofstream outputFile("Data\\Data.txt");
    bool isOpen = outputFile.is_open();
    if (isOpen) {
        if (m_lastStage > m_highStage)
            m_highStage = m_lastStage;
        outputFile << m_lastStage << endl;
        outputFile << m_highStage << endl;

        // 파일 닫기
        outputFile.close();
    }
}

void DataManager::LoadData() {

    // 파일을 읽기 모드로 열기
    ifstream inputFile("Data\\Data.txt");
    bool isOpen = inputFile.is_open();
    if (isOpen) 
    {
        inputFile >> m_lastStage >> m_highStage;
        inputFile.close();
    }
    else 
    {
        assert(isOpen);
    }
}