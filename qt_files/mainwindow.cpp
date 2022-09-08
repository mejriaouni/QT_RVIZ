#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "ros/ros.h"
#include <ros/master.h>
#include "rviz/visualization_manager.h"
#include "rviz/render_panel.h"
#include "rviz/display.h"
#include <visualization_msgs/Marker.h>
#include "qt_rviz/Shape.h"
#include "qt_rviz/Shapes.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("3D vision");
    this->new_topics();
    render_panel_ = new rviz::RenderPanel();
    QVBoxLayout* main_layout = new QVBoxLayout;
    main_layout->addWidget( render_panel_ );
    manager_ = new rviz::VisualizationManager( render_panel_ );
    render_panel_->initialize( manager_->getSceneManager(), manager_ );
    manager_->initialize();
    manager_->createDisplay("rviz/Marker", "Marker", true);
    ROS_ASSERT( marker_ != NULL );
    //marker_->subProp("Topic")->setValue("visualization_marker");
    manager_->startUpdate();
    grid_ = manager_->createDisplay( "rviz/Grid", "adjustable grid", true );
    ROS_ASSERT( grid_ != NULL );
    grid_->subProp( "Line Style" )->setValue( "Billboards" );
    ui->display_rviz->setLayout( main_layout );
    marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
    /*this->draw_box(0,3,0,0,0,0,0,1,3,3,1);
    this->draw_sphere(1,0,0,0,0,0,0,1,2);
    this->draw_cylinder(2,-3,0,0.5,0,0,0,1,1,1);*/
}


MainWindow::~MainWindow()
{
    delete ui;
    delete manager_;
}


void MainWindow::on_Refresh_clicked()
{
	this->new_topics();
}
void MainWindow::chatterCallback(const qt_rviz::Shapes::ConstPtr& msg)
{

  visualization_msgs::Marker marker;
  marker.action=3;
  marker_pub.publish(marker);
  for(int i=0;i<msg->shapes.size();i++)
    {
    //std::cout<<"Shapes["<<i<<"]= "<<msg->shapes[i].shape_type<<" ";
  qt_rviz::Shape msg1;
  msg1=msg->shapes[i];
  uint32_t shape =msg1.shape_type;
  if (ros::ok())
    {
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = i;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = shape;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
    marker.action = visualization_msgs::Marker::ADD;

    // Set the pose of the marker.  This is a full 6DOF pose relative to the frame/time specified in the header
    marker.pose=msg1.pose;

    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale=msg1.scales;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color=msg1.color;

    marker.lifetime = ros::Duration();
    while (marker_pub.getNumSubscribers() < 1)
    {
      if (!ros::ok())
      {
        ROS_ERROR("ros not ok");
      }
      ROS_WARN("Please create a subscriber to the marker");
      sleep(1);
    }
    marker_pub.publish(marker);
    }
    
  }
  
  
}
void MainWindow::on_topics_list_currentTextChanged(QString text)
{
    if (text.toStdString()!="")
    {
    std::cout<<text.toStdString()<<std::endl;
    marker_sub = n.subscribe(text.toStdString(), 1000, &MainWindow::chatterCallback,this);
    }
}
void MainWindow::new_topics()
{
ui ->topics_list->clear();
ros::master::V_TopicInfo master_topics;
ros::master::getTopics(master_topics);

for (ros::master::V_TopicInfo::iterator it = master_topics.begin() ; it != master_topics.end(); it++) {
  const ros::master::TopicInfo& info = *it;
  //std::cout << info.name << std::endl;
  QString topic_name = QString::fromStdString(info.name);
  if (info.datatype == "qt_rviz/Shapes")
  ui ->topics_list->addItem(topic_name);
  }
}
