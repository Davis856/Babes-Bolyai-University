#include <QVBoxLayout>
#include <QFormLayout>
#include <QErrorMessage>
#include <QMessageBox>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include "GUI.h"

CoatTableModel::CoatTableModel(Basket* newRepository) {
    this->basket = newRepository;
}

int CoatTableModel::rowCount(const QModelIndex& parent) const {
    return this->basket->getSize();
}

int CoatTableModel::columnCount(const QModelIndex& parent) const {
    return 5;
}

QVariant CoatTableModel::data(const QModelIndex& index, int role) const {
    int row = index.row();
    Coat currentCoat = this->basket->getArray()[row];
    int column = index.column();
    if (role == Qt::DisplayRole || role == Qt::EditRole) {
        switch (column) {
        case 0:
            return QString::fromStdString(std::to_string(currentCoat.getSize()));
        case 1:
            return QString::fromStdString(currentCoat.getColour());
        case 2:
            return QString::fromStdString(std::to_string(currentCoat.getQuantity()));
        case 3:
            return QString::fromStdString(std::to_string(currentCoat.getPrice()));
        case 4:
            return QString::fromStdString(currentCoat.getPhotograph());
        default:
            break;
        }
    }
    return QVariant();
}

QVariant CoatTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole) {
        if (orientation == Qt::Horizontal) {
            switch (section) {
            case 0:
                return QString("Size");
            case 1:
                return QString("Colour");
            case 2:
                return QString("Quantity");
            case 3:
                return QString("Price");
            case 4:
                return QString("Photo");
            default:
                break;
            }
        }
    }
    return QVariant();
}

void CoatTableModel::update() {
    QModelIndex topLeft = this->index(1, 1);
    QModelIndex bottomRight = this->index(this->rowCount(), this->columnCount());
    emit layoutChanged();
    emit dataChanged(topLeft, bottomRight);
}

GUI::GUI(AdminService& adminServ, UserService& userServ, Validator& validator, Repository& repo, Basket& basket) : adminService{ adminServ }, userService{ userServ }, validator{ validator }, repository{ repo }, basket{ basket }
{
    this->repository.InitializeRepo();
	this->titleWidget = new QLabel(this);
	this->adminButton = new QPushButton(this);
	this->userButton = new QPushButton(this);
	this->initGUI();
	this->connectSignalsAndSlots();
}

void GUI::initGUI()
{
    auto* layout = new QVBoxLayout(this);
    QFont titleFont = this->titleWidget->font();
    this->titleWidget->setText("<p style='text-align:center'><font color=#4D2D52>Welcome to the coat Shelter App! <br> Select your mode!</font></p>");
    titleFont.setItalic(true);
    titleFont.setPointSize(10);
    titleFont.setStyleHint(QFont::System);
    titleFont.setWeight(QFont::DemiBold);
    this->titleWidget->setFont(titleFont);
    layout->addWidget(this->titleWidget);
    this->adminButton->setText("Admin mode");
    layout->addWidget(this->adminButton);
    this->userButton->setText("User mode");
    layout->addWidget(this->userButton);
    this->setLayout(layout);
    this->setStyleSheet("background-color:#D9DBF1");

}

GUI::~GUI() = default;

void GUI::connectSignalsAndSlots()
{
    QObject::connect(this->adminButton, &QPushButton::clicked, this, &GUI::showAdmin);
    QObject::connect(this->userButton, &QPushButton::clicked, this, &GUI::showUser);
}

void GUI::showAdmin()
{
    this->adminService.clearUndoRedo();
    auto* admin = new AdminGUI(this, this->adminService, this->validator, this->repository, this->basket);
    admin->show();
}

