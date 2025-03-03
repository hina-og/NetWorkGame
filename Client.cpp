#include "Client.h"
#include <sstream>


//const char* SERVER_ADDRESS{ "192.168.43.1" };


const char* SERVER_ADDRESS{ "192.168.33.6" };


const unsigned short SERVER_PORT = 10654;
char data[1024];

Client::Client()
{
	sock = MakeUDPSocket(-1);
	CharToIP(ipAddress);
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

	// IPDATA 型に変換
	ipData.d1 = ip[0];
	ipData.d2 = ip[1];
	ipData.d3 = ip[2];
	ipData.d4 = ip[3];

	return 0; // 成功
}

void Client::Send()
{
	int serverPort = SERVER_PORT;
	NetWorkSendUDP(sock, ipAddress, serverPort, data, sizeof(data));
}

void Client::Recv()
{
	IPDATA serverIP;
	int serverPort;

	int ret = NetWorkRecvUDP(sock, &serverIP, &serverPort, data, sizeof(data), FALSE);
	if (ret > 0)
	{

		//std::string receivedStr(data, ret);
		//std::stringstream ss(receivedStr);
		//std::string token;

		//std::getline(ss, token, '|');  // プレイヤー数を取得
		//int playerCount = std::stoi(token);

		//std::vector<PLAYER> newPlayerList;

		//for (int i = 0; i < playerCount; i++)
		//{
		//	std::getline(ss, token, '|');
		//	if (token.size() == 13)
		//	{
		//		PLAYER p;
		//		p.job = (token[0] == '0' && token[1] == '0') ? 0 : 1;
		//		p.x = std::stoi(token.substr(1, 4));
		//		p.y = std::stoi(token.substr(5, 3));
		//		p.state = std::stoi(token.substr(8, 1));
		//		p.playerID = std::stoi(token.substr(9, 4));

		//		newPlayerList.push_back(p);
		//	}
		//}

		//playerList = newPlayerList; // 受信データで更新

		pData = {};
		// job: 1バイト目（00 → Hunter、01 → Runner）
		pData.job = (data[0] == '0' && data[1] == '0') ? 0 : 1;

		// x: 2-5バイト目（1000） => data[1]からdata[4]
		pData.x = std::stoi(std::string(data + 1, 4));

		// y: 6-8バイト目（200） => data[5]からdata[7]
		pData.y = std::stoi(std::string(data + 5, 3));

		// state: 9バイト目（3）
		pData.state = std::stoi(std::string(data + 8, 1));

		// playerID: 10-13バイト目（1234）
		pData.playerID = std::stoi(std::string(data + 9, 4));
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

void Client::SetPlayerData(PLAYER& _pData)
{
	_pData = pData;
}
