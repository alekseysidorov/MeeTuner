// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import org.meetuner 1.0
import "components"

Page {
    id: settingsPage
    property int __fontSize: 14

    tools: backTools

    PageHeader {
        id: header
        text: qsTr("Settings")
    }

    Column {

        anchors.top: header.bottom
        anchors.left: header.left
        anchors.right: header.right
        anchors.bottom: header.bottom
        anchors.topMargin: header.__bottomSpacing

        spacing: __fontSize

        FormField {
            name: qsTr("Threshold:")
            item: Slider {
                id: cutoff

                minimumValue: 0.05
                maximumValue: 0.95
                stepSize: 0.01

                value: 0.50

                valueIndicatorVisible: true
                platformStyle.inverted: true

                Binding {
                    property: "threshold"
                    target: analyzer
                    value: cutoff.value
                }
            }
        }
    }
}
