// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import org.meetuner 1.0
import "components"

Page {
	id: tunerPage
	tools: commonTools

	PageHeader {
		id: header
		text: qsTr("Tuner")
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

    TunerSlider {
        id: tuneSlider

        anchors.bottom: note.top
        anchors.left: header.left
        anchors.right: header.right
    }

	Label {
		id: note


        anchors.centerIn: tunerPage

		horizontalAlignment: Text.AlignHCenter
        color: Math.abs(noteAnalyzer.deviation) < 5 ? "#65A4F2" : "#F22727"
        text: noteAnalyzer.nearestNote

		font.pixelSize: 96

        Label {
            id: shadow

            z: parent.z - 1
            x: 2
            y: 2
            smooth: true

            horizontalAlignment: parent.horizontalAlignment
            text: parent.text
            color: "#333"
            font.pixelSize: parent.font.pixelSize
        }
	}

}
