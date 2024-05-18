#ifndef RETETA_H
#define RETETA_H

#include <QString>
#include <QList>

class Reteta {
public:
    // Constructor cu fișier formatat
    Reteta(const QString& filePath);

    // Metode pentru a accesa atributele
    QString getNume() const { return nume; }
    QList<QString> getIngrediente() const { return ingrediente; }
    QString getModDePreparare() const { return modDePreparare; }
    QString getPozaPath() const { return pozaPath; }

private:
    // Atributele clasei
    QString nume;
    QList<QString> ingrediente;
    QString modDePreparare;
    QString pozaPath; // Calea către fișierul imagine
};

#endif // RETETA_H
