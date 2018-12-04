import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Item {
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent

        Image {
            id: aboutLogo

            Layout.preferredHeight: parent.width / 2
            Layout.preferredWidth: width
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            source: "qrc:/qtquickplugin/images/template_image.png"
        }

        Label {
            id: aboutText
            text: qsTr("Label")
            font.family: "Verdana"
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            wrapMode: Text.WordWrap
            Layout.fillWidth: true
        }

    }

}
