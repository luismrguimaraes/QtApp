

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

Rectangle {
    id: rectangle
    width: 1920
    height: 1080
    opacity: 1
    visible: true

    color: Constants.backgroundColor
    layer.enabled: false
    clip: false

    PhysicsWorld{
        scene: view3D.scene
    }
    View3D
    {
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

            PointLight {
                id: pointLight
                x: -0
                y: 900
                visible: false
                brightness: 100
                castsShadow: true
                z: -600
            }

            PerspectiveCamera {
                id: sceneCamera
                x: -0
                y: 1500
                visible: true
                fieldOfViewOrientation: PerspectiveCamera.Horizontal
                pivot.x: 0
                pivot.z: 0
                pivot.y: 0
                fieldOfView: 60
                clipFar: 10000
                eulerRotation.x: -85
                eulerRotation.z: 0
                eulerRotation.y: 180
                z: -300
            }

            OrthographicCamera {
                id: orthographicCamera
                y: 1500
                visible: true
                eulerRotation.x: -55
                eulerRotation.y: 180
                z: -1000
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


            MidiNoteModel {
                id: midiNotes
                x: 0
                y: 50
                visible: true
                z: 0
            }
/*
            WhiteNote {
                id: whiteNotes
                visible: true
                materials: white
            }

            BlackNote {
                id: blackNotes
                materials: black
            }
            */
            Keyboard{
                id: sceneKeyboard
            }
        }
    }

    Item {
        id: __materialLibrary__
        PrincipledMaterial {
            id: defaultMaterial
            emissiveFactor.y: 0.11
            emissiveFactor.z: 0.19
            metalness: 0
            baseColor: "#59ffeb"
            objectName: "Default Material"
        }

        PrincipledMaterial {
            id: newMaterial
            baseColor: "#524e16"
            objectName: "New Material"
        }

        PrincipledMaterial {
            id: white
            baseColor: "#ffe6b5"
            roughness: 0.4
            metalness: 0.1
            objectName: "White"
        }

        PrincipledMaterial {
            id: black
            baseColor: "#322e27"
            roughness: 0.4
            objectName: "Black"
            metalness: 0.1
        }
    }

    Text{
        id: camParamsText
        text: qsTr("Camera Parameters")
        font.pixelSize: 30
        color: "white"
    }

    Slider {
        id: sceneCameraYSlider
        value: sceneCamera.y
        live: true
        to: 4000
        from: 1
        stepSize: 1
        onValueChanged: sceneCamera.y = value
        anchors.top: camParamsText.bottom
        Label{
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
        Label{
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
        to: -500
        from: -100
        stepSize: 1
        onValueChanged: sceneCamera.z = value
        anchors.top: sceneCameraXRotSlider.bottom
        Label{
            anchors.left: sceneCameraZSlider.right
            text: qsTr("Z")
            font.pixelSize: 30
            color: "white"
        }
    }
}

/*##^##
Designer {
    D{i:0;matPrevEnvDoc:"SkyBox";matPrevEnvValueDoc:"preview_studio"}D{i:1;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}
D{i:2;invisible:true}D{i:3;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}D{i:10;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}
D{i:11;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}
}
##^##*/

