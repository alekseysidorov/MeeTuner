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

    TunerSlider {
        id: tuneSlider

        anchors.top: header.bottom
        anchors.topMargin: 24
        anchors.left: header.left
        anchors.right: header.right
    }

	Label {
		id: note

		horizontalAlignment: Text.AlignHCenter
        color: Math.abs(noteAnalyzer.deviation) < 5 ? "#65A4F2" : "#F22727"
        text: noteAnalyzer.nearestNote
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: tuneSlider.bottom
        anchors.topMargin: 12


		font.pixelSize: 96
	}
}
