#include "pch.h"
#include "ServerManager.h"
#include "Debug.h"
#include "DataManager.h"
#include "GameSceneUI.h"

struct Player
{
	string id;
	string password;
	int score;
	string command;
};

bool ServerManager::Load() {
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		return false;
	}

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET) {
		WSACleanup();
		return false;
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr("172.30.1.30");  // 서버의 IP 주소 (로컬 호스트)
	serverAddr.sin_port = htons(8000);  // 서버의 포트 번호

	if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
		closesocket(clientSocket);
		WSACleanup();
		return false;
	}

	Player* p = new Player();
	p->id = playerId;
	p->password = playerPassword;
	p->score = 0;
	p->command = "Load";

	// 실제 데이터를 전송
	{
		std::lock_guard<std::mutex> lock(sendMutex);  // send에 뮤텍스 적용
		send(clientSocket, reinterpret_cast<char*>(p), sizeof(Player), 0);
	}

	// 비동기로 서버에서 로그인 응답을 기다림
	Player* receivedPlayer = new Player();
	{
		std::lock_guard<std::mutex> lock(recvMutex);  // recv에 뮤텍스 적용
		recv(clientSocket, reinterpret_cast<char*>(receivedPlayer), sizeof(Player), 0);
	}
	// 받아온 데이터를 처리
	playerScore = receivedPlayer->score;
	isLogin = true;
	DataManager::GetInst()->Init();
	return true;
}

void ServerManager::Save()
{
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
		closesocket(clientSocket);
		WSACleanup();
	}

	Player* p = new Player();
	p->id = playerId;
	p->password = playerPassword;
	p->score = playerScore;
	p->command = "Save";

	// 실제 데이터를 전송
	{
		std::lock_guard<std::mutex> lock(sendMutex);  // send에 뮤텍스 적용
		send(clientSocket, reinterpret_cast<char*>(p), sizeof(Player), 0);
	}
}


void ServerManager::GetRanking(GameSceneUI* _pGameSceneUI) {

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(clientSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
		closesocket(clientSocket);
		WSACleanup();
	}

	Player* p = new Player();
	p->id = playerId;
	p->password = playerPassword;
	p->score = playerScore;
	p->command = "Rank";

	// 실제 데이터를 전송
	{
		std::lock_guard<std::mutex> lock(sendMutex);  // send에 뮤텍스 적용
		send(clientSocket, reinterpret_cast<char*>(p), sizeof(Player), 0);
	}

	for (int i = 0; i < 3; ++i) {
		Player* receivedPlayer = new Player();
		{
			std::lock_guard<std::mutex> lock(recvMutex);  // recv에 뮤텍스 적용
			recv(clientSocket, reinterpret_cast<char*>(receivedPlayer), sizeof(Player), 0);
		}
		_pGameSceneUI->SetIdAndRank(receivedPlayer->id, receivedPlayer->score, i);
	}
}

void ServerManager::Release() {
	closesocket(clientSocket);
	WSACleanup();
}