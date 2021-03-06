/*!
 * \copyright (c) Nokia Corporation and/or its subsidiary(-ies) (qt-info@nokia.com) and/or contributors
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * \license{This source file is part of QmlOgre abd subject to the BSD license that is bundled
 * with this source code in the file LICENSE.}
 */

#ifndef EXAMPLEAPP_H
#define EXAMPLEAPP_H

#include "ogreengine.h"
#include <QQuickItem>
#include <QQuickWindow>

class ExampleApp : public QQuickItem
{
    Q_OBJECT
public:
    explicit ExampleApp();
    ~ExampleApp();
    
signals:
    void ogreInitialized();
    void initFinished();

public slots:
    void initializeOgre();
    void addContent();

protected slots:
    void onWindowChanged( QQuickWindow* window );
    
private:
    QQuickWindow *m_quickWindow;
    OgreEngine *m_ogreEngine;

    Ogre::SceneManager *m_sceneManager;
    Ogre::Root *m_root;
};

#endif // EXAMPLEAPP_H
