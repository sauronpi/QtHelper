import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtHelper.MyTestModel 1.0

ColumnLayout {
    anchors.fill: parent
    spacing: 10

    RowLayout {
        spacing: 10

        MyTestModel {
            id: myTestModel
        }

        Button {
            text: "Call CPP Function"
            Layout.fillWidth: true
            onClicked: {
                myTestModel.buttonOnClicked();
            }
        }

        Button {
            text: "Test Log"
            onClicked: console.log("This is a test message from QML")
        }
    }

    TextEdit {
        id: logView
        Layout.fillWidth: true
        Layout.fillHeight: true
        readOnly: true
        font.family: "Courier New"
        textFormat: TextEdit.PlainText
    }

    Connections {
        target: logHandler
        function onNewMessage(message) {
            // 追加新日志并自动滚动
            logView.append(message);
            logView.cursorPosition = logView.length - 1;
        }
    }
}
