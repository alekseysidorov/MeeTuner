// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 1.1

Item {
    id: root

    width: parent ? parent.width : 200
    height: 100

    ListModel {
        id: range

        property real minimumValue: -50
        property real maximumValue: 50
        property real step: 5

        Component.onCompleted: {
            for (var i = minimumValue; i <= maximumValue; i += step) {
                range.append({"value":i});
            }
        }
    }

    Row {
        id: row
        anchors.centerIn: parent
        spacing: 10

        Repeater {
            id: repeater
            model: range
            delegate: Rectangle {
                id: bar

                property real __deviation: Math.abs(modelData / 100)
                property bool __current: noteAnalyzer.deviation > modelData - range.step &&
                                         noteAnalyzer.deviation < modelData + range.step &&
                                         noteAnalyzer.nearestNote.length

                color: "gray"
                width: root.width / range.count - row.spacing
                height: root.height * (1 - __deviation)
                anchors.verticalCenter: parent.verticalCenter

                opacity: 1 - __deviation

                states: [
                    State {
                        when: bar.__current
                        name: "active"
                        PropertyChanges {
                            target: bar
                            color: modelData === 0 ? "#65A4F2" : "#F22727"
                        }
                    },
                    State {
                        when: !bar.__current
                        name: "passive"
                    }
                ]

                transitions: [
                    Transition {
                        from: "passive"
                        to: "active"
                        reversible: true

                        ColorAnimation {
                            duration: 300
                        }
                    }
                ]
            }
        }
    }
}
