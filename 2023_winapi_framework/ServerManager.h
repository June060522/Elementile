#pragma once
class ServerManager
{
	SINGLE(ServerManager)
public:
	bool Load();
	void Send();
	void Release();
public:
	wstring GetplayerID() { return playerId; }
	wstring GetplayerPassword() { return playerPassword; }
	int GetplayerScore() { return playerScore; }
	bool GetplayerLogin() { return isLogin; }

	void SetplayerID(wstring val) { playerId = val; }
	void SetplayerPassword(wstring val) { playerPassword = val; }
	void SetplayerScore(int val) { playerScore = val; }
	void SetLogin(bool val) { isLogin = val; }
private:
	WSADATA wsaData;
	SOCKET clientSocket;
	sockaddr_in serverAddr;

	wstring playerId;
	wstring playerPassword;
	int playerScore;

	bool isLogin = false;
};