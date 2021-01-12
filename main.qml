import QtQuick 2.12
import QtQuick.Window 2.12

import BgfxItem 1.0

Window {
    visible: true
    width: 1600
    height: 800
    title: "bgfx example"

    Rectangle {
        anchors.fill: parent
        color: "green"
    }

    BgfxItem {
        width: 300
        height: 300
    }
}
