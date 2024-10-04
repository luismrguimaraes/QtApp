

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

Rectangle {
    id: rectangle
    width: 1920
    height: 1080
    opacity: 1
    visible: true

    color: Constants.backgroundColor
    layer.enabled: false
    clip: false

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
                eulerRotation.y: 207
                castsShadow: true
                eulerRotation.z: 0
                eulerRotation.x: -36
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
                eulerRotation.x: -90
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
                scale.z: 50
                scale.y: 50
                scale.x: 50
                eulerRotation.x: -90
                materials: newMaterial
            }

            MidiNoteModel {
                id: midiNoteModel
                x: 0
                y: 50
                z: 0
                materials: defaultMaterial
            }
        }
    }

    Item {
        id: __materialLibrary__
        PrincipledMaterial {
            id: defaultMaterial
            baseColor: "#4f5ce6"
            objectName: "Default Material"
        }

        PrincipledMaterial {
            id: newMaterial
            baseColor: "#524e16"
            objectName: "New Material"
        }
    }

    Slider {
        id: sceneCameraYSlider
        value: sceneCamera.y
        live: true
        to: 4000
        from: 1
        stepSize: 1
        onValueChanged: sceneCamera.y = value
    }
}

/*##^##
Designer {
    D{i:0}D{i:1;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}D{i:2;invisible:true}D{i:3;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}
}
##^##*/

