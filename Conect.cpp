#if 0
#include "Conect.h"
#include <DxLib.h>
//#include <winsock2.h>
//#include <ws2tcpip.h>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include<cstdio>
#include<string>
#include<vector>


#pragma comment(lib, "ws2_32.lib")  // �����N���郉�C�u�������w��



Conect::Conect()
{
    // WinSock2.2 ����������
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        // �G���[����
    }
    /*
        ���͂�
        �G���[����return 0�ŏI�������ėǂ�
    */

    // UDP�\�P�b�g�̍쐬
    SOCKET sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
    {
        // �G���[����
        /*
        ���͂�
        */
    }

}

Conect::~Conect()
{
}

void Conect::Conecting()
{


    // sock���m���u���b�L���O���[�h��
    unsigned long cmdarg = 0x01;
    int ret = ioctlsocket(sock, FIONBIO, &cmdarg);

    if (ret == SOCKET_ERROR)
    {
        // �G���[����
         /*
        ���͂�
        */
        // WSAGetLastError()��WinSock����݂̒��߂̃G���[�R�[�h�擾
        int errorCode = WSAGetLastError();
        // WinSock Api Error WOULD BLOCK ...���Ԃ�u���b�L���O������...����M
        if (errorCode == WSAEWOULDBLOCK)
        {
            // ����M����������
        }
        else
        {
            // ��M�G���[
        }
    }
    else { //��M�ł���

    }


    // �T�[�o�A�h���X�̎w��
    SOCKADDR_IN serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));	// 0�N���A�ŏ�����
    serverAddr.sin_family = AF_INET;				// IPv4�A�h���X
    serverAddr.sin_port = htons(SERVER_PORT);			// �T�[�o�̃|�[�g�ԍ�
    //inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr.s_addr);		// �T�[�o��IP�A�h���X
    inet_pton_custom(SERVER_ADDRESS, &serverAddr.sin_addr.s_addr);

    // �ڑ��v��
    if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        // �G���[����
    }

    while (1)
    {
        // �T�C�Y�Ƃ��F�͂��C��
        PLAYER param = { 0, 0, 5,0 };
        // �}�E�X���W�擾���Acircle��centerX��centerT�Ɋi�[
        GetMousePoint(&param.x, &param.y);
        // �`��
      /*  DrawCircle(pParam.centerX, pParam.centerY, circle.size, circle.color, 1);*/

        // �T�[�o( serverAddr )�Ɂ��̏�񑗐M
        PLAYER value;	// ���M�f�[�^�̊i�[�̈�
        /*value = {circle.centerX,circle.centerY,circle.size,circle.color };*/
        PLAYER sendParam;
        /* sendCircle = { htonl(circle.centerX), htonl(circle.centerY), htonl(circle.color), htonl(circle.size) };*/
        sendParam.x = htonl(param.x);
        sendParam.y = htonl(param.y);
      /*  sendCircle.color = htonl(circle.color);
        sendCircle.size = htonl(circle.size);*/
        ret = send(sock, (char*)&sendParam, sizeof(sendParam), 0);
        if (ret != sizeof(sendParam))
        {
            // �G���[����
             /*
            ���͂�
            ���o�C�g�I�[�_�[�̕ϊ���Y�ꂸ�ɁI
        */
        }


        // �����M�ȊO�̃G���[
        if (ret == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
        {
            // �G���[����
        }

        WaitTimer(16);
        if (ProcessMessage() == -1 || CheckHitKey(KEY_INPUT_ESCAPE) == 1)
        {
            break;
        }
    }
}

int Conect::inet_pton_ipv6(const char* str, unsigned char* addr)
{
    unsigned int values[8];
    char colon1, colon2, colon3, colon4, colon5, colon6, colon7, colon8;

    // stringstream���g���āA16�i���̕������p�[�X
    std::istringstream iss(str);
    if (iss >> std::hex >> values[0] >> colon1
        >> std::hex >> values[1] >> colon2
        >> std::hex >> values[2] >> colon3
        >> std::hex >> values[3] >> colon4
        >> std::hex >> values[4] >> colon5
        >> std::hex >> values[5] >> colon6
        >> std::hex >> values[6] >> colon7
        >> std::hex >> values[7] &&
        colon1 == ':' && colon2 == ':' && colon3 == ':' &&
        colon4 == ':' && colon5 == ':' && colon6 == ':' &&
        colon7 == ':') {

        for (int i = 0; i < 8; ++i) {
            addr[i * 2] = (values[i] >> 8) & 0xFF;
            addr[i * 2 + 1] = values[i] & 0xFF;
        }

        return 1;  // ����
    }

    return 0;  // �s����IPv6�A�h���X�`��
}

