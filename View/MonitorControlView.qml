import QtQuick
import QtQuick.Controls

import QtHelper.MonitorControl 1.0

Item {
    MonitorControl {
        id: monitorControl
    }

    Column {
        anchors.centerIn: parent
        spacing: 20

        ComboBox {
            id: monitorCombo
            width: 300
            model: ListModel { id: monitorModel }
            onActivated: brightnessSlider.enabled = true
        }

        Slider {
            id: brightnessSlider
            width: 300
            from: 0
            to: 100
            value: 50
            enabled: false
            onMoved: monitorControl.setBrightness(monitorCombo.currentIndex, value)
        }

        Button {
            text: "Refresh Monitors"
            onClicked: monitorControl.refreshMonitors()
        }
    }

    Connections {
        target: monitorControl
        function onMonitorsUpdated(names) {
            monitorModel.clear();
            for (var i = 0; i < names.length; i++) {
                monitorModel.append({text: names[i]});
            }
            if (names.length > 0) {
                monitorCombo.currentIndex = 0;
                brightnessSlider.enabled = true;
            }
        }
    }

    Component.onCompleted: monitorControl.refreshMonitors()
}
