#ifndef TABLEVIEWMODEL_H
#define TABLEVIEWMODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QModelIndex>
#include <QStringList>
#include <QFileSystemWatcher>

#include <fileio.h>

class TableViewModel : public QAbstractTableModel
{
    Q_OBJECT

    Q_PROPERTY(QStringList userRoleNames READ userRoleNames NOTIFY userRoleNamesChanged )


    enum Role {
        Role_0=Qt::UserRole + 1,
        Role_1,
        Role_2,
        Role_3,
        Role_4,
        Role_5,
        Role_6,
        Role_7,
        Role_8,
        Role_9,
        Role_10,
        Role_11,
        Role_12,
        Role_13,
        Role_14,
        Role_15,
        Role_16
    };

public:
    explicit TableViewModel( QObject *parent = 0 );
    ~TableViewModel( void );


    // Standart, MUST be here
    QHash<int, QByteArray> roleNames() const;
    int rowCount(const QModelIndex& parent ) const;
    int columnCount(const QModelIndex& parent ) const;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole ) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole ) const;
    //bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::DisplayRole);

    // User created
    QString keyAt(int offset) const;
    void setFileIO( FileIO* file_io );
    void setFileSystemWatcher( QFileSystemWatcher* fileWatcher );
    void setFilePath( QString filePath );
    void processData( void );
    QStringList userRoleNames( void );
    //void updateModel1( );

signals:
    QStringList userRoleNamesChanged();

public slots:
    Q_INVOKABLE void updateModel( QString file );

private:
    //QMap<QString, QString> m_map;
    QMap<QString, QStringList> m_map;
    QStringList m_roleNames;
    int m_processorNumber;
    FileIO* m_file_io;
    QString m_filePath;
    QFileSystemWatcher* m_fileWatcher;
};

#endif // TABLEVIEWMODEL_H
