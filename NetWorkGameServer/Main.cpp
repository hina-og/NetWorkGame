#if 0

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>
#include <bitset>
#pragma comment( lib, "ws2_32.lib" )

// �|�[�g�ԍ�
const unsigned short SERVER_PORT = 8888;

struct PLAYER
{
	int x, y;
	int state;
	int playerID;
};

int main()
{
	std::vector<PLAYER> playerList;
	std::vector<SOCKADDR_IN> addressList;

	std::cout << "Server" << std::endl;


	//WinSock������
	WSADATA	wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		//�G���[����
		std::cout << "WinSock�������Ɏ��s���܂���" << std::endl;
	}

	//�\�P�b�g�̍쐬
	SOCKET	listenSock;
	if ((listenSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		//�G���[����
		std::cout << "�\�P�b�g�̍쐬�Ɏ��s���܂���" << std::endl;
	}

	// sock���m���u���b�L���O���[�h��
	unsigned long cmdarg = 0x01;
	ioctlsocket(listenSock, FIONBIO, &cmdarg);

	//�Œ�A�h���X�̊��蓖��
	SOCKADDR_IN bindAddr;

	memset(&bindAddr, 0, sizeof(bindAddr));
	bindAddr.sin_family = AF_INET;
	bindAddr.sin_port = htons(SERVER_PORT);
	bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(listenSock, (SOCKADDR*)&bindAddr, sizeof(bindAddr)) != 0)
	{
		//�G���[����
		std::cout << "�Œ�A�h���X�̊��蓖�ĂɎ��s���܂���" << std::endl;
	}

	// ����M���̃��[�v
	while (true)
	{
		bool isNewPlayer = true;
		int ret;

		PLAYER p;
		SOCKADDR_IN clientAddr;	// �N���C�A���g�̃A�h���X���i�[�̈�

		// ��M�@���N���C�A���g�̃A�h���X�����擾
		int fromlen = sizeof(clientAddr);

		ret = recvfrom(listenSock, (char*)&p, sizeof(p), 0, nullptr, nullptr);

		// ��M��
		if (ret > 0)
		{
			std::cout << "��M���܂�" << std::endl;

			//for (int i = 0; i != addressList.size(); i++)
			//{
			//	if ((clientAddr.sin_addr.s_addr == addressList[i].sin_addr.s_addr) && (clientAddr.sin_port == addressList[i].sin_port))
			//	{
			//		isNewPlayer = false;
			//		break;
			//	}
			//	else if (i == addressList.size() - 1)
			//	{
			//		addressList.push_back(clientAddr);
			//	}
			//}
			//if (isNewPlayer)
			//{
			//	for (int i = 0; i != playerList.size(); i++)
			//	{
			//		if (i == 0)
			//		{
			//			p.playerID = rand() % 1000;
			//		}
			//		if (p.playerID == playerList[i].playerID)//I����ID�����łɂ���Ȃ�ŏ�����
			//		{
			//			i = 0;
			//			continue;
			//		}
			//	}
			//	playerList.push_back(p);
			//}

			////�f�[�^�o��
			//for (int i = 0; i < playerList.size(); i++)
			//{
			//	////std::bitset<8> bitVal(playerList[i].state);
			//	//std::cout << "ID : " << playerList[i].playerID << std::endl;
			//	//std::cout << "Pos : " << playerList[i].x << "," << playerList[i].y << std::endl;
			//	//std::cout << "State : " << playerList[i].state << std::endl;

			//}
		}
		// ��M�G���[	����M����WSAEWOULDBLOCK������
		else if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			// ��M���s�̃G���[����
			return 0;
		}

		ret = sendto(listenSock, (char*)&p, sizeof(p), 0, (SOCKADDR*)&clientAddr, sizeof(clientAddr));
		// �����M�ȊO�̃G���[
		//if (ret == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
		//{
		//	break;
		//}
	}
	//�\�P�b�g�̔j��
	if (closesocket(listenSock) == SOCKET_ERROR)
	{
		//�G���[����
		std::cout << "�\�P�b�g�̔j���Ɏ��s���܂���" << std::endl;
	}
	// WinSock�I������
	if (WSACleanup() != 0)
	{
		// �G���[����
		std::cout << "WinSock�I�������Ɏ��s���܂���" << std::endl;
	}

	return 0;
}