AdminGUI::AdminGUI(QWidget* parent, AdminService& adminServ, Validator& validator, Repository& repo, Basket& basket) : adminService{ adminServ }, validator{ validator }, repo{ repo }, basket{ basket }
{
    this->titleWidget = new QLabel(this);
    this->coatListWidget = new QListWidget{};
    this->sizeLineEdit = new QLineEdit{};
    this->colourLineEdit = new QLineEdit{};
    this->priceLineEdit = new QLineEdit{};
    this->quantityLineEdit = new QLineEdit{};
    this->photographLineEdit = new QLineEdit{};
    this->priceFilterLineEdit = new QLineEdit{};
    this->addButton = new QPushButton("Add");
    this->deleteButton = new QPushButton("Delete");
    this->updateButton = new QPushButton("Update");
    this->chartButton = new QPushButton("Display chart");
    this->undoButton = new QPushButton("Undo");
    this->redoButton = new QPushButton("Redo");
    this->shortcutUndo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    this->shortcutRedo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);
    setParent(parent);
    setWindowFlag(Qt::Window);
    this->initAdminGUI();
    this->populateList();
    this->connectSignalsAndSlots();
}

void AdminGUI::initAdminGUI() {
    auto* layout = new QVBoxLayout(this);
    QFont titleFont = this->titleWidget->font();
    this->titleWidget->setText("<p style='text-align:center'><font color=#4D2D52>ADMIN MODE</font></p>");
    titleFont.setItalic(true);
    titleFont.setPointSize(10);
    titleFont.setStyleHint(QFont::System);
    titleFont.setWeight(QFont::DemiBold);
    this->titleWidget->setFont(titleFont);
    layout->addWidget(this->titleWidget);

    layout->addWidget(this->coatListWidget);

    auto* coatDetailsLayout = new QFormLayout{};
    coatDetailsLayout->addRow("Size", this->sizeLineEdit);
    coatDetailsLayout->addRow("Colour", this->colourLineEdit);
    coatDetailsLayout->addRow("Price", this->priceLineEdit);
    coatDetailsLayout->addRow("Quantity", this->quantityLineEdit);
    coatDetailsLayout->addRow("Photograph", this->photographLineEdit);
    
    layout->addLayout(coatDetailsLayout);

    auto* buttonsLayout = new QGridLayout{};
    buttonsLayout->addWidget(this->addButton, 0, 0);
    buttonsLayout->addWidget(this->deleteButton, 0, 1);
    buttonsLayout->addWidget(this->updateButton, 1, 0);
    buttonsLayout->addWidget(this->chartButton, 1, 1);
    buttonsLayout->addWidget(this->undoButton, 2, 0);
    buttonsLayout->addWidget(this->redoButton, 2, 1);
    layout->addLayout(buttonsLayout);
}

void AdminGUI::populateList() {
    this->coatListWidget->clear();
    std::vector<Coat> Coats = this->repo.getArray();
    for (Coat& coat : Coats)
        this->coatListWidget->addItem(QString::fromStdString(std::to_string(coat.getSize())));
}

void AdminGUI::connectSignalsAndSlots() {
    QObject::connect(this->coatListWidget, &QListWidget::itemSelectionChanged, [this]() {
        int selectedIndex = this->getSelectedIndex();
        if (selectedIndex < 0)
            return;
        Coat coat = this->repo.getArray()[selectedIndex];
        this->sizeLineEdit->setText(QString::fromStdString(std::to_string(coat.getSize())));
        this->colourLineEdit->setText(QString::fromStdString(coat.getColour()));
        this->priceLineEdit->setText(QString::fromStdString(std::to_string(coat.getPrice())));
        this->quantityLineEdit->setText(QString::fromStdString(std::to_string(coat.getQuantity())));
        this->photographLineEdit->setText(QString::fromStdString(coat.getPhotograph()));
    });

    QObject::connect(this->shortcutUndo, &QShortcut::activated, this, &AdminGUI::undoGUI);
    QObject::connect(this->shortcutRedo, &QShortcut::activated, this, &AdminGUI::redoGUI);

    QObject::connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::addCoat);
    QObject::connect(this->deleteButton, &QPushButton::clicked, this, &AdminGUI::deleteCoat);
    QObject::connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::updateCoat);
    //QObject::connect(this->chartButton, &QPushButton::clicked, this, &AdminGUI::displayChart);

    QObject::connect(this->undoButton, &QPushButton::clicked, this, &AdminGUI::undoGUI);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &AdminGUI::redoGUI);
}

