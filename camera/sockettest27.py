#!/usr/bin/env python
# coding=utf-8
import socket
import thread
import os
import sys
reload(sys)
sys.setdefaultencoding('utf-8')

START = '[[[cmdstart]]]'
END = '[[[cmdend]]]'

# 开启ip和端口
ip_port = ('0.0.0.0', 9999)
# 生成一个句柄
s = socket.socket()
# 绑定ip端口
s.bind(ip_port)
# 最多连接数
s.listen(10)


#和巡检机器人通信
def SendMsg(type):
    host = '192.168.43.26'
    port = 8080
    #remote_ip = socket.gethostbyname(host)
    sclient = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sclient.connect((host , port))
    sclient.sendall(bytes(START + type + END))
    print START + type + END
    data = sclient.recv(1024)
    sclient.close()
    return str(data)

#处理网络发送过来的和巡检机器人消息
def dealMsg(data):
    #if(data.index('[[[cmdstart]]]') >0 and data.index('[[[cmdend]]]')):
    pos1 = data.index(START)
    pos2 = data.index(END)
    if(pos1 >= 0 and pos2 >=0):
        type = data[pos1 + len(START):pos2]
        #print(type)
        if(type == '10'):
            #启动巡检机器人
            os.system('ps -ef|grep camera|grep -v grep|cut -c 9-15|xargs kill -9')
	    #os.system('cd /mnt/hgfs/New_Git/fw_rtsp_camera/rtsp-camera/camera')
            os.system('./camera -u user -p user &')
            return  START + '1' + END
        else:
            #和巡检机器人通信
           return SendMsg(type)


#处理客户端连接
def clientthread(conn):
    # Sending message to connected client


    # infinite loop so that function do not terminate and thread do not end.
    while True:

        # Receiving from client
        data = conn.recv(1024)
        if not data:
            break

        conn.sendall(bytes(  dealMsg(str(data))))
    # came out of loop
    conn.close()

# 开启死循环
# Function for handling connections. This will be used to create threads
while 1:
    # wait to accept a connection - blocking call
    conn, addr = s.accept()
    # start new thread takes 1st argument as a function name to be run, second is the tuple of arguments to the function.
    thread.start_new_thread(clientthread, (conn,))

s.close()
