import QtQuick 1.1
import com.nokia.meego 1.0
import org.meetuner 1.0

Page {

	Rectangle {
     id: rectangle1
		anchors.fill: parent
		color: "white"

		Button {
            id: button
			anchors.centerIn: parent
			text: "Click me"
			onClicked: {
				audioIcon.alert();
				analyzer.start();
			}
		}

        Label {
            anchors.top: button.bottom
            text: analyzer.currentFrequency
            font.pointSize: 12
            anchors.topMargin: 15
            anchors.horizontalCenter: button.horizontalCenter
        }

		Analyzer {
			id: analyzer
		}
	}

    tools: commonTools
}