#endif

#include <iostream>
#include <cstring>
#include <string>
#include <DxLib.h>
#include <vector>

const unsigned short SERVER_PORT = 10654;
char data[14];

struct PLAYER
{
	bool job;//0:Hunter,1:Runner
	int x, y;//x:�S��,y:�R��
	int state;
	int playerID;//�S��
	//   job  x    y   state  ID
	//��F0  0344 652    1   1234
};

std::vector<PLAYER> playerList;

int MakePlayerID();
void SetData(PLAYER _pData);

int main()
{
	std::cout << "�T�[�o�[" << std::endl;

	//�\�P�b�g�쐬
	int sock;
	sock = MakeUDPSocket(SERVER_PORT);

	// �p�P�b�g��M
	while (ProcessMessage() == 0)
	{
		
		IPDATA playerIP = {};//���M����IP�A�h���X
		int playerPort = 0;

		// �f�[�^����M
		int ret = NetWorkRecvUDP(sock, &playerIP, &playerPort, data, sizeof(data), FALSE);
		if (ret > 0)
		{
			std::cout << "��M���܂�" << std::endl;

			PLAYER p = {};

			// job: 1�o�C�g�ځi00 �� Hunter�A01 �� Runner�j
			p.job = (data[0] == '0' && data[1] == '0') ? 0 : 1;

			// x: 2-5�o�C�g�ځi1000�j => data[1]����data[4]
			p.x = std::stoi(std::string(data + 1, 4));

			// y: 6-8�o�C�g�ځi200�j => data[5]����data[7]
			p.y = std::stoi(std::string(data + 5, 3));

			// state: 9�o�C�g�ځi3�j
			p.state = std::stoi(std::string(data + 8, 1));

			// playerID: 10-13�o�C�g�ځi1234�j
			p.playerID = std::stoi(std::string(data + 9, 4));

			// ���ʂ�\��
			std::cout << "job: " << p.job << ", x: " << p.x << ", y: " << p.y
				<< ", state: " << p.state << ", playerID: " << p.playerID << std::endl;
			//std::memcpy(&p,data, sizeof(PLAYER));



			if (p.playerID == 0)
			{
				//p.playerID = MakePlayerID();
				p.playerID = MakePlayerID();
				if (playerList.size() == 0)
				{
					playerList.push_back(p);//List�ɒǉ�����
				}
			}
			for (int i = 0; i < playerList.size(); i++)
			{
				if (p.playerID == playerList[i].playerID)
				{
					break;
				}
				if (i == playerList.size() - 1)//�Ō�܂Ō��ē���ID���Ȃ����
				{
					playerList.push_back(p);//List�ɒǉ�����
				}
			}
			SetData(p);

			for (int i = 0; i < playerList.size() - 1; i++)
			{
				int sendResult = NetWorkSendUDP(sock, playerIP, playerPort, data, sizeof(data));

				if (sendResult > 0)
				{
					std::cout << "ID : " << playerList[i].playerID << "�ɑ��M���܂�" << std::endl;
				}
			}
		}
	}

	return 0;
}

int MakePlayerID()
{
	int ID = rand() % 9999;
	for (int i = 0; i < playerList.size(); i++)
	{
		if (ID == playerList[i].playerID)//����ID�����łɂ���Ȃ�ŏ�����
		{
			i = 0;
			ID = rand() % 9999;
			continue;
		}
	}
	return ID;
}

void SetData(PLAYER _pData)
{
	snprintf(data, sizeof(data), "%1d%04d%03d%1d%04d", _pData.job, _pData.x, _pData.y, _pData.state, _pData.playerID);
}
