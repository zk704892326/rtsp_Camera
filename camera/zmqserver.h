#ifndef ZMQSERVER_H
#define ZMQSERVER_H

#include <QThread>

class zmqServer : public QThread
{
public:
    explicit zmqServer();
    ~zmqServer();
private:
     void run();
};

#endif // ZMQSERVER_H
