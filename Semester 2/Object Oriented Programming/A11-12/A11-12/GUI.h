#pragma once

#include <QWidget>
#include "AdminService.h"
#include <QLabel>
#include <QPushButton>
#include "UserService.h"
#include <QListWidget>
#include <QLineEdit>
#include <QRadioButton>
#include "Validator.h"
#include "Basket.h"
#include "Repository.h"
#include <QTableView>
#include <QShortcut>
#include <QHeaderView>

class CoatTableModel : public QAbstractTableModel
{
private:
	Basket* basket;
	
public:
	explicit CoatTableModel(Basket* basket);

	int rowCount(const QModelIndex& parent = QModelIndex()) const;
	int columnCount(const QModelIndex& parent = QModelIndex()) const;
	QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
	QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
	void update();
};

class GUI : public QWidget
{
private:
	AdminService& adminService;
	UserService& userService;
	Validator& validator;
	Repository& repository;
	Basket& basket;

	void initGUI();

	QLabel* titleWidget;
	QPushButton* adminButton;
	QPushButton* userButton;
	
	void showAdmin();
	void showUser();
	void connectSignalsAndSlots();

public:
	explicit GUI(AdminService& adminService, UserService& userService, Validator& validator, Repository& repo, Basket& basket);
	~GUI() override;
};

class AdminGUI : public QWidget
{
private:
	AdminService& adminService;
	Validator& validator;
	Repository& repo;
	Basket& basket;

	void initAdminGUI();

	QLabel* titleWidget;
	QListWidget* coatListWidget;
	QLineEdit* sizeLineEdit, * colourLineEdit, * priceLineEdit, * quantityLineEdit, * photographLineEdit, *priceFilterLineEdit;
	QPushButton* addButton, * deleteButton, * updateButton, * chartButton, *filterButton, *undoButton, *redoButton;
	QShortcut* shortcutUndo, * shortcutRedo;

	void populateList();
	void connectSignalsAndSlots();
	int getSelectedIndex() const;
	void addCoat();
	void deleteCoat();
	void updateCoat();
	void displayChart();
	void undoGUI();
	void redoGUI();

	QWidget* chartWindow;

public:
	explicit AdminGUI(QWidget* parent, AdminService& adminServ, Validator& validator, Repository& repo, Basket& basket);
	~AdminGUI() override;
};

class UserGUI : public QWidget
{
	AdminService& adminserv;
	UserService& userserv;
	Repository& repo;
	Basket& basket;
	Validator& validator;

	void initUserGUI();

	QLabel* titleWidget;
	QListWidget* coatListWidget, *basketListWidget;
	QLineEdit* sizeLineEdit, * colourLineEdit, * priceLineEdit, * quantityLineEdit, * photographLineEdit, *priceFilterLineEdit;
	QPushButton* addButton, * openListButton, * filterButton, *undoButton, *redoButton;
	QRadioButton* csvButton, * htmlButton;
	CoatTableModel* basketListTableModel;
	QShortcut* shortcutUndo, * shortcutRedo;
	QTableView* basketListTable;
	QGridLayout* listAndTableLayout;

	bool repoTypeSelected;
	bool filtered;

	void populateCoatList();
	void populateBasketList();
	void connectSignalsAndSlots();
	int getSelectedIndex() const;
	void addCoat();
	void filterCoat();
	void undoGUI();
	void redoGUI();
	void createTable();

public:
	explicit UserGUI(QWidget* parent, AdminService& adminServ, UserService& userServ, Repository& repo, Basket& basket, Validator& validator1);
	~UserGUI() override;
};