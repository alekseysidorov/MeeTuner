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
        text: qsTr("Debug frequency analyzer")
    }

    Column {
        anchors.centerIn: parent
        spacing: __fontSize

        Label {
            text: qsTr("Frequency: \n") + analyzer.currentFrequency.toFixed(2)
            font.pointSize: __fontSize
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            platformStyle.inverted: true
        }
        Label {
            text: qsTr("Nearest note: \n") + noteAnalyzer.nearestNote
            font.pointSize: __fontSize
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            platformStyle.inverted: true
        }
        Label {
            text: qsTr("Deviation: \n") + noteAnalyzer.deviation.toFixed(2)
            font.pointSize: __fontSize
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            platformStyle.inverted: true
        }
        Label {
            text: qsTr("Octave: \n") + noteAnalyzer.octave
            font.pointSize: __fontSize
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            platformStyle.inverted: true
        }
        Label {
            text: qsTr("Threshold")
            font.pointSize: __fontSize
            horizontalAlignment: Text.AlignHCenter
            width: parent.width
            platformStyle.inverted: true
        }

        Slider {
            id: cutoff

            minimumValue: 0
            maximumValue: 1
            stepSize: 0.01

            value: 0.66

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
