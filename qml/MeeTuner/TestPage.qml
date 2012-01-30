// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import org.meetuner 1.0
import "components"

Page {
	id: tunerPage
	tools: commonTools

	PageHeader {
		text: qsTr("Debug frequency analyzer")
	}

	Label {
		id: label

		anchors.centerIn: parent

		text: qsTr("Frequency")
		font.pointSize: 14
		color: "gray"
	}

	Label {
		id: frequency
		x: 0

		anchors.top: label.bottom
		anchors.topMargin: 15

		text: analyzer.currentFrequency.toFixed(2)
		anchors.horizontalCenter: parent.horizontalCenter
		font.pointSize: label.font.pointSize
		color: label.color
	}

	Button {
		id: button
		anchors.horizontalCenter: parent.horizontalCenter
		anchors.bottom: parent.bottom
		text: analyzer.state === FrequencyAnalyzer.ActiveState ? qsTr("Stop") :
																 qsTr("Start")
		onClicked: {
			if (analyzer.state === FrequencyAnalyzer.ActiveState)
				analyzer.stop();
			else
				analyzer.start();
		}
	}

    Slider {
        id: cutoff

        minimumValue: 0
        maximumValue: 1
        stepSize: 0.01

        value: 0.25

        valueIndicatorVisible: true
        platformStyle.inverted: true

        anchors.right: parent.right
        anchors.rightMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.top: frequency.bottom
        anchors.topMargin: 10

        Binding {
            property: "threshold"
            target: analyzer
            value: cutoff.value
        }
    }



	onVisibleChanged: {
		//if (visible) {
		//	if (analyzer.state === FrequencyAnalyzer.ActiveState)
		//		analyzer.suspend();
		//} else {
		//	if (analyzer.state === FrequencyAnalyzer.IdleState)
		//		analyzer.resume();
		//}
	}
}
