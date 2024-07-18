#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    label = new QLabel("",this);
    label->setGeometry(10,10,250,40);

    btn1 = new QPushButton("click me",this);
    btn1->setGeometry(10,50,200,40);

    SignalSlot myObject;

    // new style
    connect(&myObject, &SignalSlot::valueChanged, this, &Widget::setValue);

    // old style
    //connect(&myObject, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));

    // signal
    myObject.setValue(50);

    connect(btn1, &QPushButton::clicked, this, &Widget::btn1_click);
}

void Widget::setValue(int val){
    QString labelText = QString("Signal emmit, Value : %1").arg(val);
    label->setText(labelText);
}

void Widget::btn1_click(){
    static int value = 0;
    value += 10;
    setValue(value);
}

Widget::~Widget()
{
}

