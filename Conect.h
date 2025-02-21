#if 0
#pragma once
#include <cstdint>

struct PLAYER
{
    int x;
    int y;
    int state;
    int playerID;
};

class Conect 
{
public:
	Conect();
	~Conect();
	void Conecting();
private:
    // �T�[�o��IP�A�h���X
    const char* SERVER_ADDRESS = "192.168.43.1";		// �ڑ���Ȃ񂩓K���ɃN���X���[�g�Ƃ���āI
    // �T�[�o�̃|�[�g�ԍ�
    const unsigned short SERVER_PORT = 8888;

    int inet_pton_ipv6(const char* str, unsigned char* addr);
    int inet_pton_ipv4(const char* str, uint32_t& addr);
    int inet_pton_custom(const char* str, void* addr);
};
#endif
#pragma once

#include <cstdint>
#include <string>
#include <stdexcept>

// PLAYER�\���́i�v���C���[�̍��W���Ԃ��i�[�j
struct PLAYER
{
    int x;
    int y;
    int state;
    int playerID;
};

// �l�b�g���[�N�ڑ��N���X
class Conect
{
public:
    // �R���X�g���N�^�ƃf�X�g���N�^
    Conect();
    ~Conect();
    bool ConnectToServer();  // �ڑ��������s���A���������� true ��Ԃ�
    void ReceiveData();      // �T�[�o����̃f�[�^����M����
    void SendData(const PLAYER& player);  // �v���C���[�̃f�[�^�𑗐M����

private:
    // �T�[�o��IP�A�h���X�ƃ|�[�g�ԍ�
    std::string m_serverAddress;
    unsigned short m_serverPort;

    // �\�P�b�g
    int m_socket;

    // �ڑ������i�����Ŏg�p�j
    void InitializeSocket();
    void CleanupSocket();

    // �G���[����
    void HandleError(const std::string& errorMessage);

    // �A�h���X�ϊ������iIPv4/IPv6�j
    int inet_pton_ipv6(const char* str, unsigned char* addr);
    int inet_pton_ipv4(const char* str, uint32_t& addr);
    int inet_pton_custom(const char* str, void* addr);
};
