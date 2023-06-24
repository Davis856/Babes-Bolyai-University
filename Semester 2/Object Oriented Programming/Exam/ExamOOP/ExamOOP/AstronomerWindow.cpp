#include "AstronomerWindow.h"
#include <time.h>

AstronomerWindow::AstronomerWindow(RepoStars& repo, Astronomer& a, QWidget* parent) : repo{ repo }, a{ a }, QWidget(parent) {
    this->repo.addObserver(this);
    this->initGUI();
    this->connectSignals();
    this->show();

}

AstronomerWindow::~AstronomerWindow() {
    this->repo.removeObserver(this);
}

void AstronomerWindow::update() {
    this->notifyModel();
}

void AstronomerWindow::notifyModel() {
    this->tableModel->updateInternalData();
}

void AstronomerWindow::initGUI() {
    QFont buttonsFont("Consolas", 13, true);

    this->starsTableView = new QTableView();
    this->tableModel = new TableModel(this->repo);

    this->starsTableView->setModel(this->tableModel);

    this->starsTableView->resizeColumnsToContents();

    this->RALineEdit = new QLineEdit();
    this->RALineEdit->setFont(buttonsFont);

    this->nameLineEdit = new QLineEdit();
    this->nameLineEdit->setFont(buttonsFont);

    this->decLineEdit = new QLineEdit();
    this->decLineEdit->setFont(buttonsFont);

    this->diameterLineEdit = new QLineEdit();
    this->diameterLineEdit->setFont(buttonsFont);

    this->RALabel = new QLabel("RA");
    this->RALabel->setFont(buttonsFont);

    this->nameLabel = new QLabel("Name");
    this->nameLabel->setFont(buttonsFont);

    this->decLabel = new QLabel("Dec");
    this->decLabel->setFont(buttonsFont);

    this->diameterLabel = new QLabel("Diameter");
    this->diameterLabel->setFont(buttonsFont);

    this->addButton = new QPushButton("Add star!");
    this->addButton->setFont(buttonsFont);

    this->updateButton = new QPushButton("Update star!");
    this->updateButton->setFont(buttonsFont);

    this->viewBox = new QCheckBox("View", this);

    this->mainLayout = new QVBoxLayout();
    this->buttonsLayout = new QGridLayout();

    this->mainLayout->addWidget(this->starsTableView);

    this->buttonsLayout->addWidget(this->nameLabel, 0, 0);
    this->buttonsLayout->addWidget(this->RALabel, 0, 1);
    this->buttonsLayout->addWidget(this->decLabel, 0, 2);
    this->buttonsLayout->addWidget(this->diameterLabel, 0, 3);

    this->buttonsLayout->addWidget(this->nameLineEdit, 1, 0);
    this->buttonsLayout->addWidget(this->RALineEdit, 1, 1);
    this->buttonsLayout->addWidget(this->decLineEdit, 1, 2);
    this->buttonsLayout->addWidget(this->diameterLineEdit, 1, 3);

    this->mainLayout->addLayout(this->buttonsLayout);
    this->mainLayout->addWidget(this->addButton);
    this->mainLayout->addWidget(this->updateButton);
    this->mainLayout->addWidget(this->viewBox);


    this->setLayout(this->mainLayout);
    this->setWindowTitle(QString::fromStdString(a.getName()));
    this->resize(1200, 700);

}

void AstronomerWindow::connectSignals() {
    QObject::connect(this->addButton, &QPushButton::clicked, this, &AstronomerWindow::addStar);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &AstronomerWindow::updateStar);
    QObject::connect(this->viewBox, &QCheckBox::isChecked, this, &AstronomerWindow::viewStars);
}

void AstronomerWindow::addStar() {
    std::string name = this->nameLineEdit->text().toStdString();
    std::string cons = a.getCons();
    if (name.empty()) {
        QMessageBox::critical(this, "Error", "Invalid input!");
        return;
    }
    int RA = this->RALineEdit->text().toInt();
    int dec = this->decLineEdit->text().toInt();
    int diameter = this->diameterLineEdit->text().toInt();
    
    Star s(name, cons, RA, dec, diameter);
    try {
        this->repo.addStar(s);
    }
    catch (...) {
        QMessageBox::critical(this, "Error", "Invalid input!");
        return;
    }
    this->nameLineEdit->clear();
    this->RALineEdit->clear();
    this->decLineEdit->clear();
    this->diameterLineEdit->clear();
}

void AstronomerWindow::updateStar()
{
    std::string name = this->nameLineEdit->text().toStdString();
    if (name.empty()) {
        QMessageBox::critical(this, "Error", "Invalid input!");
        return;
    }
    int RA = this->RALineEdit->text().toInt();
    int dec = this->decLineEdit->text().toInt();
    int diameter = this->diameterLineEdit->text().toInt();
    if (diameter<10) {
        QMessageBox::critical(this, "Error", "Invalid input!");
        return;
    }

    Star s(name, a.getCons(), RA, dec, diameter);
    try {
        this->repo.updateStar(s);
    }
    catch (...) {
        QMessageBox::critical(this, "Error", "Invalid input!");
        return;
    }
    this->nameLineEdit->clear();
    this->RALineEdit->clear();
    this->decLineEdit->clear();
    this->diameterLineEdit->clear();
}

void AstronomerWindow::viewStars()
{

}