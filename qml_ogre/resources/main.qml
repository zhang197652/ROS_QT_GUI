/*!
 * \copyright (c) Nokia Corporation and/or its subsidiary(-ies) (qt-info@nokia.com) and/or contributors
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * \license{This source file is part of QmlOgre abd subject to the BSD license that is bundled
 * with this source code in the file LICENSE.}
 */

import QtQuick 2.11
import QtQuick.Window 2.11
import Example 1.0
import ExampleApp 1.0

Window {
    id: mainWindow
    visible: true
    width: 1024
    height: 768

    MouseArea {
        anchors.fill: parent
        onClicked: {
           // Qt.quit();
            //subWindow.visible = true
        }
    }

    Loader {
        id:ogreLoader
        anchors.fill: parent
        visible: true
        source: "qrc:/qml/ogre.qml"
    }

    /*
    ExampleApp {
        id: eapp1
        anchors.fill: parent
        Loader {
            id:viewportLoader
            anchors.fill: parent
            visible: false
            source: ""
        }

        onInitFinished: {
            console.log(qsTr("\r\n****************************************************\r\n ********ExampleApp Load Finish\r\n****************************************************\r\n"))
            viewportLoader.setSource("qrc:/qml/example.qml")
            viewportLoader.visible = true
        }
    }
    */
}
