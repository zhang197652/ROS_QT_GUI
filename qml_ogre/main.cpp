/*!
 * \copyright (c) Nokia Corporation and/or its subsidiary(-ies) (qt-info@nokia.com) and/or contributors
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * \license{This source file is part of QmlOgre abd subject to the BSD license that is bundled
 * with this source code in the file LICENSE.}
 */

#include "exampleapp.h"
#include "cameranodeobject.h"
#include "ogreengine.h"
#include "ogreitem.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

QQmlApplicationEngine *g_engine = NULL;

/*
static QObject* exampleAppSingletonFactory(QQmlEngine*, QJSEngine *)
{
    ExampleApp* exampleApp = new ExampleApp(NULL);
    return exampleApp;
}
*/

int main(int argc, char **argv)
{
    QGuiApplication app(argc, argv);

	//qmlRegisterSingletonType<ExampleApp>   ("ExampleApp", 1, 0, "ExampleApp", exampleAppSingletonFactory);
	qmlRegisterType<ExampleApp>("ExampleApp", 1, 0, "ExampleApp");
    qmlRegisterType<OgreCamera>("Example", 1, 0, "Camera");

    QQmlApplicationEngine engine; /// QML引擎
    g_engine = &engine;
    engine.load(QUrl(QStringLiteral("qrc:/qml/main.qml"))); /// 加载QML文件

    //ExampleApp eApp;

    //eApp.resize(900, 700);
    //eApp.show();
    //eApp.raise();

    return app.exec();
}
