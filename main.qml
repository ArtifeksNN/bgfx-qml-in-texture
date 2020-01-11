import QtQuick 2.12
import QtQuick.Window 2.12

import BgfxItemExample 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: "bgfx example"

    BgfxItem {
        width: 300
        height: 300
    }

    Rectangle {
        anchors.fill: parent
        color: "green"
    }

}
