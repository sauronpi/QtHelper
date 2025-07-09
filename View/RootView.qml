import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    anchors.fill: parent

    // 定义页面路径的组件
    Component.onCompleted: {
        listModel.append({name: "MyTest", page: "MyTestView.qml"})
        listModel.append({name: "DisplayMonitorInfo", page: "DisplayMonitorInfoView.qml"})
        listModel.append({name: "MonitorControl", page: "MonitorControlView.qml"})
        listModel.append({name: "Button", page: "Button.qml"})
        listModel.append({name: "ListView", page: "ListView.qml"})
        listModel.append({name: "TextEdit", page: "TextEdit.qml"})
        listModel.append({name: "帮助", page: "HelpPage.qml"})
    }

    ListModel { id: listModel }

    RowLayout {
        anchors.fill: parent
        spacing: 0

        // 左侧列表视图
        ListView {
            id: listView
            Layout.preferredWidth: 200
            Layout.fillHeight: true
            model: listModel
            clip: true

            delegate: ItemDelegate {
                width: ListView.view.width
                text: name
                highlighted: ListView.isCurrentItem

                onClicked: {
                    listView.currentIndex = index
                    loader.source = page  // 切换右侧内容
                }
            }

            // 列表项高亮
            highlight: Rectangle {
                color: "#e0e0e0"
                radius: 4
            }
        }

        // 右侧分隔线
        Rectangle {
            width: 1
            Layout.fillHeight: true
            color: "#cccccc"
        }

        // 右侧内容加载器
        Loader {
            id: loader
            Layout.fillWidth: true
            Layout.fillHeight: true
            source: "MyTestView.qml"  // 默认页面

            // 加载时的过渡动画
            transitions: Transition {
                NumberAnimation {
                    property: "opacity"
                    from: 0
                    to: 1
                    duration: 200
                }
            }
        }
    }
}
