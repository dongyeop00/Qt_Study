#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class SignalSlot: public QObject{
    Q_OBJECT

public:
    void setValue(int val){
        emit valueChanged(val);
    }

signals:
    void valueChanged(int newValue);

private:
    int value;
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    QLabel *label;
    QPushButton *btn1;

public slots:
    void setValue(int val);
    void btn1_click();
};
#endif // WIDGET_H
