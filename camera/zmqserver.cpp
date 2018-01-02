#include "zmqserver.h"
#include <zmq.h>

zmqServer::zmqServer()
{

}

zmqServer::~zmqServer()
{

}

void zmqServer::run(){
    void * pCtx = NULL;
    void * pSock = NULL;
    const char * pAddr = "tcp://*:7766";
    //创建context，zmq的socket 需要在context上进行创建
    if((pCtx = zmq_ctx_new()) == NULL)
    {
        return;
    }
         //创建zmq socket ，socket目前有6中属性 ，这里使用dealer方式
         //具体使用方式请参考zmq官方文档（zmq手册）
    if((pSock = zmq_socket(pCtx, ZMQ_DEALER)) == NULL)
    {
       zmq_ctx_destroy(pCtx);
       return;
    }
    int iRcvTimeout = 5000;// millsecond
    //设置zmq的接收超时时间为5秒
    if(zmq_setsockopt(pSock, ZMQ_RCVTIMEO, &iRcvTimeout, sizeof(iRcvTimeout)) < 0)
    {
       zmq_close(pSock);
       zmq_ctx_destroy(pCtx);
       return;
    }
    //绑定地址 tcp://*:7766
    //也就是使用tcp协议进行通信，使用网络端口 7766
    if(zmq_bind(pSock, pAddr) < 0)
    {
        zmq_close(pSock);
        zmq_ctx_destroy(pCtx);
        return;
    }
    printf("bind at : %s\n", pAddr);
    int len = 0;
    char szMsg[1024] = {0};
    int i = 0;
    while(1)
    {
        errno = 0;
        //循环等待接收到来的消息，当超过5秒没有接到消息时，
        //zmq_recv函数返回错误信息 ，并使用zmq_strerror函数进行错误定位
        len = zmq_recv(pSock, szMsg, sizeof(szMsg), 0);
        if(len < 0)
        {
             continue;
        }
        printf("received message :\n");
        for(i=0;i<len;i++){
            printf("%2X ", szMsg[i]);
        }
        printf("\n");
    }

    return;
}
