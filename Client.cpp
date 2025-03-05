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
	//	return 0; // 成功
	//}

	//return -1; // 失敗

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
				std::stoi(pStr[i].substr(1,  4)),//x : ２文字目から４文字
				std::stoi(pStr[i].substr(5,  3)),//y : ４文字目から３文字
				std::stoi(pStr[i].substr(8, 1)), //state : ７文字目から１文字
				std::stoi(pStr[i].substr(9, 4))  //ID : ８文字目から４文字
			};
			playerList[i] = pData;
			// playerID: 10-13バイト目（1234）
			pData.playerID = std::stoi(std::string(data + 11, 4));

			//pData;
			//if (i == 0) {
			//	// job: 1バイト目（0 → Hunter、1 → Runner）
			//	pData[i].job = (data[2] == '0');

			//	// x: 2-5バイト目（1000） => data[3]からdata[6]
			//	pData[i].x = std::stoi(std::string(data + 3, 4));

			//	// y: 6-8バイト目（200） => data[7]からdata[9]
			//	pData[i].y = std::stoi(std::string(data + 7, 3));

			//	// state: 9バイト目（3）
			//	pData[i].state = std::stoi(std::string(data + 10, 1));

			//	// playerID: 10-13バイト目（1234）
			//	pData[i].playerID = std::stoi(std::string(data + 11, 4));
			//}
			//else {
			//	// job: 1バイト目（0 → Hunter、1 → Runner）
			//	pData[i].job = data[2];

			//	// x: 2-5バイト目（1000） => data[3]からdata[6]
			//	pData[i].x = std::stoi(std::string(data + 3, 4));

			//	// y: 6-8バイト目（200） => data[7]からdata[9]
			//	pData[i].y = std::stoi(std::string(data + 7, 3));

			//	// state: 9バイト目（3）
			//	pData[i].state = std::stoi(std::string(data + 10, 1));

			//	// playerID: 10-13バイト目（1234）
			//	pData[i].playerID = std::stoi(std::string(data + 11, 4));
			//}
			//
		}
	}
}

void Client::SetSendData(bool _job, int _x, int _y, int _state, int _playerID)
{
	//memset(data, 0, sizeof(data)); // 送信バッファをクリア
	snprintf(data, sizeof(data), "%1d%04d%03d%1d%04d", _job, _x, _y, _state, _playerID);
}

void Client::SetSendData(PLAYER _pData)
{
	memset(data, 0, sizeof(data)); // 送信バッファをクリア
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
