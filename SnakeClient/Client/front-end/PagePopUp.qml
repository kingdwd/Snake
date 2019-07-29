import QtQuick 2.11
import QtQuick.Controls 2.3
import QtQuick.Controls.Material 2.0
import QtQuick.Layouts 1.3

BasePopUp {
    id: pagePopUp
    property var source: null
    autoClose: false

    Item {
        id: sourceVal
        anchors.fill: parent
    }

    onSourceChanged: {
        source.parent = sourceVal;
        source.anchors.fill = sourceVal;

        if (source.close) {
            closeConnect.target = source;
        }
    }
    Connections {
        id : closeConnect
        target: null
        ignoreUnknownSignals: true
        onClose: {
            pagePopUp.close();
        }
    }
}