void AdminGUI::addCoat() {
    std::string size = this->sizeLineEdit->text().toStdString();
    std::string colour = this->colourLineEdit->text().toStdString();
    std::string price = this->priceLineEdit->text().toStdString();
    std::string quantity = this->quantityLineEdit->text().toStdString();
    std::string photograph = this->photographLineEdit->text().toStdString();
    int size1, price1, quantity1;
    try {
        size1 = stoi(size);
        price1 = stoi(price);
        quantity1 = stoi(quantity);
        this->adminService.addCoat(size1, colour, price1, quantity1, photograph);
        this->populateList();
    }
    catch (ValidationException& exc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(exc.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    }
    catch (RepositoryException& re) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(re.what());
        error->setWindowTitle("Error at adding coat!");
        error->exec();
    }
}

void AdminGUI::deleteCoat() {
    try {
        std::string size_s = this->sizeLineEdit->text().toStdString();
        this->validator.validateString(size_s);
        int size = stoi(size_s);
        this->adminService.removeCoat(size);
        this->populateList();
    }
    catch (ValidationException& exc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(exc.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    }
    catch (RepositoryException& re) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(re.what());
        error->setWindowTitle("Error at deleting dog!");
        error->exec();
    }
}

void AdminGUI::updateCoat() {
    int index = this->getSelectedIndex();
    try {
        if (index < 0) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText("No coat selected!");
            error->setWindowTitle("Selection error!");
            error->exec();
        }
        else {
            std::string old_size_s = std::to_string(this->repo.getArray()[index].getSize());
            int old_size = stoi(old_size_s);
            std::string new_size_s = this->sizeLineEdit->text().toStdString();
            int new_size = stoi(new_size_s);
            std::string new_colour = this->colourLineEdit->text().toStdString();
            std::string new_price = this->priceLineEdit->text().toStdString();
            int price, quantity;
            std::string new_quantity = this->quantityLineEdit->text().toStdString();
            std::string new_link = this->photographLineEdit->text().toStdString();
            price = stoi(new_price);
            quantity = stoi(new_quantity);
            this->adminService.updateCoatSize(old_size, new_size);
            this->adminService.updateCoatColour(old_size, new_colour);
            this->adminService.updateCoatPrice(old_size, price);
            this->adminService.updateCoatQuantity(old_size, quantity);
            this->adminService.updateCoatPhotograph(old_size, new_link);
            this->populateList();
        }
    }
    catch (ValidationException& exc) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(exc.what());
        error->setWindowTitle("Invalid input!");
        error->exec();
    }
    catch (RepositoryException& re) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(re.what());
        error->setWindowTitle("Error at deleting dog!");
        error->exec();
    }
}


//void AdminGUI::displayChart() {
//    this->chartWindow = new QWidget{};
//    auto* chartLayout = new QVBoxLayout(this->chartWindow);
//    this->chartWindow->setStyleSheet("background-color:#D9DBF1");
//    std::vector<Coat> Coats = this->repo.getArray();
//    auto* chart = new QtCharts::QChart();
//    auto* axis_x = new QtCharts::QBarCategoryAxis();
//    axis_x->setTitleText("Coats");
//
//    QStringList categories;
//    for (int i = 1; i <= Coats.size(); i++) {
//        categories << QString::fromStdString(std::to_string(i));
//    }
//
//    axis_x->append(categories);
//    chart->addAxis(axis_x, Qt::AlignBottom);
//
//    auto* axis_y = new QtCharts::QValueAxis();
//    chart->addAxis(axis_y, Qt::AlignLeft);
//    axis_y->setRange(0, 8);
//    axis_y->setTitleText("Number of coats");
//
//    for (auto& coat : Coats) {
//        auto* series = new QtCharts::QBarSeries();
//        auto* set = new QtCharts::QBarSet(QString::fromStdString(quantity));
//        int number_of_coats = this->adminService.numberOfDogsPerBreed(breed);
//        *set << number_of_coats;
//        series->append(set);
//        chart->addSeries(series);
//        series->attachAxis(axis_y);
//    }
//
//    chart->setTitle("Number of coats per quantity");
//    chart->setAnimationOptions(QtCharts::QChart::SeriesAnimations);
//
//    chart->legend()->setVisible(true);
//    chart->legend()->setAlignment(Qt::AlignLeft);
//    chart->legend()->setBackgroundVisible(true);
//    chart->legend()->setBorderColor(QColor::fromRgb(171, 147, 225));
//    chart->legend()->setFont(QFont("Cambria Math", 7));
//
//    auto* chartView = new QtCharts::QChartView(chart);
//    chartView->setRenderHint(QPainter::Antialiasing);
//
//    chartLayout->addWidget(chartView);
//    this->chartWindow->resize(840, 720);
//    this->chartWindow->show();
//}

