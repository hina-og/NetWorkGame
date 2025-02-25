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


#pragma comment(lib, "ws2_32.lib")  // リンクするライブラリを指定



Conect::Conect()
{
    // WinSock2.2 初期化処理
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        // エラー処理
    }
    /*
        自力で
        エラー時はreturn 0で終了させて良し
    */

    // UDPソケットの作成
    SOCKET sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
    {
        // エラー処理
        /*
        自力で
        */
    }

}

Conect::~Conect()
{
}

void Conect::Conecting()
{


    // sockをノンブロッキングモードに
    unsigned long cmdarg = 0x01;
    int ret = ioctlsocket(sock, FIONBIO, &cmdarg);

    if (ret == SOCKET_ERROR)
    {
        // エラー処理
         /*
        自力で
        */
        // WSAGetLastError()でWinSockがらみの直近のエラーコード取得
        int errorCode = WSAGetLastError();
        // WinSock Api Error WOULD BLOCK ...たぶんブロッキングが発生...未受信
        if (errorCode == WSAEWOULDBLOCK)
        {
            // 未受信だっただけ
        }
        else
        {
            // 受信エラー
        }
    }
    else { //受信できた

    }


    // サーバアドレスの指定
    SOCKADDR_IN serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));	// 0クリアで初期化
    serverAddr.sin_family = AF_INET;				// IPv4アドレス
    serverAddr.sin_port = htons(SERVER_PORT);			// サーバのポート番号
    //inet_pton(AF_INET, SERVER_ADDR, &serverAddr.sin_addr.s_addr);		// サーバのIPアドレス
    inet_pton_custom(SERVER_ADDRESS, &serverAddr.sin_addr.s_addr);

    // 接続要求
    if (connect(sock, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        // エラー処理
    }

    while (1)
    {
        // サイズとか色はお任せ
        PLAYER param = { 0, 0, 5,0 };
        // マウス座標取得し、circleのcenterXとcenterTに格納
        GetMousePoint(&param.x, &param.y);
        // 描画
      /*  DrawCircle(pParam.centerX, pParam.centerY, circle.size, circle.color, 1);*/

        // サーバ( serverAddr )に●の情報送信
        PLAYER value;	// 送信データの格納領域
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
            // エラー処理
             /*
            自力で
            ※バイトオーダーの変換を忘れずに！
        */
        }


        // 未送信以外のエラー
        if (ret == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
        {
            // エラー処理
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

    // stringstreamを使って、16進数の部分をパース
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

        return 1;  // 成功
    }

    return 0;  // 不正なIPv6アドレス形式
}

int Conect::inet_pton_ipv4(const char* str, uint32_t& addr)
{
    unsigned int b1, b2, b3, b4;
    char dot1, dot2, dot3;

    // stringstreamを使って、文字列を整数としてパース
    std::istringstream iss(str);
    if (iss >> b1 >> dot1 >> b2 >> dot2 >> b3 >> dot3 >> b4
        && dot1 == '.' && dot2 == '.' && dot3 == '.') {
        // 各部分が0?255の範囲内か確認
        if (b1 <= 255 && b2 <= 255 && b3 <= 255 && b4 <= 255) {
            addr = (b1 << 24) | (b2 << 16) | (b3 << 8) | b4;
            return 1;  // 成功
        }
    }
    return 0;  // 不正なIPv4アドレス形式
}



// 両方のアドレスに対応するinet_ptonの代替関数
int Conect::inet_pton_custom(const char* str, void* addr) {
    // IPv4のチェック
    if (strchr(str, '.') != nullptr) {
        return inet_pton_ipv4(str, *(uint32_t*)addr);
    }

    // IPv6のチェック
    if (strchr(str, ':') != nullptr) {
        return inet_pton_ipv6(str, (unsigned char*)addr);
    }

    return 0;  // 無効なアドレス形式
}
#endif
#if 1
#include "Conect.h"

// コンストラクタ
Conect::Conect(const std::string& serverAddress, unsigned short port)
    : m_serverAddress(serverAddress), m_serverPort(port), m_socket(INVALID_SOCKET)
{
    // WinSock2.2 初期化処理
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        throw std::runtime_error("WinSock initialization failed");
    }
}

// デストラクタ
Conect::~Conect()
{
    CleanupSocket();
    WSACleanup();
}

// ソケットの初期化
void Conect::InitializeSocket()
{
    m_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (m_socket == INVALID_SOCKET)
    {
        HandleError("Failed to create socket");
    }

    // ノンブロッキングモードに設定
    unsigned long cmdarg = 0x01;
    if (ioctlsocket(m_socket, FIONBIO, &cmdarg) == SOCKET_ERROR)
    {
        HandleError("Failed to set socket to non-blocking mode");
    }
}

// ソケットのクリーンアップ
void Conect::CleanupSocket()
{
    if (m_socket != INVALID_SOCKET)
    {
        closesocket(m_socket);
        m_socket = INVALID_SOCKET;
    }
}


// サーバに接続する
void Conect::ConnectToServer()
{
    InitializeSocket();

    // サーバアドレスの設定
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

// サーバにデータを送信する
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

// エラー処理
void Conect::HandleError(const std::string& errorMessage)
{
    int errorCode = WSAGetLastError();
    std::cerr << errorMessage << " Error Code: " << errorCode << std::endl;
    throw std::runtime_error(errorMessage);
}

// IPv6アドレスをバイト列に変換
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

// IPv4アドレスをバイト列に変換
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

// IPv4 または IPv6 アドレスの変換を選択
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