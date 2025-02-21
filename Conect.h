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
    // サーバのIPアドレス
    const char* SERVER_ADDRESS = "192.168.43.1";		// 接続先なんか適当にクラスメートとやって！
    // サーバのポート番号
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

// PLAYER構造体（プレイヤーの座標や状態を格納）
struct PLAYER
{
    int x;
    int y;
    int state;
    int playerID;
};

// ネットワーク接続クラス
class Conect
{
public:
    // コンストラクタとデストラクタ
    Conect();
    ~Conect();
    bool ConnectToServer();  // 接続処理を行い、成功したら true を返す
    void ReceiveData();      // サーバからのデータを受信する
    void SendData(const PLAYER& player);  // プレイヤーのデータを送信する

private:
    // サーバのIPアドレスとポート番号
    std::string m_serverAddress;
    unsigned short m_serverPort;

    // ソケット
    int m_socket;

    // 接続処理（内部で使用）
    void InitializeSocket();
    void CleanupSocket();

    // エラー処理
    void HandleError(const std::string& errorMessage);

    // アドレス変換処理（IPv4/IPv6）
    int inet_pton_ipv6(const char* str, unsigned char* addr);
    int inet_pton_ipv4(const char* str, uint32_t& addr);
    int inet_pton_custom(const char* str, void* addr);
};
