#include <stdio.h>
#include <string.h>
#include <WinSock2.h>

#pragma comment(lib, "ws2_32.lib")

//���ձ������������Ҽ���Ŀ����--->����--->C/C++--->SDL����Ϊ��

int main() {
	//��������Ȩ�� �̶�д��
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	//1������һ��socket�׽���
	
	//SOCKET socket(
	//		int af,	//Э���ַ�� IPV4/IPV6�ֱ��Ӧ AF_INET/AF_INET6
	//		int type,	//���� ��ʽЭ��(TCP) ֡ʽЭ��(UDP) �ֱ��Ӧ SOCK_STREAM��SOCK_DGRAM
	//		int protocol
	//	);

	SOCKET listen_socket = socket(AF_INET, SOCK_STREAM, 0);
	//printf("%d", listen_socket);	//listen_socket��һ������
	//-1����д��INVALID_SOCKET
	if (listen_socket == -1) {
		//�������ʧ�� ��ӡ������ ����--->�������--->���������10093--->��������ԭ��
		printf("create listen socket failed! errocode: %d\n", GetLastError());
		return -1;
	}

	//2�������socket��һ���˿ں�
	//struct sockaddr_in {
	//	ADDRESS_FAMILY sin_family;	//Э���ַ�� ͬSOCKET
	//	USHORT sin_port;	//�˿ں�	2�ֽ�
	//	IN_ADDR sin_addr;	//IP��ַ	4�ֽ�
	//	CHAR sin_zero[8];	//�����ֽ�
	//} SOCKADDR_IN, * PSOCKADDR_IN;
	struct sockaddr_in local = { 0 };
	local.sin_family = AF_INET;
	//hton�Ǵ�С��ת�� ����С���� �м��豸����� ���д��local.sin_port = 8080;�Ǵ��
	local.sin_port = htons(8080);
	//����� ����ѡ�ĸ����� 127.0.0.1(���ػ���) 0.0.0.0(ȫ������)
	//д��һ��
	//local.sin_addr.s_addr = htonl(INADDR_ANY);	//ȫ������
	//д������
	local.sin_addr.s_addr = inet_addr("0.0.0.0");	//�ַ���IP��ַת��������IP

	//int bind(
	//		SOCKET s,
	//		const struct sockaddr * name,
	//		int namelen
	//	);

	//local������sockaddr_in����Ҫ��������ת��
	if (bind(listen_socket, (struct sockaddr*)&local, sizeof(local)) == -1) {
		printf("create socket failed! errocode: %d\n", GetLastError());
		return -1;
	}

	//3�������socket������������
	//int listen(
	//		SOCKET s,
	//		int backlog	//��Ƶ˵ͨ����10�͹���
	//	);
	if (listen(listen_socket, 10) == -1) {
		printf("start listen failed! errocode: %d\n", GetLastError());
	}

	//4���ȴ��ͻ�������
	//�����������ȵ��пͻ������ӽ����ͽ������ӣ�Ȼ�󷵻أ���������
	//SOCKET accept(
	//		SOCKET s,
	//		struct sockaddr * addr,	//���ؿͻ���IP��ַ�Ͷ˿ں�
	//		int * addrlen	//�ṹ��С
	//	);

	while (1) {
		SOCKET client_socket = accept(listen_socket, NULL, NULL);
		if (client_socket == INVALID_SOCKET) continue;

		while (1) {
			//5����ʼͨѶ ---���к���Դ����������127.0.0.1:8080������֤��B/S��
			char buffer[1024] = { 0 };

			//int recv(
			//		SOCKET s,	//�ͻ���socket
			//		char * buf,	//���յ����ݴ浽����
			//		int len,	//���յĳ���
			//		int flags	//0
			//	);

			int ret = recv(client_socket, buffer, 1024, 0);
			if (ret <= 0) break;
			//recv(client_socket, buffer, 1024, 0);
			printf("%s\n", buffer);

			send(client_socket, buffer, strlen(buffer), 0);
		}

		//�ر�����
		closesocket(client_socket);

	}

	return 0;
}