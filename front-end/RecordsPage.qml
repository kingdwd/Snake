import QtQuick 2.9
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

Page {

    id:  recordsPage

    property var model: contr;
    property var rec: null;

    onModelChanged:{
        rec = model.getRecords();
    }

    header: Rectangle {
        height: parent.height * 0.1
        color: "#cccccc"
        Label {
            id: title
            text: qsTr("Records List")
            font.pointSize: 13
            wrapMode: Text.WordWrap
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors.fill: parent;
            anchors.margins: 5
        }
    }


    contentItem: ListView {
        id: list
        model: (rec)? rec.records: 0;

        delegate: Rectangle {
            color: (index % 2)? "#cccccc" : "#cfcfcf"
            height: recordsPage.height / 5;
            width: list.width;

            property string gamer: modelData.split(":")[0]
            property string value: modelData.split(":")[1]
            RowLayout {
                Label {

                    font.pointSize: 9
                    Layout.preferredWidth: parent.width / 2;
                    wrapMode: Text.WordWrap
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: gamer;
                }

                Label {

                    font.pointSize: 9
                    wrapMode: Text.WordWrap
                    Layout.preferredWidth: parent.width / 2;

                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    text: value;
                }

                anchors.fill: parent;
            }


        }
    }


}