int AdminGUI::getSelectedIndex() const {
    QModelIndexList selectedIndexes = this->coatListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty()) {
        this->sizeLineEdit->clear();
        this->colourLineEdit->clear();
        this->priceLineEdit->clear();
        this->quantityLineEdit->clear();
        this->photographLineEdit->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void AdminGUI::undoGUI() {
    try {
        this->adminService.undoLastAction();
        this->populateList();
    }
    catch (RepositoryException& re) {
        QMessageBox::critical(this, "Error", re.what());
    }
}

void AdminGUI::redoGUI() {
    try {
        this->adminService.redoLastAction();
        this->populateList();
    }
    catch (RepositoryException& re) {
        QMessageBox::critical(this, "Error", re.what());
    }
}

AdminGUI::~AdminGUI() = default;

void GUI::showUser() {
    auto* user = new UserGUI(this, this->adminService, this->userService, this->repository, this->basket, this->validator);
    user->show();
}

UserGUI::UserGUI(QWidget* parent, AdminService& serv, UserService& userserv, Repository& repo, Basket& basket, Validator& validator1) : adminserv{ serv }, userserv{ userserv }, repo{ repo }, basket{ basket }, validator{ validator1 } {
    this->titleWidget = new QLabel(this);
    this->coatListWidget = new QListWidget{};
    this->basketListWidget = new QListWidget{};
    this->sizeLineEdit = new QLineEdit{};
    this->colourLineEdit = new QLineEdit{};
    this->priceLineEdit = new QLineEdit{};
    this->quantityLineEdit = new QLineEdit{};
    this->photographLineEdit = new QLineEdit{};
    this->priceFilterLineEdit = new QLineEdit{};
    this->addButton = new QPushButton("Add to the basket");
    this->filterButton = new QPushButton("Filter");
    this->openListButton = new QPushButton("Open file");
    this->csvButton = new QRadioButton("CSV");
    this->htmlButton = new QRadioButton("HTML");
    this->undoButton = new QPushButton("Undo");
    this->redoButton = new QPushButton("Redo");
    this->shortcutUndo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_U), this);
    this->shortcutRedo = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_R), this);
    this->repoTypeSelected = false;
    this->filtered = false;
    setParent(parent);
    setWindowFlag(Qt::Window);
    this->populateBasketList();
    this->populateCoatList();
    this->initUserGUI();
    this->connectSignalsAndSlots();
}

