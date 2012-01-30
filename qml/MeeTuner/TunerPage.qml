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

	Item {
		id: tune

		height: 90
		anchors.verticalCenter: parent.verticalCenter
		anchors.left: header.left
		anchors.right: header.right

		Rectangle {
			id: slider

            property real deviation: noteAnalyzer.deviation

			width: 10
			height: tune.height

			anchors.horizontalCenter: tune.horizontalCenter
            anchors.horizontalCenterOffset: deviation

			color: "#65A4F2"
		}
	}

	Label {
		id: note

		anchors.top: tune.bottom
		anchors.topMargin: 20
		anchors.horizontalCenter: tune.horizontalCenter

		horizontalAlignment: Text.AlignHCenter
		color: Math.abs(slider.deviation) < 0.1 ? "#65A4F2" : "#F22727"
        text: noteAnalyzer.nearestNote
		font.pixelSize: 96
	}
}
