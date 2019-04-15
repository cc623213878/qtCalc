#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <math.h>
class MainWidget : public QWidget
{
    Q_OBJECT

  public:
    MainWidget(QWidget *parent = 0);
    ~MainWidget();
    void inputNumber(char ch);

    void setButton(int w, int h, int x, int y, QWidget *parent, QString str, QPushButton &button, QFont font);
    void delNum();
    void clearNum();
    void addoperator(int oper);
    void plusNum();
    void subtractNum();
    void multiplyNum();
    void divideNum();
    void powerNum();
    void equalNum();

  private:
    QPushButton number[10], dot;                                //数字键与小数点
    QPushButton plus, subtract, multiply, divide, power, equal; //加减乘除 乘方 等号按键
    QPushButton del, clr;                                       //删除键  清空键
    QLineEdit display;
    bool isdot; //表示当前输入的数字是否含小数点
    bool isNum; //是否有被操作数存储在A变量中
    QString A;  //表示被操作存储
    //(+,-,*,/,^)分别用(0,1,2,3,4)代表  运算符   5表示无
    int operaNum;
};

#endif // MAINWIDGET_H
