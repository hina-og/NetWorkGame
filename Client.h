#pragma once
#include <DxLib.h>

const char* SERVER_ADDRESS{ "192.168.43.1" };
const unsigned short SERVER_PORT = 8888;

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
	PLAYER p;
public:
	Client();
	~Client();

	void Connect();
	int CharToIP(const char* ipString, IPDATA ipData);
	void SetPlayerData(bool _job, int _x, int _y, int _state, int _playerID);
	void SetPlayerData(PLAYER _pData);
};

