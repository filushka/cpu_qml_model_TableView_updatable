/*
This program displays content of the /proc/cpuinfo file


Copyright (C) <2016>  <Sergey Tsybanov>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


import QtQuick 2.4
import QtQuick.Window 2.2
import QtQuick.Controls 1.4


Rectangle
{
    id: root
    width: 1050
    height: 650
    onScaleChanged: tableView.scale

    Component
    {
        id: columnComponent
        TableViewColumn{width: 100 }
    }

    TableView {
        id: tableView
        anchors.fill: root
        anchors.topMargin: 10
        anchors.bottomMargin: 10
        anchors.leftMargin: 10
        anchors.rightMargin: 10


        resources:
        {
            var roleList = myModel.userRoleNames
            var temp = []
            for(var i=0; i<roleList.length; i++)
            {
                var role  = roleList[i]
                temp.push(columnComponent.createObject(tableView, { "role": role, "title": role}))
            }
            return temp
        }

        model: myModel;

        Connections {
            target: tableView.model
            onDataChanged: {

                console.log("Changing data")
                var count = tableView.columnCount
                //console.log( "count =", count )

                while( tableView.columnCount )
                {
                    //console.log( "tableView.columnCount-1=", tableView.columnCount-1 )

                    tableView.removeColumn(tableView.columnCount-1);
                }

                var roleList = myModel.userRoleNames
                for(var i=0; i<roleList.length; i++)
                {
                    //console.log( "i=", i )
                    var role  = roleList[i]
                    //console.log( "role = ", role )

                    tableView.addColumn( columnComponent.createObject(tableView, { "role": role, "title": role}) );
                }

            }
        }


        Component.onCompleted: {
            console.warn("warn completed")
            console.log("log completed")
            console.log( myModel.columnCount())
            console.log( myModel.rowCount())
            console.log(myModel.userRoleNames )

            tableView.resizeColumnsToContents()
        }

    }

}
