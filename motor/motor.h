#ifndef MOTOR_H
#define MOTOR_H

class Motor {
	public:
		Motor();
		~Motor();
		float motorX;
		float motorY;
		float motorZoom;
		int motorDirection;
		bool open(const char *ip, const int port, const char *user, const char *password);
		void close();
		bool stop();
		bool moveUp();
		bool moveDown();
		bool moveLeft();
		bool moveRight();
		bool rotateLeftUp();
		bool rotateSetPostion(int p_nType,float p_nPan,float p_nTilt,float p_nZoom);
		bool rotateGetPostion(float *p_nPan,float *p_nTilt,float *p_nZoom,int *p_nDirection);
		//bool stop(const char *ip, const int port, const char *user, const char *password);
		//bool moveUp(const char *ip, const int port, const char *user, const char *password);
		//bool moveDown(const char *ip, const int port, const char *user, const char *password);
		//bool moveLeft(const char *ip, const int port, const char *user, const char *password);
		//bool moveRight(const char *ip, const int port, const char *user, const char *password);
		bool isOpen();
		int state;
	private:
		char *ip;
		int port;
		char *user;
		char *password;
		void *device;
		long handle;
		int speed;
		void setLoginInfo();
};

#endif
