#include "zmqclient.h"
#include <zmq.h>

zmqClient::zmqClient()
{
    //使用tcp协议进行通信，需要连接的目标机器IP地址为192.168.1.2
   //通信使用的网络端口 为7766

    this->Xl = -1;
    this->Yl = -1;
    this->Zl = -1;
    this->Al = -1;
    this->Bl = -1;
    this->Cl = -1;

    this->Xx1 = -1;
    this->Xx2 = -1;
    this->Yx1 = -1;
    this->Yx2 = -1;
    this->Zx1 = -1;
    this->Zx2 = -1;
    this->Ax1 = -1;
    this->Ax2 = -1;
    this->Bx1 = -1;
    this->Bx2 = -1;
    this->Cx1 = -1;
    this->Cx2 = -1;

    this->Xs = -1;
    this->Ys = -1;
    this->Zs = -1;
    this->As = -1;
    this->Bs = -1;
    this->Cs = -1;

    //this->inits = -1;
    this->isCarNumChange = 0;

    //创建context
    if((pCtx = zmq_ctx_new()) == NULL)
    {
        return;
    }
    //创建socket
    if((pSock = zmq_socket(pCtx, ZMQ_DEALER)) == NULL)
    {
        zmq_ctx_destroy(pCtx);
        return;
    }
    int iSndTimeout = 5000;// millsecond
    //设置接收超时
    if(zmq_setsockopt(pSock, ZMQ_RCVTIMEO, &iSndTimeout, sizeof(iSndTimeout)) < 0)
    {
        zmq_close(pSock);
        zmq_ctx_destroy(pCtx);
        return;
    }
}

zmqClient::~zmqClient()
{

}
void zmqClient::disconnect()
{
    zmq_close(pSock);
    zmq_ctx_destroy(pCtx);
}

int zmqClient::ConnectServer(const char *pAddr,int CarNumber)
{
    //const char * pAddr = "tcp://127.0.0.1:7766";

     printf(" ConnectServer : %s\n", pAddr);

    //连接目标IP192.168.1.2，端口7766
    if(zmq_connect(pSock, pAddr) < 0)
    {
        printf("error connect \n");
        this->Car_Number = CarNumber;
        zmq_close(pSock);
        return 0;
    }else{
        printf("connect ok \n");
        return 1;
    }
}

void zmqClient::sendText(char *str,const int len)
{
    int a = zmq_send(this->pSock, str, len, 0);
    int i = 0;

    printf("send %d message : \n",a);
    for(i=0;i<len;i++){
        printf("%2X ", str[i]);
    }
    printf("\n");

    if(a < 0)
    {
       printf( "send message faild\n");
    }

    printf( "send message OK  %d\n",a);
}

int strGcmp(char *str1,char *str2,int len)
{
    int i = 0;
    for(i=0;i<len;i++)
    {
        if(str1[i] != str2[i]){
            return 1;
        }
    }
    return 0;
}

