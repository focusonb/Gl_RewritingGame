#pragma once
#include "socketManager.h"
#include "../comStruct.h"
//#include <QObject>

class DataWuziqiSpecType;
class GameSocketManager :
    public SocketManager
{
    //Q_OBJECT
//signals:
public:
    void recievedData(ClickPoint point_chess, bool BRequestConnection) {};

public:
//public slots:
    void sendStrData(std::string msgStr);

public:
    GameSocketManager(DataWuziqiSpecType* dataWuziqiSpecType, void* ptr);
    void setBRequestConnection(bool BRequestConnection) { m_BRequestConnection = BRequestConnection; }
    bool getBRequestConnection() const { return m_BRequestConnection; }
    void reactToMessage(std::string msg) override;
    inline void setBReceive(bool bReceive) {
        m_bReceive = bReceive;
    }
    inline bool isReceive() const {
        return m_bReceive;
    }
private:
    DataWuziqiSpecType* m_dataWuziqiSpecType;
    bool m_bReceive = false;
    void* m_ptr;
protected:
    void setRequestConnectionState() override { m_BRequestConnection = true; }
    void setWaitForConnectionState() override { m_BRequestConnection = false; }
};

