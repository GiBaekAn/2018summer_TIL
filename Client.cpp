//
//  Client.cpp
//  Socket_chatting
//
//  Created by  MacBook on 2018. 7. 9..
//  Copyright © 2018년  MacBook. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define  BUFF_SIZE   1024

int   main( int argc, char **argv)
{
    int   client_socket;
    int pnum;
    char addr[20];
    
    struct sockaddr_in   server_addr;
    
    char   buff[BUFF_SIZE+5];
    
    client_socket  = socket( PF_INET, SOCK_STREAM, 0);
    if( -1 == client_socket)
    {
        printf( "클라이언트 : socket 생성 실패\n");
        exit( 1);
    }
    // 클라이언트 소켓 생성
    //
    
    printf("클라이언트 : 포트 번호를 입력해주세요\n");
    scanf("%d",&pnum);
    printf("클라이언트 : IP 주소를 입력해주세요 (self : 127.0.0.1)\n");
    scanf("%s",addr);
    
    memset( &server_addr, 0, sizeof( server_addr));
    server_addr.sin_family     = AF_INET;
    server_addr.sin_port       = htons( pnum);
    server_addr.sin_addr.s_addr= inet_addr( addr);
    // 만들어진 소켓에 정보 할당
    
    if( -1 == connect( client_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
    {
        printf( "클라이언트 : 접속 실패\n");
        exit( 1);
    }
    // 서버로의 접속을 시도
    
    write( client_socket, argv[1], strlen( argv[1])+1);      // +1: NULL까지 포함해서 전송
    // 접속에 성공할 경우 데이터 전송
    
    read ( client_socket, buff, BUFF_SIZE);
    // 자료 수신 및 출력
    printf( "클라이언트 : %s\n", buff);
    
    
    close( client_socket);
    return 0;
}
