#include <QCoreApplication>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QTime>
#include <QSqlError>
#include <QtDebug>
#include <QSqlDriver>
#include <QSqlRecord>
#pragma execution_character_set("utf-8")
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextCodec::setCodecForLocale(QTextCodec::codecForLocale());
    QSqlDatabase db =QSqlDatabase::addDatabase("QSQLITE");
//    db.setHostName("easybook-3313b0");          //设置数据库主机名
//    db.setDatabaseName("qtLOL.db");              //设置数据库名
//    db.setUserName("zhouhejun");                //设置数据库用户名
//    db.setPassword("123456");                   //设置数据库密码
//    db.open();                             		//打开连接

    db.setDatabaseName("D:\\study\\QT_Study\\Qt\\QT5Develop and Example\\Code Example\\CH13\\CH1301\\build-QSQLiteEx-Desktop_Qt_5_9_2_MinGW_32bit-Debug\\qtLOL.db");
//    //创建数据库表
//    QSqlQuery query;
//    bool success=query.exec("create table automobil(id int primary key,attribute varchar,type varchar,kind varchar,nation int,carnumber int,elevaltor int,distance int,oil int,temperature int)");
//    if(success)
//        qDebug()<<QObject::tr("数据库表创建成功！\n");
//    else
//        qDebug()<<QObject::tr("数据库表创建失败！\n");
    bool ok = db.open();
    if(ok)
    {
        qDebug()<<QObject::tr("打开数据库成功！" );
    }
    //查询
    QSqlQuery query;
    query.exec("select * from automobil");

    int max_id = 0;
    query.exec("select max(id) from automobil");

    query.next();

    max_id = query.value(0).toInt();


    QSqlRecord rec = query.record();
    qDebug() << QObject::tr("automobil表字段数：" )<< rec.count();
    //插入记录
    QTime t;
    t.start();
    query.prepare("insert into automobil values(?,?,?,?,?,?,?,?,?,?)");
    bool success=false;
    int startnum=max_id+1;
    int insertnum=1;
    long records=startnum+insertnum;

    for(int i=startnum;i<records;i++)//800 900
    {
        query.bindValue(0,i);
        query.bindValue(1,"567");
        query.bindValue(2,"轿车");
        query.bindValue(3,"富康");
        query.bindValue(4,1);
        query.bindValue(5,1);
        query.bindValue(6,300);
        query.bindValue(7,200000);
        query.bindValue(8,52);
        query.bindValue(9,100);

        success=query.exec();
        if(!success)
        {
            QSqlError lastError=query.lastError();
            qDebug()<<lastError.driverText()<<QString(QObject::tr("插入失败"));
        }
    }
    qDebug()<<QObject::tr("插入 %1 条记录，耗时：%2 ms").arg(insertnum).arg(t.elapsed());

    //排序
    t.restart();
    success=query.exec("select * from automobil order by id desc");
    if(success)
        qDebug()<<QObject::tr("排序 %1 条记录，耗时：%2 ms").arg(insertnum).arg(t.elapsed());
    else
        qDebug()<<QObject::tr("排序失败！");

    //更新记录
    t.restart();
    for(int i=startnum;i<records;i++)
    {
       query.clear();
       query.prepare(QString("update automobil set attribute=?,type=?,"
                             "kind=?,nation=?,"
                             "carnumber=?,elevaltor=?,"
                             "distance=?,oil=?,"
                             "temperature=? where id=%1").arg(i));

       query.bindValue(0,"北京");
       query.bindValue(1,"上海");
       query.bindValue(2,"广州");
       query.bindValue(3,100);
       query.bindValue(4,10000);
       query.bindValue(5,300);
       query.bindValue(6,200000);
       query.bindValue(7,52);
       query.bindValue(8,100);

       success=query.exec();
       if(!success)
       {
           QSqlError lastError=query.lastError();
           qDebug()<<lastError.driverText()<<QString(QObject::tr("更新失败"));
       }
    }
    qDebug()<<QObject::tr("更新 %1 条记录，耗时：%2 ms").arg(insertnum).arg(t.elapsed());

    //删除
    t.restart();
    if(query.exec("delete from automobil where id=0"))
    qDebug()<<QObject::tr("删除一条记录，耗时：%1 ms").arg(t.elapsed());
    db.close();
    return 0;
}
