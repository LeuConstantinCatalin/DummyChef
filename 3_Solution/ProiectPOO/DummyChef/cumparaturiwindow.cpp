#include "CumparaturiWindow.h"
#include "ingredient.h"
#include "serverconector.h"
#include <QHBoxLayout>
#include <QSet>
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QMouseEvent>
#include <QListWidget>

#include "CumparaturiWindow.h"

void CumparaturiWindow::populeazaCumparaturi() {
    // Parcurge lista de produse
    ServerConector::send_message("Cumparaturi");
    QString message;
    for (int i = 0; i < listaProduse->count(); ++i) {
        QString productName = listaProduse->item(i)->text();
        QStringList n = productName.split(" ");
        // Caută ingredientul în guiListaIngrediente după nume
        for (Ingredient &ingredient : guiListaIngrediente) {
            if (ingredient.getNume() == n[0]) {
                // Incrementați ID-ul ingredientului găsit
                ingredient.incrementID();
                break; // Ieșiți din bucla for internă după găsirea ingredientului
            }
        }
    }

    for (Ingredient &ingredient : guiListaIngrediente)
    {
        if(ingredient.getID() != 0)
        {
            message.append(ingredient.getNume());
            message.append(" ");
            message.append(QString::number(ingredient.getID()));
            message.append("\n");
        }
    }
    QString response;
    ServerConector::send_message(message);
    response = ServerConector::receive_message();
    //QStringList cuvant;
    //cuvant = response.split(" ");
    cumparaturi->addItem(response);
    qDebug() << message;
}

CumparaturiWindow::CumparaturiWindow(QList<Ingredient> li, QWidget *parent) : QMainWindow(parent), guiListaIngrediente(li) {
    setWindowTitle("Cumpărături");
    resize(720, 640);

    // Lista de produse
    listaProduse = new QListWidget(this);
    listaProduse->setGeometry(10, 10, 200, 300);
    cumparaturi = new QListWidget(this);
    cumparaturi->setGeometry(10,320,200,200);

    // Câmp pentru introducerea numelui produsului
    numeProdusEdit = new QLineEdit(this);
    numeProdusEdit->setGeometry(220, 10, 150, 30);

    // Buton pentru adăugarea produsului
    adaugaButton = new QPushButton("Adaugă", this);
    adaugaButton->setGeometry(220, 50, 150, 30);
    connect(adaugaButton, &QPushButton::clicked, this, &CumparaturiWindow::adaugaProdus);

    // Buton pentru ștergerea produsului selectat
    stergeButton = new QPushButton("Șterge", this);
    stergeButton->setGeometry(220, 90, 150, 30);
    connect(stergeButton, &QPushButton::clicked, this, &CumparaturiWindow::stergeProdus);

    populeazaCumparaturiButton = new QPushButton("Populează Cumpărături", this);
    populeazaCumparaturiButton->setGeometry(220, 130, 150, 30);
    connect(populeazaCumparaturiButton, &QPushButton::clicked, this, &CumparaturiWindow::populeazaCumparaturi);

    // Create a QListWidget for displaying ingredients
    detaliiListWidget = new QListWidget(this);
    // Set the mode to single selection
    detaliiListWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    detaliiListWidget->setGeometry(500, 10, 200, 300);

    // Populate the QListWidget with ingredients
    QString content;
    for (const Ingredient &ingredient : guiListaIngrediente) {
        content.clear();
        content.append(ingredient.getNume());
        content.append(" ");
        content.append(QString::number(ingredient.getCantitate()));
        content.append(" ");
        content.append(ingredient.getUnitateDeMasura());
        QListWidgetItem *item = new QListWidgetItem(content);
        detaliiListWidget->addItem(item);
    }
}




void CumparaturiWindow::adaugaProdus() {
    QString numeProdus = numeProdusEdit->text();
    if (!numeProdus.isEmpty()) {
        listaProduse->addItem(numeProdus);
        numeProdusEdit->clear();
    }
    else
    {
        QListWidgetItem *selectedItem = detaliiListWidget->currentItem();
        if (selectedItem) {
            // Obținem textul elementului selectat și îl adăugăm în listaProduse
            QString selectedIngredient = selectedItem->text();
            listaProduse->addItem(selectedIngredient);
        }
    }
}

void CumparaturiWindow::stergeProdus() {
    qDeleteAll(listaProduse->selectedItems());
}
