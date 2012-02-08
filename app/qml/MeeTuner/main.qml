import "components"
import QtQuick 1.1
import com.nokia.meego 1.0
import org.meetuner 1.0
import QtMobility.systeminfo 1.1

PageTileWindow {
	id: appWindow

	property alias analyzer: noteAnalyzer.frequencyAnalyzer

    NoteAnalyzer {
        id: noteAnalyzer
        Component.onCompleted: analyzer.start();
    }

	TunerPage {
		id: tunerPage
	}
    DetailsPage {
		id: testPage
	}
	AboutPage {
		id: aboutPage
	}

	ToolBarLayout {
		id: commonTools
		visible: true


		TileRow {

			pageStack: appWindow.pageStack

			anchors.fill: parent
            anchors.leftMargin: 12
            anchors.rightMargin: 12
            anchors.topMargin: 5
			spacing: 18

			TileIcon {
				id: audioIcon
				iconSource: checked ? "images/tile-audio-down.png" :
									  "images/tile-audio-up.png"
                text: qsTr("Guitar Tuner")
				checkable: true
				page: tunerPage
				transformOrigin: Item.BottomLeft
                badge: (analyzer.state === FrequencyAnalyzer.ActiveState) ? "*" : "";
			}
			TileIcon {
				id: testIcon
				iconSource: checked ? "images/tile-test-down.png" :
									  "images/tile-test-up.png"
                text: qsTr("Details")
				checkable: true
				page: testPage
			}
			TileIcon {
				iconSource: checked ? "images/tile-about-down.png" :
									  "images/tile-about-up.png"
                text: qsTr("About")
				checkable: true
				page: aboutPage
				anchors.right: parent.right
				transformOrigin: Item.BottomRight
			}
		}
	}

    ScreenSaver {
        id: saver
        screenSaverDelayed: analyzer.state === FrequencyAnalyzer.ActiveState
    }

    Connections {
        target: platformWindow
        onActiveChanged: platformWindow.active ? analyzer.resume() :
                                                 analyzer.suspend()
    }
}
