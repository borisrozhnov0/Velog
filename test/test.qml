import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Shapes 1.15

Item {
    width: 600
    height: 200
    Row {
        spacing: 18
        anchors.centerIn: parent

        Rectangle {
            width: 100
            height: 100
            radius: width/2
            color: "blue"
        }

     
        Rectangle {
            width: 100
            height: 100
            radius: width/2
            color: "transparent"
            border {
                color: "#30D5C8"  
                width: 3
            }
        }

        Shape {
            width: 100
            height: 100
            
            ShapePath {
                fillColor: "transparent"
                strokeColor: "black"
                strokeWidth: 5
                
                PathMove { x: 50; y: 0 }
                PathLine { x: 100; y: 100 }
                PathLine { x: 0; y: 100 }
                PathLine { x: 50; y: 0 }
            }
        }

        Rectangle {
            width: 100
            height: 60
            color: "black"
            y: 20
        }
        Shape {
            ShapePath {
                strokeColor: "blue"
                strokeWidth: 4
                PathMove { x: 0; y: 0 }
                PathLine { x: 0; y: 100 }
            }
        }
        Shape {
            ShapePath {
                strokeColor: "green"
                strokeWidth: 4
                PathMove { x: 0; y: 0 }
                PathLine { x: 0; y: 100 }
            }
        }
        Shape {
            ShapePath {
                strokeColor: "red"
                strokeWidth: 4
                PathMove { x: 0; y: 0 }
                PathLine { x: 0; y: 100 }
            }
        }
        Shape {
            ShapePath {
                strokeColor: "black"
                strokeWidth: 4
                PathMove { x: 0; y: 0 }
                PathLine { x: 0; y: 100 }
            }
        }
    }
}
