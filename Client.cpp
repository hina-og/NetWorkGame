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
	if (sock == -1) {
		return;
	}
	CharToIP(ipAddress);
	prevPlayerNum = 1;
	nowPlayerNum = 1;
	firstSend = true;
	Recved = false;
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
	//unsigned int ip[4];
	//int parsed = sscanf(SERVER_ADDRESS, "%u.%u.%u.%u", &ip[0], &ip[1], &ip[2], &ip[3]);

	//if (parsed == 4) {
	//	ipData.d1 = ip[0];
	//	ipData.d2 = ip[1];
	//	ipData.d3 = ip[2];
	//	ipData.d4 = ip[3];
	//	return 0; // ����
	//}

	//return -1; // ���s

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
	prevPlayerNum = nowPlayerNum;

	if (firstSend) {
		NetWorkSendUDP(sock, ipAddress, serverPort, data, sizeof(data));
		firstSend = false;
	}
	if (Recved) {
		NetWorkSendUDP(sock, ipAddress, serverPort, data, sizeof(data));
		Recved = false;
	}
}

void Client::Recv()
{
	IPDATA serverIP;
	int serverPort;

	std::stringstream ss;
	std::vector<std::string> pStr;
	std::string recvData;

	int ret = NetWorkRecvUDP(sock, &serverIP, &serverPort, data, sizeof(data), FALSE);
	if (ret > 0 )
	{
		Recved = true;
		std::string playerNum = "";
		ss << data;
		std::getline(ss, playerNum, '|');
		nowPlayerNum = stoi(playerNum);
		for (int i = 0; i < stoi(playerNum); i++)
		{
			std::getline(ss, pStr[i], '|');

			pData = 
			{
				(pStr[0] == "0"),//job
				std::stoi(pStr[i].substr(1,  4)),//x : �Q�����ڂ���S����
				std::stoi(pStr[i].substr(5,  3)),//y : �S�����ڂ���R����
				std::stoi(pStr[i].substr(8, 1)), //state : �V�����ڂ���P����
				std::stoi(pStr[i].substr(9, 4))  //ID : �W�����ڂ���S����
			};
			playerList[i] = pData;
			// playerID: 10-13�o�C�g�ځi1234�j
			pData.playerID = std::stoi(std::string(data + 11, 4));

			//pData;
			//if (i == 0) {
			//	// job: 1�o�C�g�ځi0 �� Hunter�A1 �� Runner�j
			//	pData[i].job = (data[2] == '0');

			//	// x: 2-5�o�C�g�ځi1000�j => data[3]����data[6]
			//	pData[i].x = std::stoi(std::string(data + 3, 4));

			//	// y: 6-8�o�C�g�ځi200�j => data[7]����data[9]
			//	pData[i].y = std::stoi(std::string(data + 7, 3));

			//	// state: 9�o�C�g�ځi3�j
			//	pData[i].state = std::stoi(std::string(data + 10, 1));

			//	// playerID: 10-13�o�C�g�ځi1234�j
			//	pData[i].playerID = std::stoi(std::string(data + 11, 4));
			//}
			//else {
			//	// job: 1�o�C�g�ځi0 �� Hunter�A1 �� Runner�j
			//	pData[i].job = data[2];

			//	// x: 2-5�o�C�g�ځi1000�j => data[3]����data[6]
			//	pData[i].x = std::stoi(std::string(data + 3, 4));

			//	// y: 6-8�o�C�g�ځi200�j => data[7]����data[9]
			//	pData[i].y = std::stoi(std::string(data + 7, 3));

			//	// state: 9�o�C�g�ځi3�j
			//	pData[i].state = std::stoi(std::string(data + 10, 1));

			//	// playerID: 10-13�o�C�g�ځi1234�j
			//	pData[i].playerID = std::stoi(std::string(data + 11, 4));
			//}
			//
		}
	}
}

void Client::SetSendData(bool _job, int _x, int _y, int _state, int _playerID)
{
	//memset(data, 0, sizeof(data)); // ���M�o�b�t�@���N���A
	snprintf(data, sizeof(data), "%1d%04d%03d%1d%04d", _job, _x, _y, _state, _playerID);
}

void Client::SetSendData(PLAYER _pData)
{
	memset(data, 0, sizeof(data)); // ���M�o�b�t�@���N���A
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

void Client::SetPlayerData(PLAYER& _pData)
{

}
