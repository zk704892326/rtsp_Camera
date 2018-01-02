VERSION = 1.0.0

PWD     := $(shell pwd)
RM      := rm -rf
CP      := cp -rf

MAKE    := make -w
QMAKE   := qmake

HOME            := /home/zk/guoguo/
THERMALSDK_DIR  := $(HOME)/ThermalSDK_20151126/SDK/linux_sdk
CAMERA_DIR      := $(PWD)/camera
#MOTOR_DIR       := $(PWD)/motor

BIN_DIR         := $(HOME)/Desktop
SHARE_DIR       := $(HOME)/Desktop
DB_PATH         := $(SHARE_DIR)/.camera.db
IMG_DIR         := $(SHARE_DIR)/.images

debian:debian-camera

debian-camera:debian-motor
	$(QMAKE) $(CAMERA_DIR)/camera.pro -o $(CAMERA_DIR)/Makefile
	$(MAKE) -C $(CAMERA_DIR)

debian-camera-clean:debian-motor-clean
	if [ -f $(CAMERA_DIR)/Makefile ];then $(MAKE) -C $(CAMERA_DIR) clean;fi
	$(RM) $(CAMERA_DIR)/Makefile
	$(RM) $(CAMERA_DIR)/camera

debian-motor:
#	$(MAKE) -C $(MOTOR_DIR)

debian-motor-clean:
#	$(MAKE) -C $(MOTOR_DIR) clean

debian-setup:
	$(CP) $(THERMALSDK_DIR)/bin/libnvdc_sdk.so /usr/lib
	$(CP) $(THERMALSDK_DIR)/bin/libnvdc_sdk.a /usr/lib

debian-libs-install:
	#apt-get update
	apt-get -y install ffmpeg libavcodec-dev libavfilter-dev libavformat-dev qt5-default qtcreator openssh-server \
		rar vim git-core build-essential linux-headers-$(shell uname -r)

install-old:
	if [ ! -d $(BIN_DIR) ];then mkdir -p $(BIN_DIR);fi
	if [ ! -d $(SHARE_DIR) ];then mkdir -p $(SHARE_DIR);fi
	if [ ! -d $(IMG_DIR) ];then mkdir -p $(IMG_DIR);fi
	$(CP) $(CAMERA_DIR)/camera $(BIN_DIR)
	ln -sf $(BIN_DIR)/camera $(HOME)/Desktop/camera
	if [ -f $(CAMERA_DIR)/camera.db ];then rm -rf $(CAMERA_DIR)/camera.db;fi
	sqlite3 $(CAMERA_DIR)/camera.db < camera.sql
	if [ ! -f $(DB_PATH) ];then cp -rf $(CAMERA_DIR)/camera.db $(DB_PATH);fi

install:debian
	if [ ! -d $(BIN_DIR) ];then mkdir -p $(BIN_DIR);fi
	if [ ! -d $(SHARE_DIR) ];then mkdir -p $(SHARE_DIR);fi
	if [ ! -d $(IMG_DIR) ];then mkdir -p $(IMG_DIR);fi
	$(CP) $(CAMERA_DIR)/camera $(BIN_DIR)
	if [ -f $(PWD)/camera.db ];then rm -rf $(PWD)/camera.db;fi
	sqlite3 $(PWD)/camera.db < camera.sql
	if [ ! -f $(DB_PATH) ];then cp -rf $(PWD)/camera.db $(DB_PATH);fi
	if [ ! -f $(PWD)/.camera.db ];then cp $(PWD)/camera.db $(PWD)/.camera.db;fi
	if [ ! -d $(PWD)/.images ];then mkdir -p $(PWD)/.images;fi

distclean:clean
	rm -rf $(BIN_DIR)/camera $(DB_PATH) $(IMG_DIR) $(PWD)/.images $(PWD)/.camera.db

clean:debian-camera-clean
