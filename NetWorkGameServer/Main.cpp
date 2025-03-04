#if 0

#include <iostream>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <vector>
#include <bitset>
#pragma comment( lib, "ws2_32.lib" )

// ポート番号
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


	//WinSock初期化
	WSADATA	wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		//エラー処理
		std::cout << "WinSock初期化に失敗しました" << std::endl;
	}

	//ソケットの作成
	SOCKET	listenSock;
	if ((listenSock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == INVALID_SOCKET)
	{
		//エラー処理
		std::cout << "ソケットの作成に失敗しました" << std::endl;
	}

	// sockをノンブロッキングモードに
	unsigned long cmdarg = 0x01;
	ioctlsocket(listenSock, FIONBIO, &cmdarg);

	//固定アドレスの割り当て
	SOCKADDR_IN bindAddr;

	memset(&bindAddr, 0, sizeof(bindAddr));
	bindAddr.sin_family = AF_INET;
	bindAddr.sin_port = htons(SERVER_PORT);
	bindAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(listenSock, (SOCKADDR*)&bindAddr, sizeof(bindAddr)) != 0)
	{
		//エラー処理
		std::cout << "固定アドレスの割り当てに失敗しました" << std::endl;
	}

	// 送受信部のループ
	while (true)
	{
		bool isNewPlayer = true;
		int ret;

		PLAYER p;
		SOCKADDR_IN clientAddr;	// クライアントのアドレス情報格納領域

		// 受信　※クライアントのアドレス情報も取得
		int fromlen = sizeof(clientAddr);

		ret = recvfrom(listenSock, (char*)&p, sizeof(p), 0, nullptr, nullptr);

		// 受信時
		if (ret > 0)
		{
			std::cout << "受信します" << std::endl;

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
			//		if (p.playerID == playerList[i].playerID)//I同じIDがすでにあるなら最初から
			//		{
			//			i = 0;
			//			continue;
			//		}
			//	}
			//	playerList.push_back(p);
			//}

			////データ出力
			//for (int i = 0; i < playerList.size(); i++)
			//{
			//	////std::bitset<8> bitVal(playerList[i].state);
			//	//std::cout << "ID : " << playerList[i].playerID << std::endl;
			//	//std::cout << "Pos : " << playerList[i].x << "," << playerList[i].y << std::endl;
			//	//std::cout << "State : " << playerList[i].state << std::endl;

			//}
		}
		// 受信エラー	未受信時はWSAEWOULDBLOCKが発生
		else if (WSAGetLastError() != WSAEWOULDBLOCK)
		{
			// 受信失敗のエラー処理
			return 0;
		}

		ret = sendto(listenSock, (char*)&p, sizeof(p), 0, (SOCKADDR*)&clientAddr, sizeof(clientAddr));
		// 未送信以外のエラー
		//if (ret == SOCKET_ERROR && WSAGetLastError() != WSAEWOULDBLOCK)
		//{
		//	break;
		//}
	}
	//ソケットの破棄
	if (closesocket(listenSock) == SOCKET_ERROR)
	{
		//エラー処理
		std::cout << "ソケットの破棄に失敗しました" << std::endl;
	}
	// WinSock終了処理
	if (WSACleanup() != 0)
	{
		// エラー処理
		std::cout << "WinSock終了処理に失敗しました" << std::endl;
	}

	return 0;
}

#endif

#if 0
#include <iostream>
#include <cstring>
#include <string>
#include <DxLib.h>
#include <vector>

const unsigned short SERVER_PORT = 10654;
char data[1024];

struct PLAYER
{
	bool job;//0:Hunter,1:Runner
	int x, y;//x:４桁,y:３桁
	int state;
	int playerID;//４桁
	//   job  x    y   state  ID
	//例：0  0344 652    1   1234
};

std::vector<PLAYER> playerList;

int MakePlayerID();
void SetData(PLAYER _pData);

