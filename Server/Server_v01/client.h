#ifndef CLIENT_H
#define CLIENT_H

#include <QTcpSocket>

class Client
{
public:
    Client();
    Client(QTcpSocket*, QString, int, int);

    const QString getName()const{return this->Name;}
    QTcpSocket* getSocket()const{return this->soc;}
    const int getX()const{return x;}
    const int getY()const{return y;}
    const quint16 getBlockSize()const{return blockSize;}
    bool getAuth()const{return Auth;}

    void setX(const int);
    void setY(const int);
    void setName(const QString);
    void setSocket(QTcpSocket*);
    void setBlockSize(const quint16);
    void setAuth(bool);
private:
    QTcpSocket *soc;
    bool Auth;
    QString Name;
    int x;
    int y;
    quint16 blockSize;
};

#endif // CLIENT_H
