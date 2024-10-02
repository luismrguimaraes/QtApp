

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
                x: -0
                y: 168.706
                castsShadow: true
                z: 0
            }

            PerspectiveCamera {
                id: sceneCamera
                x: -0
                y: 139.967
                eulerRotation.x: -20
                eulerRotation.z: 0
                eulerRotation.y: 0
                z: 280.354
            }

            Model {
                id: cone
                x: -129.312
                y: 8.804
                visible: true
                source: "#Cone"
                z: -103.70641
                materials: defaultMaterial
            }

            PointLight {
                id: pointLight
                x: -0
                y: 162.642
                castsShadow: true
                z: 100.99
            }

            Model {
                id: plane
                x: -88.194
                y: -0.566
                source: "#Rectangle"
                pickable: true
                receivesReflections: false
                castsReflections: true
                scale.z: 50
                scale.y: 50
                scale.x: 50
                eulerRotation.x: -90
                z: 7.60921
                materials: newMaterial
            }

            MyCubeModel {
                id: myCubeModel
                y: 79.205
                z: 0
                materials: defaultMaterial
            }
        }
    }

    Item {
        id: __materialLibrary__
        PrincipledMaterial {
            id: defaultMaterial
            baseColor: "#4554ee"
            objectName: "Default Material"
        }

        PrincipledMaterial {
            id: newMaterial
            baseColor: "#27d96a"
            objectName: "New Material"
        }
    }
}

/*##^##
Designer {
    D{i:0}D{i:1;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}D{i:2;invisible:true}D{i:3;cameraSpeed3d:25;cameraSpeed3dMultiplier:1}
}
##^##*/

