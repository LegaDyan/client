#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    type = -1;
    udpSocket.bind(QHostAddress::LocalHost, 5888);
    connect(&udpSocket, SIGNAL(readyRead()), this, SLOT(processPendingData()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::processPendingData() {
    QByteArray datagram;//拥于存放接收的数据报
    do{
        datagram.resize(udpSocket.pendingDatagramSize());//让datagram的大小为等待处理的数据报的大小，这样才能接收到完整的数据
        udpSocket.readDatagram(datagram.data(),datagram.size());//接收数据报，将其存放到datagram中
    }while(udpSocket.hasPendingDatagrams());//拥有等待的数据报
    QDataStream in(&datagram,QIODevice::ReadOnly);
    in.setVersion(QDataStream::Qt_4_3);
    QString str;
    in >> str;
    auto s = str.toStdString().c_str();

    sscanf(s, "%d", &type);
    if (type == 0) {
        sscanf(s + 1, "%d %d %d", &a, &b, &c);
    }
    else if (type == 1) {
        sscanf(s + 1, "%d %d %d %d", &a, &b, &c, &d);
    }
    else sscanf(s + 1, "%d %d %d %d %d %d", &a, &b, &c, &d, &e, &f);
    qDebug() << type << a << b << c;
    update();
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    p.setBrush(Qt::yellow);
    int w = 0, h = 0;
    while (1) {
        w += 50;
        if (w > width()) break;
        p.drawLine(QPoint(w, 0), QPoint(w, height()));
    }
    while (1) {
        h += 50;
        if (h > width()) break;
        p.drawLine(QPoint(0, h), QPoint(width(), h));
    }

    if (type == -1) return;
    if (type == 0) {
        p.drawEllipse(QPoint(a, b), c, c);
    }
    else if (type == 1) {
        p.drawRect(a, b, c, d);
    }
    else if (type == 2) {
        static const QPoint points[3] = {
              QPoint(a, b),
              QPoint(c, d),
              QPoint(e, f)
          };
        p.drawPolygon(points, 3);
    }
}
