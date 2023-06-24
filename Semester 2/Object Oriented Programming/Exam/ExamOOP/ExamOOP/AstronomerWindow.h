#pragma once


#include "RepoStars.h"
#include <QWidget>
#include "Observer.h"
#include <QPushButton>
#include <QLineEdit>
#include <QListWidget>
#include <QLabel>
#include "TableModel.h"
#include <QTableView>
#include <QVBoxLayout>
#include <QMessageBox>
#include "Astronomer.h"
#include <qcheckbox.h>
#include <qabstractitemview.h>

class AstronomerWindow : public QWidget, public Observer {

private:
    RepoStars& repo;
    Astronomer& a;
    QLineEdit* nameLineEdit, * consLineEdit, * RALineEdit, *decLineEdit, *diameterLineEdit;
    QPushButton* addButton, * updateButton, * viewButton, *saveButton;
    QTableView* starsTableView;
    TableModel* tableModel;
    QLabel* nameLabel, * consLabel, * RALabel, * decLabel, * diameterLabel;
    QVBoxLayout* mainLayout;
    QGridLayout* buttonsLayout;
    QCheckBox* viewBox;

public:
    AstronomerWindow(RepoStars& repo, Astronomer &a, QWidget* parent = Q_NULLPTR);
    ~AstronomerWindow();
    void update() override;
    void notifyModel();
    void initGUI();
    void connectSignals();
    void addStar();
    void updateStar();
    void viewStars();
};