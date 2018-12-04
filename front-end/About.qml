import QtQuick 2.9
import QtQuick.Controls.Material 2.0
import QtQuick.Controls 2.3
import QtQuick.Layouts 1.3

Page {

    title: "Page"
    header: Label {
        id: title
        text: qsTr("About")
        font.pointSize: 13
        wrapMode: Text.WordWrap
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
    }

    contentItem: AboutPage{
    }

}
