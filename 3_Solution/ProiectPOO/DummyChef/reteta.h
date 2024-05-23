#ifndef RETETA_H
#define RETETA_H

#include <QString>
#include <QList>
#include <QDebug>
#include "ingredient.h"

class Reteta {
public:
    // Constructor cu fișier formatat
    //Reteta(const QString& filePath);
    Reteta(const QString& text);
    Reteta() : nume("-"), modDePreparare("-"), pozaPath("-") {ingrediente.clear();}
    // Metode pentru a accesa atributele
    QString getNume() const { return nume; }
    QList<Ingredient> getIngrediente() const { return ingrediente; }
    QString getModDePreparare() const { return modDePreparare; }
    QString getPozaPath() const { return pozaPath; }

    void setNume(const QString& newName) {
        if (!newName.isNull() && !newName.isEmpty()) {
            nume = newName;
        } else {
            qDebug() << "setNumeErr";
        }
    }

    void setIngrediente(const QList<Ingredient>& newIngrediente) {
        ingrediente.clear(); // Șterge lista actuală de ingrediente
        for (const Ingredient& ingredient : newIngrediente) {
            ingrediente.append(ingredient); // Adaugă fiecare ingredient din lista nouă
        }
    }

    void setModDePreparare(const QString& newPreparare) {
        if (!newPreparare.isNull()) {
            modDePreparare = newPreparare;
        } else {
            qDebug() << "setNPreparareErr";
        }
    }

    void setPozaPath(const QString& newPath) {
        if (!newPath.isNull()) {
            pozaPath = newPath;
        } else {
            qDebug() << "setPozaErr";
        }
    }

private:
    // Atributele clasei
    QString nume;
    QList<Ingredient> ingrediente;
    QString modDePreparare;
    QString pozaPath;
};

#endif // RETETA_H
