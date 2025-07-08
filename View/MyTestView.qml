import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtHelper.MyTestModel 1.0

// ColumnLayout {
//     anchors.fill: parent
//     spacing: 10

//     RowLayout {
//         spacing: 10

//         MyTestModel {
//             id: myTestModel
//         }

//         Button {
//             text: "Call CPP Function"
//             Layout.fillWidth: true
//             onClicked: {
//                 myTestModel.buttonOnClicked();
//             }
//         }

//         Button {
//             text: "Test Log"
//             onClicked: console.log("This is a test message from QML")
//         }
//     }

//     TextEdit {
//         id: logView
//         Layout.fillWidth: true
//         Layout.fillHeight: true
//         readOnly: true
//         font.family: "Courier New"
//         textFormat: TextEdit.PlainText
//     }

//     Connections {
//         target: logHandler
//         function onNewMessage(message) {
//             // 追加新日志并自动滚动
//             logView.append(message);
//             logView.cursorPosition = logView.length - 1;
//         }
//     }
// }
Item {
    anchors.fill: parent
    DisplayMonitorInfo {
        id: monitorInfo
    }

    ScrollView {
        anchors.fill: parent
        padding: 10

        ListView {
            model: monitorInfo.monitors
            spacing: 15

            delegate: Column {
                width: ListView.view.width
                spacing: 8

                Label {
                    text: "显示器: " + modelData.name
                    font.bold: true
                    font.pixelSize: 16
                }

                Label {
                    text: "设备ID: " + modelData.deviceId
                    font.pixelSize: 12
                    elide: Text.ElideRight
                }

                Label {
                    text: "物理尺寸: " + modelData.width + "x" + modelData.height + " 英寸"
                    font.pixelSize: 12
                }

                Label {
                    text: "EDID数据:"
                    font.pixelSize: 12
                    font.italic: true
                }

                TextArea {
                    text: modelData.edid || "无EDID数据"
                    font.family: "Courier New"
                    font.pixelSize: 10
                    readOnly: true
                    wrapMode: Text.WrapAnywhere
                    width: parent.width
                }

                Rectangle {
                    height: 1
                    width: parent.width
                    color: "#ccc"
                }
            }
        }
    }

    Button {
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        anchors.margins: 20
        text: "刷新"
        onClicked: monitorInfo.refresh()
    }
}
