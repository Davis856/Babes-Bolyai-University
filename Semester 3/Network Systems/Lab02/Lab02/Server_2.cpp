// ServerSuma-Iterativ.cpp : Defines the entry point for the console application.

//



#define _WINSOCK_DEPRECATED_NO_WARNINGS 1

// exists on all platforms

#include <stdio.h>



// this section will only be compiled on NON Windows platforms

#ifndef _WIN32

#include <sys/types.h>

#include <sys/socket.h>

#include <netinet/in.h>

#include <netinet/ip.h>

#include <string.h>

#include <arpa/inet.h>





#include <unistd.h>

#include <errno.h>



#define closesocket close

typedef int SOCKET;

#else

// on Windows include and link these things

#include<WinSock2.h>

// for uint16_t an so

#include<cstdint>

#include <iostream>


// this is how we can link a library directly from the source code with the VC++ compiler � otherwise got o project settings and link to it explicitly

#pragma comment(lib,"Ws2_32.lib")

#endif



int main() {

    SOCKET s;

    struct sockaddr_in server, client;

    int c, l, err;



    // initialize the Windows Sockets LIbrary only when compiled on Windows

#ifdef _WIN32

    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) < 0) {

        printf("Error initializing the Windows Sockets LIbrary");

        return -1;

    }

#endif

    s = socket(AF_INET, SOCK_STREAM, 0);

    if (s < 0) {

        printf("Eroare la crearea socketului server\n");

        return 1;

    }



    memset(&server, 0, sizeof(server));

    server.sin_port = htons(1234);

    server.sin_family = AF_INET;

    server.sin_addr.s_addr = INADDR_ANY;



    if (bind(s, (struct sockaddr*)&server, sizeof(server)) < 0) {

        perror("Bind error:");

        return 1;

    }



    listen(s, 5);

    l = sizeof(client);

    memset(&client, 0, sizeof(client));



    while (1) {

        char chr[20];
        uint16_t counter = 0;

        printf("Listening for incomming connections\n");

        c = accept(s, (struct sockaddr*)&client, &l);

        err = errno;

#ifdef _WIN32

        err = WSAGetLastError();

#endif

        if (c < 0) {

            printf("accept error: %d", err);

            continue;

        }

        printf("Incomming connected client from: %s:%d", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        // serving the connected client

        int res = 0;
        
        res = recv(c, chr, strlen(chr)+1, 0);

        for (int i = 0; i < strlen(chr) + 1; i++)
        {
            if (chr[i] == ' ')
                counter++;
        }

        counter = htons(counter);

        res = send(c, (char*)&counter, sizeof(counter), 0);

        if (res != sizeof(counter)) printf("Error sending result\n");

        //on Linux closesocket does not exist but was defined above as a define to close

        closesocket(c);

    }



    // never reached

    // Release the Windows Sockets Library

#ifdef _WIN32

    WSACleanup();

#endif

}
