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


#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QtQml>
#include <QDebug>

#include "fileio.h"
#include "tableviewmodel.h"

int main(int argc, char *argv[])
{
    if( !QResource::registerResource("qml.rcc") )
        qDebug() << "Error registering resources";
    else
        qDebug() << "resources OK";

    QGuiApplication app(argc, argv);

    QString filePath = "/proc/cpuinfo";

    FileIO* file_io = new FileIO();
    file_io->setSource( filePath );

    TableViewModel model;
    model.setFileIO( file_io );

    QFileSystemWatcher fileWatcher;
    fileWatcher.addPath( filePath );

    model.setFileSystemWatcher( &fileWatcher );
    model.setFilePath( filePath );

    file_io->moveToThread( app.thread());
    model.moveToThread(app.thread());
    fileWatcher.moveToThread( app.thread() );

    QObject::connect( &fileWatcher, &QFileSystemWatcher::fileChanged, &model, &TableViewModel::updateModel );

    model.processData();

    QQuickView view;
    QQmlContext* ctxt = view.rootContext();

    ctxt->setContextProperty("myModel", &model);

    view.setSource( QUrl ("qrc:/main.qml") );
    view.setMinimumSize( QSize( 1000, 600 ) );
    view.setResizeMode(QQuickView::ResizeMode::SizeRootObjectToView);
    view.show();
    return app.exec();

}


//Q_DECL_EXPORT int main(int argc, char *argv[])


