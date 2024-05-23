#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <QString>

class Ingredient {
private:
    int ID;
    QString nume;
    double cantitate;
    QString unitateDeMasura;

public:
    // Constructor
    Ingredient(int id, const QString& nume, double cantitate, const QString& unitateDeMasura)
        : ID(id), nume(nume), cantitate(cantitate), unitateDeMasura(unitateDeMasura) {}

    // Getters
    int getID() const { return ID; }
    QString getNume() const { return nume; }
    double getCantitate() const { return cantitate; }
    QString getUnitateDeMasura() const { return unitateDeMasura; }

    // Setters
    void setID(int id) { ID = id; }
    void setNume(const QString& nume) { this->nume = nume; }
    void setCantitate(double cantitate) { this->cantitate = cantitate; }
    void setUnitateDeMasura(const QString& unitateDeMasura) { this->unitateDeMasura = unitateDeMasura; }
    void incrementID() {ID++;}
};

#endif // INGREDIENT_H
