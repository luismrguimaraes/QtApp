

/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/
import QtQuick 6.7
import QtQuick.Controls 6.7
import QtQuick3D 6.7
import QtQuick3D.Effects 6.7
import DesignerProject
import QtQuick3D.Physics

import MyModule

Rectangle {
    id: rectangle
    width: 1280
    height: 720
    opacity: 1
    visible: true

    color: Constants.backgroundColor
    layer.enabled: false
    clip: false

    PhysicsWorld {
        scene: view3D.scene
    }
    View3D {
        id: view3D
        anchors.fill: parent
        environment: sceneEnvironment
        importScene: scene

        SceneEnvironment {
            id: sceneEnvironment
            skyboxBlurAmount: 0.6
            backgroundMode: SceneEnvironment.SkyBox
            depthTestEnabled: true
            aoEnabled: false
            antialiasingMode: SceneEnvironment.MSAA
            antialiasingQuality: SceneEnvironment.High
        }

        Node {
            id: scene
            DirectionalLight {
                id: directionalLight
                x: 0
                y: 0
                opacity: 1
                visible: true
                shadowFilter: 15
                shadowFactor: 5
                shadowMapQuality: Light.ShadowMapQualityMedium
                eulerRotation.y: -131.88103
                castsShadow: true
                eulerRotation.z: -29.36037
                eulerRotation.x: -62.56247
                brightness: 1
                z: 0
            }

            PerspectiveCamera {
                id: sceneCamera
                x: -0
                y: 6000
                visible: true
                fieldOfViewOrientation: PerspectiveCamera.Horizontal
                pivot.x: 0
                pivot.z: 0
                pivot.y: 0
                fieldOfView: 10
                clipFar: 10000
                eulerRotation.x: -93
                eulerRotation.z: 0
                eulerRotation.y: 180
                z: -10
            }

            Model {
                id: plane
                source: "#Rectangle"
                scale.z: 60
                scale.y: 60
                scale.x: 60
                eulerRotation.x: -90
                materials: newMaterial
            }


            Game{
                id: game
            }
        }
    }

    Item {
        id: __materialLibrary__
        PrincipledMaterial {
            id: defaultMaterial
            //emissiveFactor.y: 0.11
            //emissiveFactor.z: 0.19
            metalness: 0
            baseColor: "#61ff59"
            objectName: "Default Material"
        }

        PrincipledMaterial {
            id: newMaterial
            roughness: 0.8
            transmissionFactor: 0
            clearcoatAmount: 0
            baseColor: "#3b3a0f"
            objectName: "New Material"
        }

        PrincipledMaterial {
            id: red
            //emissiveFactor.y: 0.11
            //emissiveFactor.z: 0.19
            metalness: 0
            baseColor: "#ff6159"
            objectName: "Red"
        }

        PrincipledMaterial {
            id: white
            baseColor: "#ffe6b5"
            roughness: 0.4
            metalness: 0.1
            objectName: "White"
        }

        PrincipledMaterial {
            id: white2
            baseColor: "#ffe6b5"
            roughness: 0.4
            metalness: 0.1
            opacity: 0.2
            objectName: "White"
        }

        PrincipledMaterial {
            id: black
            baseColor: "#322e27"
            roughness: 0.4
            objectName: "Black"
            metalness: 0.1
        }

        PrincipledMaterial {
            id: black2
            baseColor: "#606060"
            roughness: 0.4
            opacity: 0.8
            objectName: "Black"
            metalness: 0.1
        }
    }

    // Camera Params
    Text {
        id: camParamsText
        text: qsTr("Camera Parameters")
        font.pixelSize: 30
        color: "white"
    }

    Slider {
        id: sceneCameraYSlider
        value: sceneCamera.y
        live: true
        to: 10000
        from: 1
        stepSize: 1
        onValueChanged: sceneCamera.y = value
        anchors.top: camParamsText.bottom
        Label {
            anchors.left: sceneCameraYSlider.right
            text: qsTr("Y")
            font.pixelSize: 30
            color: "white"
        }
    }
    Slider {
        id: sceneCameraXRotSlider
        value: sceneCamera.eulerRotation.x
        live: true
        to: -70
        from: -100
        stepSize: 1
        onValueChanged: sceneCamera.eulerRotation.x = value
        anchors.top: sceneCameraYSlider.bottom
        Label {
            anchors.left: sceneCameraXRotSlider.right
            text: qsTr("XRot")
            font.pixelSize: 30
            color: "white"
        }
    }
    Slider {
        id: sceneCameraZSlider
        value: sceneCamera.z
        live: true
        to: 500
        from: -1000
        stepSize: 1
        onValueChanged: sceneCamera.z = value
        anchors.top: sceneCameraXRotSlider.bottom
        Label {
            anchors.left: sceneCameraZSlider.right
            text: qsTr("Z")
            font.pixelSize: 30
            color: "white"
        }
    }
    Slider {
        id: sceneCameraFOV
        value: sceneCamera.fieldOfView
        live: true
        to: 0
        from: 100
        stepSize: 1
        onValueChanged: sceneCamera.fieldOfView = value
        anchors.top: sceneCameraZSlider.bottom
        Label {
            anchors.left: sceneCameraFOV.right
            text: qsTr("FOV")
            font.pixelSize: 30
            color: "white"
        }
    }

    // Game stuff
    TextField {
        id: textField
        placeholderText: qsTr("path")
        text: "test.mid"
        anchors.right: rectangle.right
    }
    Button{
        id: spawnButton
        anchors.top: textField.bottom
        anchors.right: rectangle.right
        text: qsTr("Spawn")
        onClicked: game.readFile(":/midi/" + textField.text)
    }
    Button{
        id: startStopButton
        anchors.top: spawnButton.bottom
        anchors.right: rectangle.right
        text: qsTr("Start/Stop")
        onClicked: game.startStop()
    }
    Label {
        id: scoreLabel
        width: rectangle.width
        property real score: game.score
        horizontalAlignment: Text.AlignHCenter
        text: score.toFixed(2)
        font.pointSize: 50
        color: "white"
    }
    Label {
        id: gameSpeedSliderLabel
        anchors.top: sceneCameraFOV.bottom
        text: qsTr("Game Speed")
        font.pixelSize: 30
        color: "white"
    }
    Slider {
        id: gameSpeedSlider
        value: game.interval
        live: true
        to: 1
        from: 50
        stepSize: 1
        onValueChanged: game.interval = value
        anchors.top: gameSpeedSliderLabel.bottom

    }
}

/*##^##
Designer {
    D{i:0;matPrevEnvDoc:"SkyBox";matPrevEnvValueDoc:"preview_studio";matPrevModelDoc:"#Sphere"}
D{i:4;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}
}
##^##*/

