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

	// IPDATA �^�ɕϊ�
	ipData.d1 = ip[0];
	ipData.d2 = ip[1];
	ipData.d3 = ip[2];
	ipData.d4 = ip[3];

	return 0; // ����
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

		//std::getline(ss, token, '|');  // �v���C���[�����擾
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

		//playerList = newPlayerList; // ��M�f�[�^�ōX�V

		pData = {};
		// job: 1�o�C�g�ځi00 �� Hunter�A01 �� Runner�j
		pData.job = (data[0] == '0' && data[1] == '0') ? 0 : 1;

		// x: 2-5�o�C�g�ځi1000�j => data[1]����data[4]
		pData.x = std::stoi(std::string(data + 1, 4));

		// y: 6-8�o�C�g�ځi200�j => data[5]����data[7]
		pData.y = std::stoi(std::string(data + 5, 3));

		// state: 9�o�C�g�ځi3�j
		pData.state = std::stoi(std::string(data + 8, 1));

		// playerID: 10-13�o�C�g�ځi1234�j
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
