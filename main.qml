import QtQuick 2.12
import QtQuick.Window 2.12

import BgfxItemExample 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    BgfxItem {
        anchors.fill: parent
    }
}
