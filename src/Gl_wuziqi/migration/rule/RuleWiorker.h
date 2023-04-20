#pragma once
#include "Rule.h"
#include <QObject>

class RuleWorker : public QObject
{
    Q_OBJECT

public slots:
    void doWork(QPointF point_chess, MapPoint* ptrchesses, qreal chess_width, bool myturn) {
    //void doWork(QPointF& point_chess, MapPoint*& ptrchesses, qreal& chess_width, bool& myturn) {
        bool isWin;
        /* ... here is the expensive or blocking operation ... */
        isWin = is_win(point_chess, ptrchesses, chess_width, myturn, true);
        emit resultReady(isWin);
    }


signals:
    void resultReady(bool result);
};

class ControllerRuleWorker : public QObject
{
    Q_OBJECT
        QThread workerThread;
public:
    ControllerRuleWorker() {
        RuleWorker* worker = new RuleWorker;
        worker->moveToThread(&workerThread);
        QObject::connect(&workerThread, &QThread::finished, worker, &QObject::deleteLater);
        QObject::connect(this, SIGNAL(operate(QPointF , MapPoint *, qreal , bool )), worker, SLOT(doWork(QPointF , MapPoint *, qreal  , bool )));
        QObject::connect(worker, &RuleWorker::resultReady, this, &ControllerRuleWorker::handleResults);
        workerThread.start();
    }
    ~ControllerRuleWorker() {
        workerThread.quit();
        workerThread.wait();
    }
public slots:
    void handleResults(bool result) {
        if (result == true) {
            emit workFinished();
        }
    };
    void emitOperate(QPointF& point_chess, MapPoint* ptrchesses, qreal& chess_width, bool& myturn) {
        emit operate(point_chess, ptrchesses, chess_width, myturn);
    }
signals:
    void operate(QPointF point_chess, MapPoint* ptrchesses, qreal chess_width, bool myturn);
    void workFinished();
};