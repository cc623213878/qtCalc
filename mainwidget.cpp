#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    int i, x, y;
    QString str;
    x = 215;
    y = 50;
    isdot = false;
    isNum = false;
    this->resize(225, 240);

    display.setParent(this);
    display.resize(x, y);
    display.move(5, 5);
    display.setAlignment(Qt::AlignRight);
    display.setFont(QFont("Microsoft YaHei", 16));
    display.setReadOnly(true);
    display.setStyleSheet("border-width:0;border-style:outset");

    setButton(50, 30, 5, 35 * 3 + 45 + y, this, "0", number[0], QFont("Microsoft YaHei", 10));
    connect(&number[i], &QPushButton::clicked, [=]() { inputNumber(i + 48); });
    for (i = 1; i < 10; i++)
    {
        setButton(50, 30, 55 * ((i - 1) % 3) + 5, 35 * ((i - 1) / 3) + 45 + y, this, str.setNum(i), number[i], QFont("Microsoft YaHei", 10));
        connect(&number[i], &QPushButton::clicked, [=]() { inputNumber(i + 48); });
    }

    setButton(50, 30, 5 + 1 * 55, 35 * 4 + 10 + y, this, ".", dot, QFont("Microsoft YaHei", 10));
    setButton(50, 30, 5 + 3 * 55, 10 + y, this, "+", plus, QFont("Microsoft YaHei", 10));
    setButton(50, 30, 5 + 3 * 55, 10 + y + 35 * 1, this, "-", subtract, QFont("Microsoft YaHei", 10));
    setButton(50, 30, 5 + 3 * 55, 10 + y + 35 * 2, this, "*", multiply, QFont("Microsoft YaHei", 10));
    setButton(50, 30, 5 + 3 * 55, 10 + y + 35 * 3, this, "/", divide, QFont("Microsoft YaHei", 10));
    setButton(50, 30, 5 + 2 * 55, 10 + y, this, "^", power, QFont("Microsoft YaHei", 10));
    setButton(105, 30, 5 + 2 * 55, 10 + y + 35 * 4, this, "=", equal, QFont("Microsoft YaHei", 10));
    setButton(50, 30, 5 + 1 * 55, 10 + y, this, "<", del, QFont("Microsoft YaHei", 10));
    setButton(50, 30, 5, 10 + y, this, "C", clr, QFont("Microsoft YaHei", 10));

    connect(&dot, &QPushButton::clicked, [=]() { inputNumber('.'); });
    connect(&del, &QPushButton::clicked, [=]() { delNum(); });
    connect(&clr, &QPushButton::clicked, [=]() { clearNum(); });
    connect(&plus, &QPushButton::clicked, [=]() { addoperator(0); });
    connect(&subtract, &QPushButton::clicked, [=]() { addoperator(1); });
    connect(&multiply, &QPushButton::clicked, [=]() { addoperator(2); });
    connect(&divide, &QPushButton::clicked, [=]() { addoperator(3); });
    connect(&power, &QPushButton::clicked, [=]() { addoperator(4); });
    connect(&equal, &QPushButton::clicked, [=]() {equalNum();isNum=false;isdot=false;operaNum=5; });
}

MainWidget::~MainWidget()
{
}
void MainWidget::setButton(int w, int h, int x, int y, QWidget *parent, QString str, QPushButton &button, QFont font)
{
    button.resize(w, h);
    button.setParent(parent);
    button.setText(str);
    button.move(x, y);
    button.setFont(font);
}
void MainWidget::inputNumber(char ch)
{
    if (operaNum == 5){
        clearNum();
        operaNum=0;
    }
    if (ch == '.' && isdot == false)
    {
        if (display.text().length() <= 0)
        {
            display.setText(QString("0") + ch);
        }
        else
        {
            display.setText(display.text() + ch);
        }
        isdot = true;
    }
    if (ch != '.')
    {
        display.setText(display.text() + ch);
    }
}

void MainWidget::delNum()
{
    QString str;
    str = display.text();
    str = str.left(str.length() - 1);
    display.setText(str);
    if (str.indexOf('.') == -1)
    {
        isdot = false;
    }
}
void MainWidget::clearNum()
{
    display.clear();
    isNum = false;
    isdot = false;
}

void MainWidget::addoperator(int oper)
{
    if (isNum)
    {
        equalNum();
        operaNum = oper;
        A = display.text();
        display.clear();
    }
    else
    {
        isNum = true;
        operaNum = oper;
        if(display.text().isEmpty())
            A="0";
        else
            A = display.text();
        display.clear();
    }
}

void MainWidget::plusNum()
{
    QString str;
    display.setText(str.setNum(A.toDouble() + display.text().toDouble()));
}

void MainWidget::subtractNum()
{
    QString str;
    display.setText(str.setNum(A.toDouble() - display.text().toDouble()));
}

void MainWidget::multiplyNum()
{
    QString str;
    display.setText(str.setNum(A.toDouble() * display.text().toDouble()));
}

void MainWidget::divideNum()
{
    QString str;
    display.setText(str.setNum(A.toDouble() / display.text().toDouble()));
}

void MainWidget::powerNum()
{
    QString str;
    display.setText(str.setNum(pow(A.toDouble(), display.text().toDouble())));
}

void MainWidget::equalNum()
{
    switch (operaNum)
    {
    case 0:
        plusNum();
        break;
    case 1:
        subtractNum();
        break;
    case 2:
        multiplyNum();
        break;
    case 3:
        divideNum();
        break;
    case 4:
        powerNum();
        break;
    default:
        break;
    }
}
