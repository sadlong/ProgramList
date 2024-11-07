#include <stdio.h>
#include <string.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

//风险报错解决方法：右键项目名称--->属性--->C/C++--->SDL检查改为否

int main() {
	//开启网络权限 固定写法
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//1、创建一个socket套接字
	
	//SOCKET socket(
	//		int af,	//协议地址簇 IPV4/IPV6分别对应 AF_INET/AF_INET6
	//		int type,	//类型 流式协议(TCP) 帧式协议(UDP) 分别对应 SOCK_STREAM和SOCK_DGRAM
	//		int protocol
	//	);

	SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	//printf("%d", listen_socket);	//listen_socket是一个整型
	//-1可以写成INVALID_SOCKET
	if (listen_socket == -1) {
		//如果创建失败 打印错误码 工具--->错误查找--->输入错误码10093--->给出错误原因
		printf("create listen socket failed! errocode: %d\n", GetLastError());
		return -1;
	}

	//2、给这个socket绑定一个端口号
	//struct sockaddr_in {
	//	ADDRESS_FAMILY sin_family;	//协议地址簇 同SOCKET
	//	USHORT sin_port;	//端口号	2字节
	//	IN_ADDR sin_addr;	//IP地址	4字节
	//	CHAR sin_zero[8];	//保留字节
	//} SOCKADDR_IN, * PSOCKADDR_IN;
	struct sockaddr_in local = { 0 };
	local.sin_family = AF_INET;
	//hton是大小端转化 本地小端序 中间设备大端序 如果写成local.sin_port = 8080;是错的
	local.sin_port = htons(8080);
	//服务端 理解成选哪个网卡 127.0.0.1(本地环回) 0.0.0.0(全部接收)
	//写法一：
	//local.sin_addr.s_addr = htonl(INADDR_ANY);	//全部接收
	//写法二：
	local.sin_addr.s_addr = inet_addr("0.0.0.0");	//字符串IP地址转换成整数IP

	//int bind(
	//		SOCKET s,
	//		const struct sockaddr * name,
	//		int namelen
	//	);

	//local类型是sockaddr_in，需要进行类型转换
	if (bind(listen_socket, (struct sockaddr*)&local, sizeof(local)) == -1) {
		printf("create socket failed! errocode: %d\n", GetLastError());
		return -1;
	}

	//3、给这个socket开启监听属性
	//int listen(
	//		SOCKET s,
	//		int backlog	//视频说通常填10就够了
	//	);
	if (listen(listen_socket, 10) == -1) {
		printf("start listen failed! errocode: %d\n", GetLastError());
	}

	//4、等待客户端连接
	//阻塞函数，等到有客户端连接进来就接收连接，然后返回，否则阻塞
	//SOCKET accept(
	//		SOCKET s,
	//		struct sockaddr * addr,	//返回客户端IP地址和端口号
	//		int * addrlen	//结构大小
	//	);

	while (1) {
		SOCKET client_socket = accept(listen_socket, NULL, NULL);
		if (client_socket == INVALID_SOCKET) continue;

		while (1) {
			//5、开始通讯 ---运行后可以打开浏览器输入127.0.0.1:8080进行验证（B/S）
			char buffer[1024] = { 0 };

			//int recv(
			//		SOCKET s,	//客户端socket
			//		char * buf,	//接收的数据存到哪里
			//		int len,	//接收的长度
			//		int flags	//0
			//	);

			int ret = recv(client_socket, buffer, 1024, 0);
			if (ret <= 0) break;
			//recv(client_socket, buffer, 1024, 0);
			printf("%s\n", buffer);

			send(client_socket, buffer, strlen(buffer), 0);
		}

		//关闭连接
		closesocket(client_socket);

	}

	return 0;
}