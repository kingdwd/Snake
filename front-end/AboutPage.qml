import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Item {
    ColumnLayout {
        id: columnLayout
        anchors.fill: parent
        spacing: 10

        Rectangle {
            Layout.preferredHeight: parent.width / 4
            Layout.preferredWidth: parent.width / 4
            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop
            color: "#00000000"
            Image {
                id: aboutLogo
                fillMode: Image.PreserveAspectFit

                source: "qrc:/logo/logo"
                anchors.margins: 10
                anchors.fill: parent

            }
        }



        Flickable {
            id: flickable
            flickableDirection: Flickable.VerticalFlick

            Layout.preferredHeight: parent.width - parent.width / 4


            TextArea.flickable: TextArea {
                id: textArea
                textFormat: Qt.RichText
                wrapMode: TextArea.Wrap
                readOnly: true
                persistentSelection: true

                leftPadding: 6
                rightPadding: 6
                topPadding: 0
                bottomPadding: 0
                background: null

                text: qsTr("Управление игрой происходит посредством нажатия на тачпад вашего устройства, чем чаще нажимаете, тем быстрее двигается змейка. Каждое последующее нажатие, изменяет направление змейки, в противоположную сторону.
Цель игры набрать максимальное количество очков. Количество очков зависит от пройденного расстояния.
Автор: Янкович Роман. Группа 10903516");
                font.family: "Verdana"
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignTop

                onLinkActivated: Qt.openUrlExternally(link)
            }

            ScrollBar.vertical: ScrollBar {}
            Layout.fillWidth: true

        }

//        TextEdit {



////            Label {
////                id: aboutText

////                wrapMode: Text.WordWrap

////            }
//            wrapMode: Text.WordWrap



//        }


    }

}
