#include <stdio.h>
#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//1、创建socket套接字
	SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (client_socket == INVALID_SOCKET) {
		printf("create socket failed!\n");
		return -1;
	}

	//2、连接服务器
	struct sockaddr_in target;
	target.sin_family = AF_INET;
	target.sin_port = htons(8080);
	target.sin_addr.s_addr = inet_addr("127.0.0.1");

	if (connect(client_socket, (struct sockaddr*)&target, sizeof(target)) == -1) {
		printf("connect server failed!\n");
		closesocket(client_socket);
		return -1;
	}

	//3、开始通讯 send recv
	//回写服务器
	while (1) {
		//发送
		char sbuffer[1024] = { 0 };
		printf("please enter: ");
		scanf("%s", sbuffer);
		send(client_socket, sbuffer, strlen(sbuffer), 0);

		//接收
		char rbuffer[1024] = { 0 };
		int ret = recv(client_socket, rbuffer, 1024, 0);
		if (ret <= 0) break;
		printf("%s\n", rbuffer);
	}
	
	//关闭连接
	closesocket(client_socket);

	return 0;
}