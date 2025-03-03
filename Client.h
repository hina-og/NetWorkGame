#pragma once
#include <DxLib.h>
#include <vector>


struct PLAYER
{
	bool job;//0:Hunter,1:Runner
	int x, y;//x:ÇSåÖ,y:ÇRåÖ
	int state;
	int playerID;//ÇSåÖ
	//   job  x    y   state  ID
	//ó·ÅF0  0344 652    1   1234
};

class Client
{
	int sock;
	IPDATA ipAddress;
	PLAYER pData;

	std::vector<PLAYER> playerList;
public:
	Client();
	~Client();

	void Connect();
	int CharToIP(IPDATA &ipData);
	void Send();
	void Recv();

	void SetSendData(bool _job, int _x, int _y, int _state, int _playerID);
	void SetSendData(PLAYER _pData);
	void SetPlayerData(PLAYER& _pData);
};

