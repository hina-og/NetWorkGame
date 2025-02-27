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
#include <DxLib.h>

const unsigned short SERVER_PORT = 8888;
BYTE Data[65500];

struct PLAYER
{
	int x, y;
	int state;
	int playerID;
};

int main()
{
	std::cout << "�T�[�o�[" << std::endl;

	PLAYER pData;

	//if (DxLib_Init() == -1)		// �c�w���C�u��������������
	//{
	//	return -1;			// �G���[���N�����璼���ɏI��
	//}
	//�\�P�b�g�쐬
	int sock;
	sock = MakeUDPSocket(SERVER_PORT);

	// �p�P�b�g��M
	while (ProcessMessage() == 0)
	{
		// �f�[�^����M
		int ret = NetWorkRecvUDP(sock, NULL, NULL, Data, sizeof(Data), FALSE);
		if (ret >= 0)
		{
			std::cout << "��M���܂�" << std::endl;
		}
	}

	//DxLib_End();

	return 0;
}