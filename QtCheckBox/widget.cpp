#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    QString str1[3] = {"Game", "Office", "Develop"};
    QString str2[3] = {"P&rogramming", "Q&t", "O&S"};

    int xpos = 30;
    int ypos = 30;

    chk_group[0] = new QButtonGroup(this);
    chk_group[1] = new QButtonGroup(this);

    for(int i = 0 ; i < 3 ; i++){
        exclusive[i] = new QCheckBox(str1[i], this);
        exclusive[i]->setGeometry(xpos, ypos, 120, 30);
        chk_group[0]->addButton(exclusive[i]);


        non_exclusive[i] = new QCheckBox(str2[i], this);
        non_exclusive[i]->setGeometry(xpos + 120, ypos, 120, 30);
        chk_group[1]->addButton(non_exclusive[i]);

        connect(exclusive[i], SIGNAL(clicked()),this, SLOT(slot_chkChanged ()));
        ypos += 40;
    }

    chk_group[0]->setExclusive(false);
    chk_group[1]->setExclusive(true);

    //exclusive[0]->setIcon(QIcon(":/dd.png"));
    //exclusive[1]->setIcon(QIcon(":/kkk.jpeg"));
    //exclusive[2]->setIcon(QIcon(":/love.jpeg"));

    //non_exclusive[0]->setIcon(QIcon(":/marong.jpeg"));
    //non_exclusive[1]->setIcon(QIcon(":/oh.jpeg"));
    //non_exclusive[2]->setIcon(QIcon(":/wow.jpeg"));

}

void Widget::slot_chkChanged(){
    for(int i=0; i<3; i++){
        if(exclusive[i]->checkState()){
            qDebug("checkbox %d selected",i+1);
        }
    }
}

Widget::~Widget()
{
}

