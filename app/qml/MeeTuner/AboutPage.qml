// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import "components"

Page {
    id: aboutPage

    PageHeader {
        id: header
        text: qsTr("About MeeTuner")
    }

    Column {

        spacing: 14

        anchors.top: header.bottom
        anchors.right: header.right
        anchors.left: header.left
        anchors.topMargin: header.__bottomSpacing

        Label {
            platformStyle.inverted: true
            text: qsTr("Aleksey and Maksim Sidorov presents a guitar tuner for MeeGo Harmattan. <br />" +
                       "This is a pre-alpha software! <br />" +
                       "Visit our <a href=\"https://github.com/gorthauer/MeeTuner\">webpage</a> for details.")
            width: parent.width
            textFormat: Text.RichText
            onLinkActivated: Qt.openUrlExternally(link)
        }
    }

    tools: commonTools
}
