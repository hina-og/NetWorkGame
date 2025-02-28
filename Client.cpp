#include "Client.h"
#include <sstream>

char data[13];

Client::Client()
{
	sock = MakeUDPSocket(SERVER_PORT);
	CharToIP(SERVER_ADDRESS, ipAddress);
	p = {};
}

Client::~Client()
{
	DeleteUDPSocket(sock);
}

void Client::Connect()
{
	SetPlayerData(p);
	NetWorkSendUDP(sock, ipAddress, SERVER_PORT, data, sizeof(data));
}

int Client::CharToIP(const char* ipString, IPDATA ipData)
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

void Client::SetPlayerData(bool _job, int _x, int _y, int _state, int _playerID)
{
	snprintf(data, sizeof(data), "%1d%04d%03d%1d%04d", _job, _x, _y, _state, _playerID);
}

void Client::SetPlayerData(PLAYER _pData)
{
	snprintf(data, sizeof(data), "%1d%04d%03d%1d%04d", _pData.job, _pData.x, _pData.y, _pData.state, _pData.playerID);
}
