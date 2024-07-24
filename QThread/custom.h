#ifndef CUSTOM_H
#define CUSTOM_H

#include <QObject>

class Custom : public QObject
{
    Q_OBJECT
public:
    explicit Custom(QObject *parent = nullptr);

public slots:
    void doWork();

signals:
    void workFinished();

};

#endif // CUSTOM_H
