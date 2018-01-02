VERSION = 1.0.0

PWD     = $(shell pwd)
RM      = rm -rf
CP      = cp -rf

MAKE    = make -w

THERMALSDK_DIR  = $(HOME)/ThermalSDK_20151126/SDK/linux_sdk

CFLAGS := -I$(THERMALSDK_DIR)/include 
LDFLAGS = -L$(THERMALSDK_DIR)/bin -lnvdc_sdk -lpthread -lrt

CPP=g++ -O2

all:motor.o motor_sample.o
	$(CPP) -o motor_sample motor_sample.o $(LDFLAGS)

%.o:%.cpp
	$(CPP) $(CFLAGS) -o $@ -c $^

clean:
	$(RM) *.o motor_sample
