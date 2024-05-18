#include "Reteta.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>

Reteta::Reteta(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // Dacă nu se poate deschide fișierul, afișăm un mesaj de eroare
        qDebug() << "Eroare la deschiderea fișierului" << filePath;
        return;
    }

    QTextStream in(&file);
    // Citim numele rețetei
    if (!in.atEnd()) {
        nume = in.readLine();
    }
    // Citim modul de preparare
    if (!in.atEnd()) {
        modDePreparare = in.readLine();
    }
    // Citim calea către fișierul imagine
    if (!in.atEnd()) {
        pozaPath = in.readLine();
    }
    // Citim lista de ingrediente
    while (!in.atEnd()) {
        ingrediente.append(in.readLine());
    }
    file.close();
}
