// Clasa DetaliiRetetaWindow (DetaliiRetetaWindow.cpp)
#include "DetaliiRetetaWindow.h"

DetaliiRetetaWindow::DetaliiRetetaWindow(QWidget *parent) : QDialog(parent) {
    creazaInterfata();
}

void DetaliiRetetaWindow::creazaInterfata() {
    // Creează etichetele pentru afișarea detaliilor rețetei
    numeLabel = new QLabel(this);
    ingredienteLabel = new QLabel(this);
    modPreparareLabel = new QLabel(this);
    pozaLabel = new QLabel(this);

    resize(720, 640);
    // Layout vertical pentru aranjarea etichetelor
    layout = new QVBoxLayout(this);
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

    // Setează layout-ul pentru fereastra
    setLayout(layout);
}



void DetaliiRetetaWindow::afiseazaDetaliiReteta(const Reteta& reteta) {
    // Actualizează etichetele cu detaliile rețetei
    numeLabel->setText("Nume: " + reteta.getNume());
    ingredienteLabel->setText("Ingrediente: " + reteta.getIngrediente().join(", "));
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

