#ifndef FILEIO_H
#define FILEIO_H

#include <QObject>
#include <QFileSystemWatcher>

class FileIO : public QObject
{
    Q_OBJECT

public:
    Q_PROPERTY(QString source
               READ source
               WRITE setSource
               NOTIFY sourceChanged)

    explicit FileIO(QObject *parent = 0);

    Q_INVOKABLE QStringList read();
    Q_INVOKABLE bool write(const QString& data);
    Q_INVOKABLE quint32 line_number( void );

    QString source()
    {
        return mSource;
    };

public slots:
    void setSource(const QString& source)
    {
        mSource = source;
    };

signals:
    void sourceChanged(const QString& source);
    void error(const QString& msg);
    void fileContentChanged( QString file );

private:
    QString mSource;
    quint32 m_line_numbers;
    QFileSystemWatcher m_fileWatcher;
};

#endif // FILEIO_H