void UserGUI::initUserGUI() {
    auto* layout = new QVBoxLayout(this);
    QFont titleFont = this->titleWidget->font();
    this->titleWidget->setText("<p style='text-align:center'><font color=#4D2D52>USER MODE <br> Select the type of file you want for saving your basket!</font></p>");
    titleFont.setItalic(true);
    titleFont.setPointSize(10);
    titleFont.setStyleHint(QFont::System);
    titleFont.setWeight(QFont::DemiBold);
    this->titleWidget->setFont(titleFont);
    layout->addWidget(this->titleWidget);

    auto* radioButtonsLayout = new QGridLayout(this);
    radioButtonsLayout->addWidget(this->csvButton, 0, 0);
    radioButtonsLayout->addWidget(this->htmlButton, 1, 0);
    radioButtonsLayout->addWidget(this->openListButton, 0, 1);
    layout->addLayout(radioButtonsLayout);

    auto* listLayout = new QGridLayout(this);
    listLayout->addWidget(this->coatListWidget, 0, 0);
    listLayout->addWidget(this->basketListWidget, 0, 1);
    layout->addLayout(listLayout);

    auto* coatDetailsLayout = new QFormLayout{};
    coatDetailsLayout->addRow("Size", this->sizeLineEdit);
    coatDetailsLayout->addRow("Colour", this->colourLineEdit);
    coatDetailsLayout->addRow("Price", this->priceLineEdit);
    coatDetailsLayout->addRow("Quantity", this->quantityLineEdit);
    coatDetailsLayout->addRow("Photograph", this->photographLineEdit);
    coatDetailsLayout->addRow(this->addButton);
    layout->addLayout(coatDetailsLayout);

    auto* undoRedoLayout = new QGridLayout(this);
    undoRedoLayout->addWidget(this->undoButton, 0, 0);
    undoRedoLayout->addWidget(this->redoButton, 0, 1);
    layout->addLayout(undoRedoLayout);


    auto* filterTitle = new QLabel("<p style='text-align:center'><font color=#4D2D52><br>Filter the available coats by price</font></p>");
    QFont filterFont = filterTitle->font();
    filterFont.setPointSize(10);
    filterFont.setStyleHint(QFont::System);
    filterFont.setWeight(QFont::DemiBold);
    filterTitle->setFont(filterFont);
    layout->addWidget(filterTitle);

    auto* filterDetailsLayout = new QFormLayout{};
    filterDetailsLayout->addRow("Price", this->priceFilterLineEdit);
    filterDetailsLayout->addRow(this->filterButton);
    layout->addLayout(filterDetailsLayout);
}

void UserGUI::createTable() {
    this->basketListTableModel = new CoatTableModel{ this->userserv.getRepo() };
    this->basketListTable = new QTableView{};
    this->basketListTable->setModel(this->basketListTableModel);
    this->listAndTableLayout->addWidget(this->basketListTable, 0, 1);
    this->basketListTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    this->resize(900, 500);
}

void UserGUI::connectSignalsAndSlots() {
    QObject::connect(this->coatListWidget, &QListWidget::itemClicked, [this]() {
        int pos = this->coatListWidget->selectedItems().at(0)->text().toInt();
        int index = this->repo.FindElemBySize(pos);
        Coat coat = this->repo.getArray()[index];
        this->sizeLineEdit->setText(QString::fromStdString(std::to_string(coat.getSize())));
        this->colourLineEdit->setText(QString::fromStdString(coat.getColour()));
        this->priceLineEdit->setText(QString::fromStdString(std::to_string(coat.getPrice())));
        this->quantityLineEdit->setText(QString::fromStdString(std::to_string(coat.getQuantity())));
        std::string link = std::string("start ").append(coat.getPhotograph());
        system(link.c_str());
    });

    QObject::connect(this->csvButton, &QRadioButton::clicked, [this]() {
        this->userserv.repositoryType("csv");
        this->repoTypeSelected = true;
    });

    QObject::connect(this->htmlButton, &QRadioButton::clicked, [this]() {
        this->userserv.repositoryType("html");
        this->repoTypeSelected = true;
    });

    QObject::connect(this->openListButton, &QPushButton::clicked, [this]() {
        if (!this->repoTypeSelected) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Warning);
            error->setText("Please select the type of file you want!");
            error->setWindowTitle("File type warning!");
            error->exec();
        }
        else {
            std::string link = std::string("start ").append(this->userserv.getFileService());
            system(link.c_str());
        }
    });

    QObject::connect(this->shortcutUndo, &QShortcut::activated, this, &UserGUI::undoGUI);
    QObject::connect(this->shortcutRedo, &QShortcut::activated, this, &UserGUI::redoGUI);

    QObject::connect(this->addButton, &QPushButton::clicked, this, &UserGUI::addCoat);
    QObject::connect(this->filterButton, &QPushButton::clicked, this, &UserGUI::filterCoat);

    QObject::connect(this->undoButton, &QPushButton::clicked, this, &UserGUI::undoGUI);
    QObject::connect(this->redoButton, &QPushButton::clicked, this, &UserGUI::redoGUI);
}

