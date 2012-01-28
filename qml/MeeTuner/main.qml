import "components"
import QtQuick 1.1
import com.nokia.meego 1.0
import org.meetuner 1.0

PageTileWindow {
	id: appWindow

	property alias analyzer: noteAnalyzer.frequencyAnalyzer

	initialPage: tunerPage

	TunerPage {
		id: tunerPage
	}
	TestPage {
		id: testPage
	}
	AboutPage {
		id: aboutPage
	}

	NoteAnalyzer {
		id: noteAnalyzer
	}

	ToolBarLayout {
		id: commonTools
		visible: true

		TileRow {

			pageStack: appWindow.pageStack

			anchors.fill: parent
			anchors.margins: 10
			spacing: 18

			TileIcon {
				id: audioIcon
				iconSource: checked ? "images/tile-audio-down.png" :
									  "images/tile-audio-up.png"
				text: qsTr("Tuner")
				checkable: true
				page: tunerPage
				transformOrigin: Item.BottomLeft
			}
			TileIcon {
				id: testIcon
				iconSource: checked ? "images/tile-test-down.png" :
									  "images/tile-test-up.png"
				text: qsTr("Debug")
				checkable: true
				page: testPage
				badge: (analyzer.state === FrequencyAnalyzer.ActiveState) ? "*" : "";
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
}
