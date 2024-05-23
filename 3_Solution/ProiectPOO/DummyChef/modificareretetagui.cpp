#include "modificareretetagui.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>

ModificareRetetaGUI::ModificareRetetaGUI(Reteta& r, QWidget *parent)
    : QMainWindow(parent), reteta(r)
{
    //connect(modificaButton, &QPushButton::clicked, this, &ModificareRetetaGUI::aplicareModificari);
    setupUI();
}

ModificareRetetaGUI::~ModificareRetetaGUI()
{
    // Clean up any resources if needed
}

void ModificareRetetaGUI::setupUI()
{
    // Creează câmpuri de editare pentru fiecare detaliu al retetei
    numeLineEdit = new QLineEdit(reteta.getNume(), this);

    // Creează întotdeauna 5 câmpuri de editare text pentru ingrediente
    for (int i = 0; i < 5; ++i) {
        QLineEdit* lineEdit = new QLineEdit(this);
        listaIngredienteLineEdit.append(lineEdit);
    }

    modPreparareTextEdit = new QLineEdit(reteta.getModDePreparare(), this);

    // Butonul "Modifică"
    modificaButton = new QPushButton("Modifică", this);
    connect(modificaButton, &QPushButton::clicked, this, &ModificareRetetaGUI::aplicareModificari);

    // Layout-ul principal
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addWidget(new QLabel("Nume:", this));
    mainLayout->addWidget(numeLineEdit);
    mainLayout->addWidget(new QLabel("Ingrediente:", this));
    for (QLineEdit* lineEdit : listaIngredienteLineEdit) {
        mainLayout->addWidget(lineEdit);
    }
    mainLayout->addWidget(new QLabel("Mod de preparare:", this));
    mainLayout->addWidget(modPreparareTextEdit);
    mainLayout->addWidget(modificaButton);

    // Setează layout-ul principal în fereastra principală
    QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(mainLayout);
    setCentralWidget(centralWidget);
}

void ModificareRetetaGUI::aplicareModificari()
{
    // Obține noile valori introduse în câmpurile de editare
    QString numeNou = numeLineEdit->text();
    QString modPreparareNou = modPreparareTextEdit->text();

    // Construiește o listă nouă de ingrediente pe baza valorilor introduse în câmpurile de editare
    QList<Ingredient> ingredienteNoi;
    for (QLineEdit* lineEdit : listaIngredienteLineEdit) {
        QStringList ingredientParts = lineEdit->text().split(" ");
        if (ingredientParts.size() >= 3) {
            QString nume = ingredientParts[0];
            double cantitate = ingredientParts[1].toDouble();
            QString unitateDeMasura = ingredientParts[2];
            Ingredient ingredient(0, nume, cantitate, unitateDeMasura); // ID-ul este 0, poate fi ajustat în funcție de nevoi
            ingredienteNoi.append(ingredient);
        }
    }

    // Actualizează detaliile retetei cu noile valori
    reteta.setNume(numeNou);
    reteta.setModDePreparare(modPreparareNou);
    reteta.setIngrediente(ingredienteNoi);
}


