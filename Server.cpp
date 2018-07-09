//
//  Server.cpp
//  Socket_chatting
//
//  Created by  MacBook on 2018. 7. 9..
//  Copyright © 2018년  MacBook. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define  BUFF_SIZE   1024

int   main( void)
{
    int   server_socket;
    int   client_socket;
    int   client_addr_size;
    int   nSockOpt;
    
    struct sockaddr_in   server_addr;
    struct sockaddr_in   client_addr;
    
    char   buff_rcv[BUFF_SIZE+5];
    char   buff_snd[BUFF_SIZE+5];
    
    server_socket  = socket( PF_INET, SOCK_STREAM, 0); // 소켓 디스크립터
    
    if( -1 == server_socket)
    {
        printf( "서버 : server socket 생성 실패\n");
        exit( 1);
    }
    // 서버 소켓 생성
    //
    
    
    //소켓에 주소와 port를 할당하기 위하여 sockaddr_in 구조체 사용
    memset( &server_addr, 0, sizeof( server_addr));
    server_addr.sin_family     = AF_INET;               //IPv4
    server_addr.sin_port       = htons(4000);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);   //32bit IPv4 주소
    // INADDR_ANY :  시스템 마다 IP가 다르므로 IP를 고정하지 않고 어떠한 IP도 허용
    
    
    if( -1 == bind( server_socket, (struct sockaddr*)&server_addr, sizeof( server_addr) ) )
    {
        printf( "서버 : bind() 실행 에러\n");
        exit( 1);
    }
    // 서버 소켓에 필요한 정보를 할당
    //
    
    nSockOpt = 1;
    setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &nSockOpt, sizeof(nSockOpt));
    
    if( -1 == listen(server_socket, 5))
    {
        printf( "서버 : listen() 실행 실패\n");
        exit( 1);
    }
    // 접속 요청 확인
    //
    
    
    while( 1)
    {
        client_addr_size  = sizeof( client_addr);
        client_socket     = accept( server_socket, (struct sockaddr*)&client_addr, (socklen_t*)&client_addr_size);
        // accept를 통하여 클라이언트의 접속 허용, 클라이언트 소켓 생성
        
        if ( -1 == client_socket)
        {
            printf( "서버 : 클라이언트 연결 수락 실패\n");
            exit( 1);
        }
        
        read ( client_socket, buff_rcv, BUFF_SIZE);
        // 클라이언트로 부터 자료를 읽어들임
        printf( "서버 received: %s\n", buff_rcv);
        
        sprintf( buff_snd, "%zu : %s", strlen( buff_rcv), buff_rcv);   // 수신된 길이를 구하여 전송할 데이터 준비
        write( client_socket, buff_snd, strlen( buff_snd)+1);          // +1: NULL까지 포함해서 전송
        
        close( client_socket);
        // 클라이언트 소켓을 소멸시켜 통신 종료
    }
}
