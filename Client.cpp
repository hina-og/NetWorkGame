#include "Client.h"
#include <sstream>


const char* SERVER_ADDRESS{ "192.168.43.1" };
//const char* SERVER_ADDRESS{ "192.168.33.6" };

//const char* SERVER_ADDRESS{ "192.168.43.54" };


const unsigned short SERVER_PORT = 10654;
char data[1024];

Client::Client()
{
	sock = MakeUDPSocket(-1);
	CharToIP(ipAddress);
	prevPlayerNum = 1;
	nowPlayerNum = 1;
}

Client::~Client()
{
	DeleteUDPSocket(sock);
}

void Client::Connect()
{
	Send();
	Recv();
}

int Client::CharToIP(IPDATA &ipData)
{
	unsigned int ip[4];

	std::stringstream ss(SERVER_ADDRESS);
	std::string token;

	for (int i = 0; i < 4; i++)
	{
		std::getline(ss, token, '.');
		ip[i] = std::stoi(token);
	}

	// IPDATA Œ^‚É•ÏŠ·
	ipData.d1 = ip[0];
	ipData.d2 = ip[1];
	ipData.d3 = ip[2];
	ipData.d4 = ip[3];

	return 0; // ¬Œ÷
}

void Client::Send()
{
	int serverPort = SERVER_PORT;
	NetWorkSendUDP(sock, ipAddress, serverPort, data, sizeof(data));
	prevPlayerNum = nowPlayerNum;
}

void Client::Recv()
{
	IPDATA serverIP;
	int serverPort;

	std::stringstream ss;
	std::vector<std::string> pStr;
	std::string recvData;

	int ret = NetWorkRecvUDP(sock, &serverIP, &serverPort, data, sizeof(data), FALSE);
	if (ret > 0)
	{
		std::string playerNum;
		ss << data;
		std::getline(ss, playerNum, '|');
		nowPlayerNum = stoi(playerNum);
		for (int i = 0; i < stoi(playerNum); i++)
		{
			std::getline(ss, pStr[i], '|');

			pData = 
			{
				(pStr[0] == "0"),//job
				std::stoi(pStr[i].substr(1,  4)),//x : ‚Q•¶Žš–Ú‚©‚ç‚S•¶Žš
				std::stoi(pStr[i].substr(5,  3)),//y : ‚S•¶Žš–Ú‚©‚ç‚R•¶Žš
				std::stoi(pStr[i].substr(8, 1)), //state : ‚V•¶Žš–Ú‚©‚ç‚P•¶Žš
				std::stoi(pStr[i].substr(9, 4))  //ID : ‚W•¶Žš–Ú‚©‚ç‚S•¶Žš
			};
			playerList[i] = pData;
		}
	}
}

void Client::SetSendData(bool _job, int _x, int _y, int _state, int _playerID)
{
	snprintf(data, sizeof(data), "%1d%04d%03d%1d%04d", _job, _x, _y, _state, _playerID);
}

void Client::SetSendData(PLAYER _pData)
{
	snprintf(data, sizeof(data), "%1d%04d%03d%1d%04d", _pData.job, _pData.x, _pData.y, _pData.state, _pData.playerID);
}

void Client::SetPlayerData(std::vector<PLAYER>& _pData)
{
	_pData = playerList;
}

int Client::AddPlayerNum()
{
	int pNum = 0;
	if (prevPlayerNum < nowPlayerNum)
	{
		pNum = nowPlayerNum - prevPlayerNum;
	}
	return pNum;
}