int UserGUI::getSelectedIndex() const {
    QModelIndexList selectedIndexes = this->coatListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.empty()) {
        this->sizeLineEdit->clear();
        this->colourLineEdit->clear();
        this->priceLineEdit->clear();
        this->quantityLineEdit->clear();
        this->photographLineEdit->clear();
        return -1;
    }
    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void UserGUI::populateCoatList() {
    this->coatListWidget->clear();
    std::vector<Coat> allCoats = this->repo.getArray();
    for (Coat& coat : allCoats)
        this->coatListWidget->addItem(QString::fromStdString(std::to_string(coat.getSize())));
}

void UserGUI::populateBasketList() {
    this->coatListWidget->clear();
    std::vector<Coat> allCoats = this->basket.getArray();
    for (Coat& coat : allCoats)
        this->coatListWidget->addItem(QString::fromStdString(std::to_string(coat.getSize())));
}


void UserGUI::addCoat() {
    if (!this->repoTypeSelected) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Warning);
        error->setText("Please select the type of file you want!");
        error->setWindowTitle("File type warning!");
        error->exec();
    }
    else {
        std::string size = this->sizeLineEdit->text().toStdString();
        std::string colour = this->colourLineEdit->text().toStdString();
        std::string price = this->priceLineEdit->text().toStdString();
        std::string quantity = this->quantityLineEdit->text().toStdString();
        std::string photograph = this->photographLineEdit->text().toStdString();
        int size1, price1, quantity1;
        try {
            size1 = stoi(size);
            price1 = stoi(price);
            quantity1 = stoi(quantity);
            this->userserv.addCoatToBasket(size1, colour, price1, quantity1, photograph);
            if (!this->filtered)
                this->populateCoatList();
            else
                this->coatListWidget->addItem(this->coatListWidget->takeItem(this->getSelectedIndex()));
        }
        catch (ValidationException& exc) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText(exc.what());
            error->setWindowTitle("Invalid input!");
            error->exec();
        }
        catch (RepositoryException& re) {
            auto* error = new QMessageBox();
            error->setIcon(QMessageBox::Critical);
            error->setText(re.what());
            error->setWindowTitle("Error at adding coat!");
            error->exec();
        }
    }
}

void UserGUI::filterCoat() {
    try {
        std::string price_s = this->priceFilterLineEdit->text().toStdString();
        int price;
        if (price_s.empty()) {
            this->filtered = false;
            this->populateCoatList();
        }
        else {
            this->validator.validateString(price_s);
            price = stoi(price_s);
            this->validator.validCoatPrice(price);
            std::vector<Coat> validCoats;
            this->userserv.getFiltered(validCoats, price);
            if (validCoats.empty()) {
                std::string error;
                error += std::string("The list of valid coats is empty!");
                if (!error.empty())
                    throw UserException(error);
            }
            else {
                this->filtered = true;
                this->coatListWidget->clear();
                for (Coat& coat : validCoats)
                    this->coatListWidget->addItem(QString::fromStdString(std::to_string(coat.getSize())));
            }
        }
    }
    catch (ValidationException& ve) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(ve.what());
        error->setWindowTitle("Validation error!");
        error->exec();
    }
    catch (UserException& ue) {
        auto* error = new QMessageBox();
        error->setIcon(QMessageBox::Critical);
        error->setText(ue.what());
        error->setWindowTitle("Filter error!");
        error->exec();
    }
}

void UserGUI::undoGUI() {
    try {
        this->userserv.undoLastAction();
        this->populateCoatList();
        this->populateBasketList();
    }
    catch (RepositoryException& re) {
        QMessageBox::critical(this, "Error", re.what());
    }
}

void UserGUI::redoGUI() {
    try {
        this->userserv.redoLastAction();
        this->populateCoatList();
        this->populateBasketList();
    }
    catch (RepositoryException& re) {
        QMessageBox::critical(this, "Error", re.what());
    }
}

UserGUI::~UserGUI() = default;