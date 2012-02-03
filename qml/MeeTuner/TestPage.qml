// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import org.meetuner 1.0
import "components"

Page {
    id: tunerPage

    property int __fontSize: 14
    property color __fontColor: "gray"

    tools: commonTools

    PageHeader {
        id: header
        text: qsTr("Debug frequency analyzer")
    }

    Column {

        anchors.top: header.bottom
        anchors.left: header.left
        anchors.right: header.right
        anchors.bottom: header.bottom
        anchors.topMargin: header.height

        spacing: __fontSize

        ValueField {
            name: qsTr("Frequency:")
            value: analyzer.currentFrequency.toFixed(2)
        }
        ValueField {
            name: qsTr("Nearest note:")
            value: noteAnalyzer.nearestNote
        }
        ValueField {
            name: qsTr("Deviation:")
            value: noteAnalyzer.deviation.toFixed(2)
        }
        ValueField {
            name: qsTr("Octave:")
            value: noteAnalyzer.octave
        }
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
