#ifndef CZSOCKCLIENT_H
#define CZSOCKCLIENT_H
#define WIN32_LEAN_AND_MEAN
#include <thread>
#include <memory.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h> // after winsock2.h 
#include <iostream>
#include "Basics.h"
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")  
#pragma comment (lib, "AdvApi32.lib")  
#define  BUF_LEN 512
namespace cz{
	namespace czsocket{
		class CZClient :public Object{
		private:
			char serverAddress[BUF_LEN];
			char sendBuf[BUF_LEN];
			char recvBuf[BUF_LEN];
			char serverPort[BUF_LEN];
			WSADATA wsaData;
			struct addrinfo *result = NULL, *ptr = NULL, hints;
			SOCKET ConnectSocket = INVALID_SOCKET;
			std::thread mReceiveThread;
		public:
			CZClient(const char* _serverAddress, const char* _serverPort){
				memcpy(serverAddress, _serverAddress, strlen(_serverAddress));
				memcpy(serverPort, _serverPort, strlen(_serverPort));
				//initialize
				if (WSAStartup(MAKEWORD(2, 2), &wsaData)){
					std::cerr << "client WSAStartup failed\n";
					return;
				}
				ZeroMemory(&hints, sizeof(hints));
				hints.ai_family = AF_UNSPEC;
				hints.ai_socktype = SOCK_STREAM;
				hints.ai_protocol = IPPROTO_TCP;

				// resolve the server address and port
				std::cout << serverPort << " " << serverAddress << std::endl;
				int iResult = getaddrinfo(serverAddress, serverPort, &hints, &result);
				if (iResult != 0){
					std::cerr << "client get addrinfo fail\n";
					WSACleanup();
					return;
				}
				for (ptr = result; ptr != NULL; ptr = ptr->ai_next){
					// create a socket for client  
					ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
					if (ConnectSocket == INVALID_SOCKET){
						std::cerr << "client socket failed with error\n";
						WSACleanup();
						return;
					}

					// connect to server  
					iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
					if (iResult == SOCKET_ERROR){
						closesocket(ConnectSocket);
						ConnectSocket = INVALID_SOCKET;// if fail try next address returned by getaddrinfo  
						continue;
					}
					break;
				}
				freeaddrinfo(result);
				if (ConnectSocket == INVALID_SOCKET)
				{
					printf("client unable to connect to server\n");
					WSACleanup();
					return;
				}
				//detach a Receive Thread
				std::thread t1(&CZClient::Receive,this);
				mReceiveThread = std::move(t1);
				mReceiveThread.detach();
			}

			void Send(const std::string& msg){
				std::thread t(&CZClient::SendImpl, this, msg);
				t.detach();
				//std::cout << "send " + msg <<" " << num << std::endl;
			}

			void ShutDown(){
				closesocket(ConnectSocket);
				WSACleanup();
			}

			bool isConnected(){
				int num = recv(ConnectSocket, recvBuf, BUF_LEN, 0);
				return num == -1;
			}

			std::string getRemoteAddress(){
				SOCKADDR_IN addr_conn;
				int nSize = sizeof(addr_conn);
				ZeroMemory(&addr_conn, sizeof(addr_conn));
				getpeername(ConnectSocket, (SOCKADDR*)&addr_conn, &nSize);
				char szPeername[16];
				ZeroMemory(szPeername, sizeof(szPeername));
				strcpy_s(szPeername, inet_ntoa(addr_conn.sin_addr));
				return std::string(szPeername);
			}
		private:
			void SendImpl(const std::string& msg){
				int num = send(ConnectSocket, msg.c_str(), msg.length() + 1, 0);
			}
			void Receive(){
				int num = 0;
				while (true){
					num = recv(ConnectSocket, recvBuf, BUF_LEN, 0);
					if (num == -1){
						printf("client receive error\n");
						ShutDown();
						return;
					}
					recvBuf[num] = '\0';
					std::string temp(recvBuf);
					std::cout <<recvBuf;
				}
			}
		};
	}
}
#endif