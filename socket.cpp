//#include "Socket.h"
//#include <WinSock2.h>
//#include <WS2tcpip.h>
//#pragma comment( lib, "ws2_32.lib" )
//
//// ポート番号
//const unsigned short SERVER_PORT = 8888;
//// 送受信するメッセージの最大値
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
//	//ソケットの破棄
//	closesocket(sock);
//	// WinSock終了処理
//	WSACleanup();
//}
//
//void Socket::sockmain()
//{
//	int ret;
//	char buff[MESSAGE_LENGTH];	// 送受信文字列の格納領域
//	SOCKADDR_IN serverAddr;	// サーバのアドレス情報格納領域
//	// サーバの宛先情報セット
//
//
//	/*std::sprintf(buff, "%d", transform_.position_.x);*/
//
//
//	// 送信　※受信時に取得したクライアントのアドレスに送信
//	memset(&serverAddr, 0, sizeof(serverAddr));
//	serverAddr.sin_family = AF_INET;				// IPv4アドレス
//	serverAddr.sin_port = htons(SERVER_PORT);			// サーバのポート番号
//	inet_pton(AF_INET, "192.168.43.1", &serverAddr.sin_addr.s_addr);		// サーバのIPアドレス
//	ret = sendto(sock, buff, strlen(buff), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
//	if (ret != strlen(buff))
//	{
//		//std::cout << "エラー" << std::endl;
//		// エラー処理
//	}
//	else
//	{
//		//buff = '\0';
//		//std::cout << "送信成功" << std::endl;
//	}
//}
