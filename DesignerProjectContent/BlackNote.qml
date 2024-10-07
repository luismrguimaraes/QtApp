import QtQuick 6.7
import QtQuick3D 6.7
import MyModule

Model {
                    id: blackNote
                    source: "#Cube"
                    materials: black
                    instancing: KeyboardInstancing{
                        isWhiteNote: false
                    }
                    Node {
                        id: __materialLibrary__
                    }
                }