int main()
{
	std::cout << "サーバー" << std::endl;

	//ソケット作成
	int sock;
	sock = MakeUDPSocket(SERVER_PORT);

	// パケット受信
	while (ProcessMessage() == 0)
	{
		
		IPDATA playerIP = {};//送信側のIPアドレス
		int playerPort = 0;

		// データを受信
		int ret = NetWorkRecvUDP(sock, &playerIP, &playerPort, data, sizeof(data), FALSE);
		if (ret > 0)
		{
			std::cout << "受信します" << std::endl;

			PLAYER p = {};//受信したプレイヤーの情報を入れる

			// job: 1バイト目（00 → Hunter、01 → Runner）
			p.job = (data[0] == '0' && data[1] == '0') ? 0 : 1;

			// x: 2-5バイト目（1000） => data[1]からdata[4]
			p.x = std::stoi(std::string(data + 1, 4));

			// y: 6-8バイト目（200） => data[5]からdata[7]
			p.y = std::stoi(std::string(data + 5, 3));

			// state: 9バイト目（3）
			p.state = std::stoi(std::string(data + 8, 1));

			// playerID: 10-13バイト目（1234）
			p.playerID = std::stoi(std::string(data + 9, 4));

			// 結果を表示
			std::cout << "job: " << p.job << ", x: " << p.x << ", y: " << p.y
				<< ", state: " << p.state << ", playerID: " << p.playerID << std::endl;
			//std::memcpy(&p,data, sizeof(PLAYER));


			if (p.playerID == 0)
			{
				//p.playerID = MakePlayerID();
				p.playerID = MakePlayerID();
				if (playerList.size() == 0)
				{
					playerList.push_back(p);//Listに追加する
				}
			}
			for (int i = 0; i < playerList.size(); i++)
			{
				if (p.playerID == playerList[i].playerID)
				{
					break;
				}
				if (i == playerList.size() - 1)//最後まで見て同じIDがなければ
				{
					playerList.push_back(p);//Listに追加する
				}
			}

			SetData(p);


			//送信する部分
			for (int i = 0; i < playerList.size() - 1; i++)
			{
				int sendResult = NetWorkSendUDP(sock, playerIP, playerPort, data, sizeof(data));

				if (sendResult > 0)
				{
					std::cout << "ID : " << playerList[i].playerID << "に送信します" << std::endl;
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
		if (ID == playerList[i].playerID)//同じIDがすでにあるなら最初から
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
	std::string sendData = std::to_string(playerList.size()); // 最初にプレイヤー数を入れる
	sendData += "|";
	for (const auto& player : playerList)
	{
		snprintf(data, sizeof(data), "%1d%04d%03d%1d%04d",player.job, player.x, player.y, player.state, player.playerID);

		sendData += std::string(data, sizeof(data)) + "|"; // 各プレイヤーのデータを追加
	}
	//snprintf(data, sizeof(data), "%1d%04d%03d%1d%04d", _pData.job, _pData.x, _pData.y, _pData.state, _pData.playerID);
}

#endif

#include <iostream>
#include <cstring>
#include <string>
#include <DxLib.h>
#include <vector>

const unsigned short SERVER_PORT = 10654;
char data[1024];

struct PLAYER
{
	bool job;      // 0: Hunter, 1: Runner
	int x, y;      // x: 4 digits, y: 3 digits
	int state;
	int playerID;  // 4 digits
};

std::vector<PLAYER> playerList;
std::vector<IPDATA> clientIPs;
std::vector<int> clientPorts;

const int MAX_PLAYERS = 2;

int MakePlayerID();
void SetData(PLAYER _pData);

int main()
{
	std::cout << "サーバー" << std::endl;

	// Create socket
	int sock;
	sock = MakeUDPSocket(SERVER_PORT);

	// Main loop to handle incoming data
	while (ProcessMessage() == 0)
	{
		IPDATA playerIP = {}; // Player's IP address
		int playerPort = 0;

		// Receive data
		int ret = NetWorkRecvUDP(sock, &playerIP, &playerPort, data, sizeof(data), FALSE);
		if (ret > 0)
		{
			std::cout << "Received data" << std::endl;

			PLAYER p = {}; // Store the received player data

			// Decode the received data into the PLAYER structure
			p.job = (data[0] == '0' && data[1] == '0') ? 0 : 1;
			p.x = std::stoi(std::string(data + 1, 4));
			p.y = std::stoi(std::string(data + 5, 3));
			p.state = std::stoi(std::string(data + 8, 1));
			p.playerID = std::stoi(std::string(data + 9, 4));

			// Display the player data
			std::cout << "job: " << p.job << ", x: " << p.x << ", y: " << p.y
				<< ", state: " << p.state << ", playerID: " << p.playerID << std::endl;

			if (p.playerID == 0)
			{
				p.playerID = MakePlayerID();
			}

			bool playerExists = false;
			for (size_t i = 0; i < playerList.size(); ++i)
			{
				if (p.playerID == playerList[i].playerID)
				{
					playerExists = true;
					break;
				}
			}

			if (!playerExists)
			{
				playerList.push_back(p);
				clientIPs.push_back(playerIP);
				clientPorts.push_back(playerPort);
			}

			// Set the data to send to clients
			SetData(p);

			// Send data to all connected clients
			for (size_t i = 0; i < playerList.size(); ++i)
			{
				int sendResult = NetWorkSendUDP(sock, clientIPs[i], clientPorts[i], data, sizeof(data));

				if (sendResult > 0)
				{
					std::cout << "Sent data to client with ID: " << playerList[i].playerID << std::endl;
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
		if (ID == playerList[i].playerID)
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
	std::string sendData = std::to_string(playerList.size()); // Start with the player count
	sendData += "|";

	for (const auto& player : playerList)
	{
		snprintf(data, sizeof(data), "%1d%04d%03d%1d%04d", player.job, player.x, player.y, player.state, player.playerID);
		sendData += std::string(data, sizeof(data)) + "|"; // Append each player's data
	}
}