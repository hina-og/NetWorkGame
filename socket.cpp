//#include "Socket.h"
//#include <WinSock2.h>
//#include <WS2tcpip.h>
//#pragma comment( lib, "ws2_32.lib" )
//
//// �|�[�g�ԍ�
//const unsigned short SERVER_PORT = 8888;
//// ����M���郁�b�Z�[�W�̍ő�l
//const unsigned int MESSAGE_LENGTH = 1024;
//
//Socket::Socket()
//{
//	WSAStartup(MAKEWORD(2, 2), &wsaData);
//	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
//}
//
//Socket::~Socket()
//{
//	//�\�P�b�g�̔j��
//	closesocket(sock);
//	// WinSock�I������
//	WSACleanup();
//}
//
//void Socket::sockmain()
//{
//	int ret;
//	char buff[MESSAGE_LENGTH];	// ����M������̊i�[�̈�
//	SOCKADDR_IN serverAddr;	// �T�[�o�̃A�h���X���i�[�̈�
//	// �T�[�o�̈�����Z�b�g
//
//
//	/*std::sprintf(buff, "%d", transform_.position_.x);*/
//
//
//	// ���M�@����M���Ɏ擾�����N���C�A���g�̃A�h���X�ɑ��M
//	memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = AF_INET;				// IPv4�A�h���X
//	serverAddr.sin_port = htons(SERVER_PORT);			// �T�[�o�̃|�[�g�ԍ�
//	inet_pton(AF_INET, "192.168.43.1", &serverAddr.sin_addr.s_addr);		// �T�[�o��IP�A�h���X
//	ret = sendto(sock, buff, strlen(buff), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
//	if (ret != strlen(buff))
//	{
//		//std::cout << "�G���[" << std::endl;
//		// �G���[����
//	}
//	else
//	{
//		//buff = '\0';
//		//std::cout << "���M����" << std::endl;
//	}
//}
