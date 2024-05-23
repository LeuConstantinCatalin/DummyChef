#include <QApplication>
#include <QFile>
#include <QTextStream>

#include"signfactory.h"

void writeTextToFile(const QString &filePath, const QString &content) {
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << content;
        file.close();
        qDebug() << "Conținutul a fost scris în fișierul text cu succes.";
    } else {
        qDebug() << "Nu am reușit să deschidem fișierul text pentru scriere.";
    }
}

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   SignFactory::createSign(" ","LOGIN").show();


    return a.exec();
}