int Conect::inet_pton_ipv4(const char* str, uint32_t& addr)
{
    unsigned int b1, b2, b3, b4;
    char dot1, dot2, dot3;

    // stringstream���g���āA������𐮐��Ƃ��ăp�[�X
    std::istringstream iss(str);
    if (iss >> b1 >> dot1 >> b2 >> dot2 >> b3 >> dot3 >> b4
        && dot1 == '.' && dot2 == '.' && dot3 == '.') {
        // �e������0?255�͈͓̔����m�F
        if (b1 <= 255 && b2 <= 255 && b3 <= 255 && b4 <= 255) {
            addr = (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
            return 1;  // ����
        }
    }
    return 0;  // �s����IPv4�A�h���X�`��
}



// �����̃A�h���X�ɑΉ�����inet_pton�̑�֊֐�
int Conect::inet_pton_custom(const char* str, void* addr) {
    // IPv4�̃`�F�b�N
    if (strchr(str, '.') != nullptr) {
        return inet_pton_ipv4(str, *(uint32_t*)addr);
    }

    // IPv6�̃`�F�b�N
    if (strchr(str, ':') != nullptr) {
        return inet_pton_ipv6(str, (unsigned char*)addr);
    }

    return 0;  // �����ȃA�h���X�`��
}
#endif
#if 1
#include "Conect.h"

// �R���X�g���N�^
Conect::Conect(const std::string& serverAddress, unsigned short port)
    : m_serverAddress(serverAddress), m_serverPort(port), m_socket(INVALID_SOCKET)
{
    // WinSock2.2 ����������
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        throw std::runtime_error("WinSock initialization failed");
    }
}

// �f�X�g���N�^
Conect::~Conect()
{
    CleanupSocket();
    WSACleanup();
}

// �\�P�b�g�̏�����
void Conect::InitializeSocket()
{
    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_socket == INVALID_SOCKET)
    {
        HandleError("Failed to create socket");
    }

    // �m���u���b�L���O���[�h�ɐݒ�
    unsigned long cmdarg = 0x01;
    if (ioctlsocket(m_socket, FIONBIO, &cmdarg) == SOCKET_ERROR)
    {
        HandleError("Failed to set socket to non-blocking mode");
    }
}

// �\�P�b�g�̃N���[���A�b�v
void Conect::CleanupSocket()
{
    if (m_socket != INVALID_SOCKET)
    {
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
    }
}


// �T�[�o�ɐڑ�����
void Conect::ConnectToServer()
{
    InitializeSocket();

    // �T�[�o�A�h���X�̐ݒ�
    SOCKADDR_IN serverAddr = {};
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(m_serverPort);

    if (!inet_pton_custom(m_serverAddress.c_str(), &serverAddr.sin_addr.s_addr))
    {
        HandleError("Invalid server address format");
    }

    if (connect(m_socket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        HandleError("Failed to connect to server");
    }
    SendData(serverAddr);
}

void Conect::ReceiveData()
{
}

// �T�[�o�Ƀf�[�^�𑗐M����
void Conect::SendData(SOCKADDR_IN _serverAddr)
{
    //PLAYER sendParam = player;
    //sendParam.x = htonl(player.x);
    //sendParam.y = htonl(player.y);

    PLAYER sendParam;
    sendParam.x = htonl(714);
    sendParam.y = htonl(800);

    int ret = sendto(m_socket, (char*)&sendParam, sizeof(sendParam), 0,(SOCKADDR*)&_serverAddr,sizeof(_serverAddr));
    if (ret == SOCKET_ERROR)
    {
        HandleError("Failed to send data");
    }
}

// �G���[����
void Conect::HandleError(const std::string& errorMessage)
{
    int errorCode = WSAGetLastError();
    std::cerr << errorMessage << " Error Code: " << errorCode << std::endl;
    throw std::runtime_error(errorMessage);
}

// IPv6�A�h���X���o�C�g��ɕϊ�
int Conect::inet_pton_ipv6(const char* str, unsigned char* addr)
{
    unsigned int values[8];
    char colon[7];

    std::istringstream iss(str);
    if (iss >> std::hex >> values[0] >> colon[0]
        >> std::hex >> values[1] >> colon[1]
        >> std::hex >> values[2] >> colon[2]
        >> std::hex >> values[3] >> colon[3]
        >> std::hex >> values[4] >> colon[4]
        >> std::hex >> values[5] >> colon[5]
        >> std::hex >> values[6] >> colon[6])
    {
        for (int i = 0; i < 8; ++i) {
            addr[i * 2] = (values[i] >> 8) & 0xFF;
            addr[i * 2 + 1] = values[i] & 0xFF;
        }
        return 1;
    }

    return 0;
}

// IPv4�A�h���X���o�C�g��ɕϊ�
int Conect::inet_pton_ipv4(const char* str, uint32_t& addr)
{
    unsigned int b1, b2, b3, b4;
    char dot1, dot2, dot3;

    std::istringstream iss(str);
    if (iss >> b1 >> dot1 >> b2 >> dot2 >> b3 >> dot3 >> b4
        && dot1 == '.' && dot2 == '.' && dot3 == '.')
    {
        if (b1 <= 255 && b2 <= 255 && b3 <= 255 && b4 <= 255) {
            addr = (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
            return 1;
        }
    }
    return 0;
}

// IPv4 �܂��� IPv6 �A�h���X�̕ϊ���I��
int Conect::inet_pton_custom(const char* str, void* addr)
{
    if (strchr(str, '.') != nullptr)
    {
        return inet_pton_ipv4(str, *(uint32_t*)addr);
    }
    if (strchr(str, ':') != nullptr)
    {
        return inet_pton_ipv6(str, (unsigned char*)addr);
    }

    return 0;
}
#endif