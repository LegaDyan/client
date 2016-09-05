#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtNetwork/QUdpSocket>
#include <QtNetwork/QTcpSocket>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void paintEvent(QPaintEvent* event);

private slots:
    void processPendingData();

private:
    Ui::MainWindow *ui;
    int type;
    int a, b, c, d, e, f;
    QUdpSocket udpSocket;
};

#endif // MAINWINDOW_H
