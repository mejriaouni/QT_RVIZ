#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ros/ros.h"
#include <ros/master.h>
#include "qt_rviz/Shape.h"
#include "qt_rviz/Shapes.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

namespace rviz
{
class Display;
class RenderPanel;
class VisualizationManager;
}

class MainWindow : public QMainWindow
{	
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Refresh_clicked();

    void on_topics_list_currentTextChanged(QString text);

private:
    Ui::MainWindow *ui;
    void new_topics();
    void chatterCallback(const qt_rviz::Shapes::ConstPtr& msg);
    rviz::VisualizationManager* manager_;
    rviz::RenderPanel* render_panel_;
    rviz::Display* grid_;
    rviz::Display* marker_;
    ros::NodeHandle n;
    ros::Publisher marker_pub;
    ros::Subscriber marker_sub;
};
#endif // MAINWINDOW_H
