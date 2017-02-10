#include "tableviewmodel.h"

#include <QDebug>

TableViewModel::TableViewModel(QObject *parent)
    : QAbstractTableModel(parent)
{

}


TableViewModel::~TableViewModel( void )
{

}

QHash<int, QByteArray> TableViewModel::roleNames() const
{
    QHash<int, QByteArray> roles;

    roles[Role_0] = "title";
    roles[Role_1] = "cpu 1";
    roles[Role_2] = "cpu 2";
    roles[Role_3] = "cpu 3";
    roles[Role_4] = "cpu 4";
    roles[Role_5] = "cpu 5";
    roles[Role_6] = "cpu 6";
    roles[Role_7] = "cpu 7";
    roles[Role_8] = "cpu 8";
    roles[Role_9] = "cpu 9";
    roles[Role_10] = "cpu 10";
    roles[Role_11] = "cpu 11";
    roles[Role_12] = "cpu 12";
    roles[Role_13] = "cpu 13";
    roles[Role_14] = "cpu 14";
    roles[Role_15] = "cpu 15";
    roles[Role_16] = "cpu 16";

    return roles;
}

QString TableViewModel::keyAt(int offset) const
{
    return (m_map.begin() + offset).key();
}

void TableViewModel::setFileIO( FileIO* file_io )
{
    m_file_io = file_io;

}


void TableViewModel::setFileSystemWatcher( QFileSystemWatcher* fileWatcher )
{
    m_fileWatcher = fileWatcher;
}

void TableViewModel::setFilePath( QString filePath )
{
    m_filePath = filePath;
}

int TableViewModel::rowCount(const QModelIndex& parent ) const
{
    return m_map.count();
}

int TableViewModel::columnCount(const QModelIndex& parent ) const
{
    return 9;
}


QVariant TableViewModel::headerData(int section, Qt::Orientation orientation, int role ) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if( orientation == Qt::Vertical )
        return QVariant( section );

    if( orientation == Qt::Horizontal )
        return QVariant( keyAt(section) );
}


/*
void CppModelItem::setData(const QVariant &value, int role)
{
if( role == NameRole )
{
m_name = value.toString();

    this->model()->dataChanged(this->index(), this->index());
}
}
*/

/*
bool TableViewModel::setData(const QModelIndex &index, const QVariant &value, int role )
{
    //if (index.isValid() ){

        //this->updateModel1();
        emit dataChanged(index, index);

        return true;
    //}
    //return false;
}
*/



QVariant TableViewModel::data(const QModelIndex & index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (role == Qt::TextAlignmentRole) {
        return int(Qt::AlignRight | Qt::AlignVCenter);
    } else { //if (role == Qt::DisplayRole) {
        int row = index.row();
        int column = index.column();


        switch(role)
        {
            case Role_0:
                return QVariant( keyAt( row ) );
            case Role_1:
                return QVariant( m_map.value( keyAt( row ) ).at(0) );
            case Role_2:
                return QVariant( m_map.value( keyAt( row ) ).at(1) );
            case Role_3:
                return QVariant( m_map.value( keyAt( row ) ).at(2) );
            case Role_4:
                return QVariant( m_map.value( keyAt( row ) ).at(3) );
            case Role_5:
                return QVariant( m_map.value( keyAt( row ) ).at(4) );
            case Role_6:
                return QVariant( m_map.value( keyAt( row ) ).at(5) );
            case Role_7:
                return QVariant( m_map.value( keyAt( row ) ).at(6) );
            case Role_8:
                return QVariant( m_map.value( keyAt( row ) ).at(7) );
            case Role_9:
                return QVariant( m_map.value( keyAt( row ) ).at(8) );
            case Role_10:
                return QVariant( m_map.value( keyAt( row ) ).at(9) );
            case Role_11:
                return QVariant( m_map.value( keyAt( row ) ).at(10) );
            case Role_12:
                return QVariant( m_map.value( keyAt( row ) ).at(11) );
            case Role_13:
                return QVariant( m_map.value( keyAt( row ) ).at(12) );
            case Role_14:
                return QVariant( m_map.value( keyAt( row ) ).at(13) );
            case Role_15:
                return QVariant( m_map.value( keyAt( row ) ).at(14) );
            case Role_16:
                return QVariant( m_map.value( keyAt( row ) ).at(15) );
            }
    }

    return QVariant();
}

void TableViewModel::processData( void )
{
    QStringList dataList = m_file_io->read();
    dataList.removeAll( QString( "    " ) );

    // Clear all
    m_roleNames.clear();
    m_map.clear();

    // Get number of processors
    m_processorNumber = 0;
    int cnt = dataList.count();


    for( int i=0; i < cnt; i++ )
        if( dataList.at(i).contains("processor") )
            ++m_processorNumber;


    m_roleNames.append( "title" );

    for (int i = 1; i <= m_processorNumber; i++ )
    {
        m_roleNames.append( QString( "cpu " ) + QString::number(i));
    }

    QString var;

    foreach( var, dataList )
    {
        var.remove("\t");
        QStringList tmp = var.split( ":" );

        if( m_map.contains(tmp.at(0) ))
        {
            QStringList strList = m_map.value( tmp.at(0) );

            if( tmp.count() == 2 )
                strList.append( tmp.at(1) );
            if( tmp.count() == 1 )
                strList.append("");

            m_map[ tmp.at(0) ] = strList;
        }
        else
        {
            if( tmp.count() == 2 )
            {
                QStringList lst;
                lst.append( tmp.at(1) );
                m_map.insert( tmp.at(0), lst );
            }

            if( tmp.count() == 1 )
            {
                QStringList lst;
                lst.append( "" );
                m_map.insert( tmp.at(0), lst );
            }
        }
    }
}


QStringList TableViewModel::userRoleNames()
{
    return m_roleNames;
}


void TableViewModel::updateModel( QString file )
{
    qDebug() << Q_FUNC_INFO  << file;

    m_filePath = file;

    processData( );
    m_fileWatcher->addPath( m_filePath );

    emit dataChanged( QModelIndex(), QModelIndex());
}

