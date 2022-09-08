#include "mainwindow.h"
#include "ros/ros.h"
#include <QApplication>
#include <ros/master.h>
int main(int argc, char *argv[])
{

    ros::init(argc, argv, "qt_rviz");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
