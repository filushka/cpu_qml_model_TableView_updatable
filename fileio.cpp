#include "fileio.h"
#include <QFile>
#include <QTextStream>

FileIO::FileIO(QObject *parent) :
    QObject(parent)
{
    m_line_numbers =0;
}

QStringList FileIO::read()
{
    if (mSource.isEmpty()){
        emit error("source is empty");
        return QStringList();
    }

    QFile file(mSource);
    QStringList fileContent;
    if ( file.open(QIODevice::ReadOnly) ) {
        QString line;
        QTextStream t( &file );
        do {
            line = t.readLine();
            fileContent.append( QString("    " ) + line );
            m_line_numbers+=1;
         } while (!line.isNull());

        file.close();
    } else {
        emit error("Unable to open the file");
        return QStringList();
    }
    return fileContent;
}

bool FileIO::write(const QString& data)
{
    if (mSource.isEmpty())
        return false;

    QFile file(mSource);
    if (!file.open(QFile::WriteOnly | QFile::Truncate))
        return false;

    QTextStream out(&file);
    out << data;

    file.close();

    return true;
}

quint32 FileIO::line_number( void )
{
    return m_line_numbers;
}
