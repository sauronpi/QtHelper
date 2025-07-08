import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

RowLayout {
    anchors.fill: parent
    // 数据模型
    ListModel {
        id: listModel
        ListElement {
            name: "Button"
            category: "Control"
            price: "$2.5"
        }
        ListElement { name: "ListView"; category: "Fruit"; price: "$2.5" }
        ListElement { name: "Carrot"; category: "Vegetable"; price: "$1.0" }
        ListElement { name: "Beef"; category: "Meat"; price: "$8.0" }
    }

    ListView {
        id: listView
        width: 200
        Layout.fillHeight: true
        model: listModel
        // spacing: 20

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
            width: listView.width
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
                onClicked: listView.currentIndex = index
            }
        }

        // 高亮选中项
        highlight: Rectangle { color: "lightblue" }

        // 下拉刷新提示
        Rectangle {
            y: 0
            // anchors.bottom: parent.top
            visible: listView.contentY < -40
            width: parent.width
            height: 30
            color: "lightgreen"
            Text {
                anchors.centerIn: parent
                text: "松开刷新数据..."
            }
        }

        // 监听垂直滚动
        onContentYChanged: {
            console.log("垂直滚动坐标 (contentY):", contentY)
        }

        // 监听水平滚动（如果启用了水平滚动）
        onContentXChanged: {
            console.log("水平滚动坐标 (contentX):", contentX)
        }

        // 滚动事件处理
        onMovementEnded: {
            console.log(contentY)
            if (contentY < -70) {
                listModel.append({
                                     name: "New Item",
                                     category: "Other",
                                     price: "$0.0"
                                 })
            }
        }
    }

    // 操作按钮
    ColumnLayout {
        spacing: 10
        Button {
            text: "添加项目"
            onClicked: {
                listModel.append({
                                     name: "Item " + (listModel.count + 1),
                                     category: "Category " + (listModel.count % 3 + 1),
                                     price: "$" + Math.random().toFixed(2)
                                 })
                listView.positionViewAtEnd()
            }
        }
        Button {
            text: "删除当前项"
            onClicked: if (listModel.count > 0) listModel.remove(listView.currentIndex)
        }
    }

}
