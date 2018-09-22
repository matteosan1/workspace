//#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

#include <QFile>
#include <QByteArray>

#include <QDebug>

int main()
{
    //QCoreApplication app( argc, argv );

    // Set up database
    QString dbName("/home/sani/team_prova.sqlite" );
    QSqlDatabase db = QSqlDatabase::addDatabase( "QSQLITE", "MyConnection" );
    db.setDatabaseName( dbName );
    db.open();
    QSqlQuery query(db);

    // Alternatively, load an image file directly into a QByteArray
    QFile file("/home/sani/maglia_a.c.uga.png");
    if (!file.open(QIODevice::ReadOnly))
        return 0;
    QByteArray inByteArray = file.readAll();


    query.prepare( "UPDATE teamName SET shirt=? WHERE name = \"A.C. UGA\"" );
    query.bindValue( 0, inByteArray );
    if (!query.exec()) {
        qDebug() << "ERROR: " << query.lastError().text();
    }
    db.close();

    //return app.exec();
}

