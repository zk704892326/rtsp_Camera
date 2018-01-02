#!/usr/bin/env python
# -*- coding:utf-8 -*-

import threading
import socket
import select
import sys
import time
import binascii
import traceback
import struct
import re
import datetime

class R():
    logFile = None
    @staticmethod
    def log(*msg):
        a0 = (str(datetime.datetime.now()),) + msg
        print a0
        if R.logFile:
            R.logFile.write(str(a0) + "\r\n")
            R.logFile.flush()
    @staticmethod        
    def debug(*msg):
        R.log(*msg)
        
class TcpUdpServer(threading.Thread):
    def __init__(self, **kwargs):
        threading.Thread.__init__(self)
        self.addr = kwargs.get('addr', ("0.0.0.0", 10086))
        self.timeout = kwargs.get('timeout', 5)
        self.tcpsocket = None
        self.udpsocket = None
        self.tcpclient = None
        self.udpclient = None
        self.tcpclients = []
        self.tcpclients_addr = {}
        self.udpclients = []
        self.running = True
        
    def run(self):
        while self.running:
            self.tcpconnect()
            self.udpconnect()
            self.handler()
        
    def handler(self):
        inputs = self.tcpclients + [self.tcpsocket, self.udpsocket]
        readable, writable, exceptional = select.select(inputs, [], [], self.timeout)
        if not readable:
            #R.debug("select time out ", self.addr)
            pass
        for s in readable:
            if s is self.tcpsocket:
                sock, addr = s.accept()
                sock.settimeout(self.timeout)
                R.debug("tcp accept ", addr)
                self.tcpclients.append(sock)
                self.tcpclients_addr[sock] = addr
                break
            if s is self.udpsocket:
                data, addr = s.recvfrom(1024)
                self.udpclient = addr
                R.debug("udp receive ", addr, binascii.hexlify(data))
            else:
                data = ""
                try:
                    data = s.recv(1024)
                except Exception, e:
                    R.debug(e)
                    addr = self.tcpclients_addr[s]
                    R.debug("tcp disconnect from ", addr)
                    del self.tcpclients_addr[s]
                    self.tcpclients.remove(s)
                    s.close()
                    break
                if len(data) <= 0:
                    addr = self.tcpclients_addr[s]
                    R.debug("tcp disconnect from ", addr)
                    del self.tcpclients_addr[s]
                    self.tcpclients.remove(s)
                    s.close()
                    break
                self.tcpclient = s
                addr = self.tcpclients_addr[s]
                R.debug("tcp receive ", addr, binascii.hexlify(data))
                #s.send(data[0:27])
                motor = False
                if len(data) >= 31:
                    data = data[0:31]
                    motor = True
                if motor:
                    data = struct.unpack(">4sB" + "iBB" * 4 + "BB", data)
                    motors = data[2:-2]
                    R.debug(data)
                    #R.debug(motors)
                    data = struct.pack(">4sB" + "iB" * 4 + "B", "EMMA", data[1], motors[0], 2, motors[3], 2, motors[6], 2, motors[9], 2, data[-2])
                    data0 = struct.unpack("B"*len(data), data)
                    sum0 = sum(data0)
                    data += struct.pack("B", sum0 & 0xFF)
                    s.send(data)

    def tcpconnect(self):
        if self.tcpsocket:
            return
        for res in socket.getaddrinfo(self.addr[0], self.addr[1], socket.AF_UNSPEC, socket.SOCK_STREAM):
            af, socktype, proto, canonname, sa = res
            server = None
            try:
                server = socket.socket(af, socktype, proto)
                server.settimeout(self.timeout)
                server.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
            except socket.error, msg:
                continue
            server.bind(sa)
            server.listen(100)
            self.tcpsocket = server
            break
        if None == self.tcpsocket:
            raise Exception("tcp server create fail")
            
        R.log("tcp server create ok", self.addr)
            
    def udpconnect(self):
        if self.udpsocket:
            return
            
        for res in socket.getaddrinfo(self.addr[0], self.addr[1], socket.AF_UNSPEC, socket.SOCK_DGRAM):
            af, socktype, proto, canonname, sa = res
            server = None
            try:
                server = socket.socket(af, socktype, proto)
                server.settimeout(self.timeout)
                server.setsockopt(socket.SOL_SOCKET,socket.SO_REUSEADDR,1)
            except socket.error, msg:
                continue
            server.bind(sa)
            self.udpsocket = server
            break
        if None == self.udpsocket:
            raise Exception("udp server create fail")
        R.log("udp server create ok", self.addr)
        
if __name__ == "__main__":
    server = TcpUdpServer()
    server.run()