void zmqClient::run(){

    recvData_t abc;
    sendData_t abd;
    short acTmp = 0;

    int len = 0,i = 0;
    char stateA = 0;
    //qDebug()<<"hello from worker thread " << thread()->currentThreadId();
    char szMsg[1024] = {0};
    char szTmp[40] = {0},szTmp1[40] = {0};

    while(1)
    {
//        if(this->inits == -1){

//            abd.a1 = 2;
//            abd.a2 = 16;
//            abd.a3 = 0;
//            abd.a4 = 0;
//            abd.a6 = 0;
//            abd.a7 = 0;
//            abd.a5 = 0;
//            abd.a8 = 0;
//            abd.a9 = 0;
//            abd.a10 = 0;

//            this->sendText((char *)(&abc),16);

//            this->inits = 1;
//            this->StaticBu = 0;
//        }
        //printf("waitting...\n");
        if(this->pSock)
          errno = 0;
        //循环等待接收到来的消息，当超过5秒没有接到消息时，
        //zmq_recv函数返回错误信息 ，并使用zmq_strerror函数进行错误定位

        len = zmq_recv(this->pSock, szMsg, sizeof(szMsg), 0);

        if(len < 0)
        {
            //printf("error = %s\n", zmq_strerror(errno));
            continue;
        }

        if((len == 38)&&(szMsg[0] == 1)){

            if(strGcmp(szMsg,szTmp,38) == 0){
                continue;
            }else{
                memcpy(szTmp,szMsg,38);
            }

            memcpy((char *)&abc,szMsg,38);

//            for(i=0;i<len;i++){
//                printf("%2X ", szMsg[i]);
//            }
//            printf("\n");

            if(this->Al != abc.Az.office){
               this->Al = abc.Az.office;
                //printf("A zhou %d\n",this->Al);
            }
            if(this->Bl != abc.Bz.office){
                this->Bl = abc.Bz.office;
                //printf("B zhou %d \n",this->Bl);
            }
            if(this->Cl != abc.Cz.office){
                this->Cl = abc.Cz.office;
                //printf("C zhou %d \n",this->Cl);
            }
            if(this->Xl != abc.Xz.office){
                this->Xl = abc.Xz.office;
                //printf("X zhou %d \n",this->Xl);
            }
            if(this->Yl != abc.Yz.office){
                this->Yl = abc.Yz.office;
                //printf("Y zhou %d \n",this->Yl);
            }
            if(this->Zl != abc.Zz.office){
                this->Zl = abc.Zz.office;
                //printf("Z zhou %d \n",this->Zl);
            }
            acTmp = abc.active.office;
            for(i = 1;i < 16;i++){
                switch(i){
                case 1:
                    printf("X1 %d ",acTmp%2);
                    if(this->Xx1 != acTmp%2){
                       this->Xx1 = acTmp%2;
                    }
                    break;
                case 2:
                    printf("X2 %d ",acTmp%2);
                    if(this->Xx2 != acTmp%2){
                        this->Xx2 = acTmp%2;
                    }
                    break;
                case 3:
                    printf("Y1 %d ",acTmp%2);
                    if(this->Yx1 != acTmp%2){
                      this->Yx1 = acTmp%2;
                    }
                    break;
                case 4:
                    printf("Y2 %d ",acTmp%2);
                    if(this->Yx2 != acTmp%2){
                        this->Yx2 = acTmp%2;
                    }
                    break;
                case 5:
                    printf("Z1 %d ",acTmp%2);
                    if(this->Zx1 != acTmp%2){
                        this->Zx1 = acTmp%2;
                    }
                    break;
                case 6:
                    printf("Z2 %d ",acTmp%2);
                    if(this->Zx2 != acTmp%2){
                        this->Zx2 = acTmp%2;
                    }
                    break;
                case 7:
                    printf("A1 %d ",acTmp%2);
                    if(this->Ax1 != acTmp%2){
                        this->Ax1 = acTmp%2;
                    }
                    break;
                case 8:
                    printf("A2 %d ",acTmp%2);
                    if(this->Ax2 != acTmp%2){
                        this->Ax2 = acTmp%2;
                    }
                    break;
                case 9:
                    printf("B1 %d ",acTmp%2);
                    if(this->Bx1 != acTmp%2){
                        this->Bx1 = acTmp%2;
                    }

                    break;
                case 10:
                    printf("B2 %d ",acTmp%2);
                    if(this->Bx2 != acTmp%2){
                        this->Bx2 = acTmp%2;
                    }
                    break;
                case 11:
                    printf("C1 %d ",acTmp%2);
                    if(this->Cx1 != acTmp%2){
                        this->Cx1 = acTmp%2;
                    }
                    break;
                case 12:
                    printf("C2 %d ",acTmp%2);
                    if(this->Cx2 != acTmp%2){
                        this->Cx2 = acTmp%2;
                    }
                    break;
                }

                acTmp = acTmp>>1;
            }
            printf("\n");

//            stateA = abc.state;
//            for(i = 1;i < 8;i++){
//                switch(i){
//                case 1:
//                    printf("X %d ",stateA%2);
//                    this->Xs = stateA%2;
//                    break;
//                case 2:
//                    printf("y %d ",stateA%2);
//                    this->Ys = stateA%2;
//                    break;
//                case 3:
//                    printf("Z %d ",stateA%2);
//                    this->Zs = stateA%2;
//                    break;
//                case 4:
//                    printf("A %d ",stateA%2);
//                    this->As = stateA%2;
//                    break;
//                case 5:
//                    printf("B %d ",stateA%2);
//                    this->Bs = stateA%2;
//                    break;
//                case 6:
//                    printf("C %d ",stateA%2);
//                    this->Cs = stateA%2;
//                    break;
//                }

//                stateA = stateA>>1;
//            }
//            printf("\n");
            printf("RFID %X \n",abc.RFID.office);
            if(abc.RFID.office != this->CarDNum){
                printf("Chnage RFID  %X \n",abc.RFID.office);
                this->CarDNum = abc.RFID.office;
                this->isCarNumChange = 1;
            }

            //printf("CS %d %d %d %d %d %d %d %d\n",abc.CS1.office,abc.CS2.office,abc.CS3.office,abc.CS4.office,abc.CS5.office,abc.CS6.office,abc.CS7.office,abc.CS8.office);

        }

        if((len == 37)&&(szMsg[0] == 1)){

            if(strGcmp(szMsg,szTmp1,37) == 0){
                continue;
            }else{
                memcpy(szTmp1,szMsg,37);
            }

            memcpy(&abc,szMsg,37);

            for(i=0;i<len;i++){
                printf("%2X ", szMsg[i]);
            }
            printf("\n");
        }

        msleep(10);
    }
}
