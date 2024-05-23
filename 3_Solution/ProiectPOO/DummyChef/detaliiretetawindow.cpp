// Clasa DetaliiRetetaWindow (DetaliiRetetaWindow.cpp)
#include "DetaliiRetetaWindow.h"
#include "ingredient.h"


DetaliiRetetaWindow::DetaliiRetetaWindow(QWidget *parent) : QMainWindow(parent) {
    creazaInterfata();
}

void DetaliiRetetaWindow::creazaInterfata() {
    // Creează un QListWidget pentru a afișa detaliile rețetei
    detaliiListWidget = new QListWidget(this);

    // Setează dimensiunea și comportamentul listei
    detaliiListWidget->setFixedSize(720, 480);
    detaliiListWidget->setSelectionMode(QAbstractItemView::NoSelection);

    // Setează wordWrap pentru a permite textului să treacă pe următorul rând în elementele listei
    detaliiListWidget->setWordWrap(true);

    // Adaugă QListWidget la fereastra principală
    setCentralWidget(detaliiListWidget);

    // Creează QLabel pentru afișarea pozei rețetei
    pozaLabel = new QLabel(this);
    pozaLabel->setFixedSize(520, 470);
    pozaLabel->setAlignment(Qt::AlignCenter);
    pozaLabel->move(10,100);
    // Adaugă QLabel la fereastra principală
    //layout()->addWidget(pozaLabel);
}

void DetaliiRetetaWindow::afiseazaDetaliiReteta(const Reteta& reteta) {
    // Șterge elementele anterioare din lista
    detaliiListWidget->clear();

    // Adaugă detaliile rețetei în QListWidget
    detaliiListWidget->addItem("Nume: " + reteta.getNume());
    QList<Ingredient> ingrediente = reteta.getIngrediente();
    QStringList ingredienteStringList;
    for (const Ingredient& ingredient : ingrediente) {
        ingredienteStringList << ingredient.getNume() + " " + QString::number(ingredient.getCantitate()) + " " + ingredient.getUnitateDeMasura();
    }
    detaliiListWidget->addItem("Ingrediente: " + ingredienteStringList.join(", "));
    detaliiListWidget->addItem("Mod de preparare: " + reteta.getModDePreparare());

    // Încarcă poza rețetei și o redimensionează
    QPixmap poza(reteta.getPozaPath());
    if (!poza.isNull()) {
        poza = poza.scaled(720, 160, Qt::KeepAspectRatio); // Redimensionează poza păstrând aspectul original
        pozaLabel->setPixmap(poza);
        pozaLabel->setScaledContents(true);
    } else {
        pozaLabel->setText("Poza indisponibilă");
    }
}


/*
void DetaliiRetetaWindow::creazaInterfata() {
    // Creează etichetele pentru afișarea detaliilor rețetei
    numeLabel = new QLabel(this);
    ingredienteLabel = new QLabel(this);
    modPreparareLabel = new QLabel(this);
    pozaLabel = new QLabel(this);

    // Creează un widget central și un layout vertical pentru el
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Adaugă etichetele în layout-ul vertical
    layout->addWidget(numeLabel);
    layout->addWidget(ingredienteLabel);
    layout->addWidget(modPreparareLabel);
    layout->addWidget(pozaLabel);

    // Setează distanța verticală între elemente
    layout->setSpacing(20); // Poți ajusta valoarea la distanța dorită

    // Setează dimensiunea fixă pentru widget-ul pozei
    pozaLabel->setFixedSize(720, 640);

    // Setează wordWrap pentru eticheta modPreparareLabel pentru a permite textului să treacă pe următorul rând
    modPreparareLabel->setWordWrap(true);

    // Setează widget-ul central al ferestrei cu widget-ul cu layout-ul vertical
    setCentralWidget(centralWidget);
}

void DetaliiRetetaWindow::afiseazaDetaliiReteta(const Reteta& reteta) {
    // Actualizează etichetele cu detaliile rețetei
    numeLabel->setText("Nume: " + reteta.getNume());
    QList<Ingredient> ingrediente = reteta.getIngrediente();

    QStringList ingredienteStringList;
    for (const Ingredient& ingredient : ingrediente) {
        ingredienteStringList << ingredient.getNume() + " " + QString::number(ingredient.getCantitate()) + " " + ingredient.getUnitateDeMasura();
    }

    ingredienteLabel->setText("Ingrediente: " + ingredienteStringList.join(", "));
    modPreparareLabel->setText("Mod de preparare: " + reteta.getModDePreparare());

    // Încarcă poza rețetei și o redimensionează
    QPixmap poza(reteta.getPozaPath());
    if (!poza.isNull()) {
        poza = poza.scaled(720, 640, Qt::KeepAspectRatio); // Redimensionează poza păstrând aspectul original
        pozaLabel->setPixmap(poza);
        pozaLabel->setScaledContents(true);
    } else {
        pozaLabel->setText("Poza indisponibilă");
    }

}
*/




