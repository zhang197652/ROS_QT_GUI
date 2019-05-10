#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <ros/ros.h>

#include <rviz/ogrecamera.h>
#include <rviz/ogreengine.h>
#include <rviz/ogreitem.h>
#include "exampleapp.h"

QQmlApplicationEngine *g_engine = NULL;

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

	qmlRegisterType<ExampleApp>("ExampleApp", 1, 0, "ExampleApp");
	
	
	ros::init(argc, argv, "librviz_qml", ros::init_options::AnonymousName);
	
    QQmlApplicationEngine engine; /// QML引擎
    g_engine = &engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml"))); /// 加载QML文件


    return app.exec();
}
