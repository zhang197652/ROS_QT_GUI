/*!
 * \copyright (c) Nokia Corporation and/or its subsidiary(-ies) (qt-info@nokia.com) and/or contributors
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * \license{This source file is part of QmlOgre abd subject to the BSD license that is bundled
 * with this source code in the file LICENSE.}
 */

#include "exampleapp.h"

#include <rviz/ogrecamera.h>
#include <rviz/ogreengine.h>
#include <rviz/ogreitem.h>
#include <rviz/display.h>
#include <rviz/debug.h>

#include <QCoreApplication>
#include <QtQml/QQmlContext>
#include <QDir>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QQuickWindow>
#include <QDebug>

extern QQmlApplicationEngine *g_engine;

static QString appPath()
{
    QString path = QCoreApplication::applicationDirPath();
    QDir dir(path);
#ifdef Q_WS_MAC
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();
#elif defined(Q_WS_WIN)
    dir.cdUp();
#endif
    return dir.absolutePath();
}

ExampleApp::ExampleApp() : m_ogreEngine(0)
  , m_quickWindow(0)
  , m_sceneManager(0)
  , m_root(0)
{
    qDebug() << "************** ExampleApp::ExampleApp ******************";
    // start Ogre once we are in the rendering thread (Ogre must live in the rendering thread)
    //connect(this, &ExampleApp::beforeRendering, this, &ExampleApp::initializeOgre, Qt::DirectConnection);
    connect(this, &ExampleApp::ogreInitialized, this, &ExampleApp::addContent);
    connect(this, SIGNAL( windowChanged( QQuickWindow* ) ), this, SLOT( onWindowChanged( QQuickWindow* ) ) );
}

ExampleApp::~ExampleApp()
{
    /*
    if (m_sceneManager) {
        m_root->destroySceneManager(m_sceneManager);
    }
    */
}


void ExampleApp::onWindowChanged( QQuickWindow* window )
{
    if ( window == Q_NULLPTR )
        return;

    disconnect(this, SIGNAL( windowChanged( QQuickWindow* ) ), this, SLOT( onWindowChanged( QQuickWindow* ) ) );

    m_quickWindow = window;
    connect(window, SIGNAL(beforeRendering()), this, SLOT(initializeOgre()), Qt::DirectConnection);
    /*
    connect( window, SIGNAL( beforeRendering( ) ),
             this, SLOT( Render( ) ), Qt::DirectConnection );
    window->setClearBeforeRendering( false );
    */
}

void ExampleApp::initializeOgre()
{
    qDebug() << "************** ExampleApp::initializeOgre ******************";

    // we only want to initialize once
  //  disconnect(this, &ExampleApp::beforeRendering, this, &ExampleApp::initializeOgre);

    disconnect(m_quickWindow, SIGNAL(beforeRendering()), this, SLOT(initializeOgre()));

    // start up Ogre
    m_ogreEngine = new rviz::OgreEngine(window());
	
	qDebug() << "************** ExampleApp::startEngine ******************";
    m_root = m_ogreEngine->startEngine();
	
    //qDebug() << "************** ExampleApp::setupResources ******************";
    //m_ogreEngine->setupResources();

    // set up Ogre scene
    //m_sceneManager = m_root->createSceneManager(Ogre::ST_GENERIC, "mySceneManager");

    //m_sceneManager->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
    //m_sceneManager->createLight("myLight")->setPosition(20, 80, 50);

    // Resources with textures must be loaded within Ogre's GL context
    m_ogreEngine->activateOgreContext();

    m_sceneManager = m_ogreEngine->getSceneManager();
    m_sceneManager->setSkyBox(true, "SpaceSkyBox", 10000);
    m_sceneManager->getRootSceneNode()->attachObject(m_sceneManager->createEntity("Head", "ogrehead.mesh"));
		
	rviz::RvizDbg::print("ExampleApp createDisplay");

	// Create a Grid display.
    rviz::Display* grid_ = m_ogreEngine->createDisplay( "rviz/Grid", "adjustable grid", true );

	rviz::RvizDbg::print("ExampleApp subProp");
	// Configure the GridDisplay the way we like it.
	grid_->subProp( "Line Style" )->setValue( "Billboards" );
	grid_->subProp( "Color" )->setValue( QColor( Qt::yellow ) );
	int thickness_percent = 25;
	int cell_size_percent = 10;
	grid_->subProp( "Line Style" )->subProp( "Line Width" )->setValue( thickness_percent / 100.0f );
	grid_->subProp( "Cell Size" )->setValue( cell_size_percent / 10.0f );
	
	rviz::RvizDbg::print("ExampleApp initFinished");

    m_ogreEngine->doneOgreContext();

    Q_EMIT(ogreInitialized());
    Q_EMIT(initFinished());
}

void ExampleApp::addContent()
{
    // expose objects as QML globals
#if 1
    g_engine->rootContext()->setContextProperty("Window", this);
    g_engine->rootContext()->setContextProperty("OgreEngine", m_ogreEngine);
 #else
    rootContext()->setContextProperty("Window", this);
    rootContext()->setContextProperty("OgreEngine", m_ogreEngine);
#endif

    // load the QML scene
 //   setResizeMode(QQuickView::SizeRootObjectToView);
    //m_quickWindow->setsetSource(QUrl("qrc:/qml/example.qml"));
    //g_engine->load(QUrl(QStringLiteral("qrc:/qml/example.qml"))); /// 加载QML文件
}
