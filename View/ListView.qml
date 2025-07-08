import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

Item {
    anchors.fill: parent
    // 数据模型
    ListModel {
        id: listModel
        ListElement { name: "Apple"; category: "Fruit"; price: "$2.5" }
        ListElement { name: "Carrot"; category: "Vegetable"; price: "$1.0" }
        ListElement { name: "Beef"; category: "Meat"; price: "$8.0" }
    }

    ColumnLayout {
        anchors.fill: parent
        spacing: 20

        // 垂直列表（带分组和固定表头）
        GroupBox {
            title: "垂直列表（带分组和下拉刷新）"
            Layout.fillWidth: true
            Layout.preferredHeight: 300

            ListView {
                id: verticalListView
                width: parent.width
                height: parent.height
                clip: true
                model: listModel
                spacing: 5

                // 固定表头
                header: Rectangle {
                    width: parent.width
                    height: 40
                    color: "#f0f0f0"
                    Row {
                        anchors.fill: parent
                        spacing: 20
                        Text { width: 200; text: "名称"; font.bold: true }
                        Text { width: 200; text: "价格"; font.bold: true }
                    }
                }

                // 分组显示
                section {
                    property: "category"
                    delegate: Rectangle {
                        width: parent.width
                        height: 30
                        color: "#e0e0e0"
                        Text {
                            anchors.verticalCenter: parent.verticalCenter
                            leftPadding: 10
                            text: section
                            font.bold: true
                        }
                    }
                }

                // 列表项代理
                delegate: Item {
                    width: verticalListView.width
                    height: 40
                    Row {
                        anchors.fill: parent
                        spacing: 20
                        leftPadding: 15
                        Text { width: 200; text: name }
                        Text { width: 200; text: price }
                    }

                    // 鼠标交互
                    MouseArea {
                        anchors.fill: parent
                        onClicked: verticalListView.currentIndex = index
                    }
                }

                // 高亮选中项
                highlight: Rectangle {
                    color: "lightblue"
                    radius: 5
                }

                // 下拉刷新提示
                Rectangle {
                    visible: verticalListView.contentY < -20
                    width: parent.width
                    height: 30
                    color: "lightgreen"
                    Text {
                        anchors.centerIn: parent
                        text: "松开刷新数据..."
                    }
                }

                // 滚动事件处理
                onMovementEnded: {
                    if (contentY < -30) {
                        listModel.append({
                            name: "New Item",
                            category: "Other",
                            price: "$0.0"
                        })
                    }
                }
            }
        }

        // 水平列表
        GroupBox {
            title: "水平列表（带动画）"
            Layout.fillWidth: true
            Layout.preferredHeight: 150

            ListView {
                id: horizontalListView
                width: parent.width
                height: parent.height
                orientation: ListView.Horizontal
                spacing: 10
                model: listModel
                cacheBuffer: 200 // 预加载项提升性能

                delegate: Rectangle {
                    width: 120
                    height: parent.height
                    color: index % 2 ? "#f8f8f8" : "white"
                    border.color: "gray"

                    Column {
                        anchors.centerIn: parent
                        spacing: 5
                        Text { text: name; font.bold: true }
                        Text { text: category; color: "gray" }
                        Text { text: price; color: "green" }
                    }

                    // 点击动画
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            horizontalListView.currentIndex = index
                            parent.color = "lightblue"
                            resetColor.start()
                        }
                    }

                    ColorAnimation on color {
                        id: resetColor
                        to: index % 2 ? "#f8f8f8" : "white"
                        duration: 500
                    }
                }
            }
        }

        // 操作按钮
        RowLayout {
            spacing: 10
            Button {
                text: "添加项目"
                onClicked: listModel.append({
                    name: "Item " + (listModel.count + 1),
                    category: "Category " + (listModel.count % 3 + 1),
                    price: "$" + Math.random().toFixed(2)
                })
            }
            Button {
                text: "删除当前项"
                onClicked: if (listModel.count > 0) listModel.remove(verticalListView.currentIndex)
            }
        }
    }
}
