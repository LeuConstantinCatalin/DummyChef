#include "reteta.h"
#include "ingredient.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QRegularExpression>

Reteta::Reteta(const QString& text) {

    QRegularExpression re("^\\n+|\\n+$");

    // Replace leading and trailing newlines with an empty string
    QString data = text;
    data =  data.replace(re, "");

    QStringList lines = data.split('\n');

    // Extract name, instructions, and image path
    if (!lines.isEmpty()) {
        nume = lines.takeFirst();
    }
    modDePreparare = lines.takeFirst();
    if (!lines.isEmpty()) {
        pozaPath = lines.takeFirst();
    }

    // Extract ingredients
    foreach(QString line, lines) {
        QStringList parts = line.split(' ');
        if (parts.size() == 3) {
            QString ingredientName = parts[0];
            double quantity = parts[1].toDouble();
            QString unitOfMeasure = parts[2];
            ingrediente.append(Ingredient(0, ingredientName, quantity, unitOfMeasure));
        }
    }
}
/*
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
        QString numeIngredient = in.readLine();
        Ingredient ingredient(0,numeIngredient,0,"u.m");
        ingrediente.push_back(ingredient);
    }
    file.close();
}
*/
