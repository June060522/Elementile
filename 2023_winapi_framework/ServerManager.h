#pragma once
class GameSceneUI;
class ServerManager
{
	SINGLE(ServerManager)
public:
	bool Load();
	void Save();
	void GetRanking(GameSceneUI* _pGameSceneUI);
	void Release();
public:
	string GetplayerID() { return playerId; }
	string GetplayerPassword() { return playerPassword; }
	int GetplayerScore() { return playerScore; }
	bool GetplayerLogin() { return isLogin; }

	void SetplayerID(string val) { playerId = val; }
	void SetplayerPassword(string val) { playerPassword = val; }
	void SetplayerScore(int val) { playerScore = val; }
	void SetLogin(bool val) { isLogin = val; }
private:
	WSADATA wsaData;
	SOCKET clientSocket;
	sockaddr_in serverAddr;

	string playerId;
	string playerPassword;
	int playerScore;

	bool isLogin = false;

	std::mutex sendMutex;
	std::mutex recvMutex;
};