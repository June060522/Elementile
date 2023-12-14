#pragma once
class DBManager
{
	SINGLE(DBManager)
public:
	bool Init();
	void Update();
	void Release();
private:
	WSADATA wsaData;
	SOCKET clientSocket;
	sockaddr_in serverAddr;

	int playerId;
	int playerScore;
};