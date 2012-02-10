// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1
import com.nokia.meego 1.0
import org.meetuner 1.0
import "components"

Page {
    id: settingsPage
    tools: backTools

    PageHeader {
        id: header
        text: qsTr("Settings")
    }
}
