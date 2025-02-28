#pragma once
#include <DxLib.h>



struct PLAYER
{
	bool job;//0:Hunter,1:Runner
	int x, y;//x:�S��,y:�R��
	int state;
	int playerID;//�S��
	//   job  x    y   state  ID
	//��F0  0344 652    1   1234
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
	int CharToIP(IPDATA &ipData);
	void SetPlayerData(bool _job, int _x, int _y, int _state, int _playerID);
	void SetPlayerData(PLAYER _pData);
};

