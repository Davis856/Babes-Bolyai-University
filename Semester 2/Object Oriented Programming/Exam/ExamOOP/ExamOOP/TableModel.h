#pragma once
#include <QAbstractTableModel>
#include "RepoStars.h"

class TableModel : public QAbstractTableModel {

private:
    RepoStars& repository;
    std::vector<int> indexes;

public:

    TableModel(RepoStars& repository, QObject* parent = NULL);

    ~TableModel();

    // number of rows
    int rowCount(const QModelIndex& parent = QModelIndex{}) const override;

    // number of columns
    int columnCount(const QModelIndex& parent = QModelIndex{}) const override;

    // Value at a given position
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    // add header data
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // will be called when a cell is edited
    bool setData(const QModelIndex& index, const QVariant& value, int role = Qt::EditRole) override;

    bool addBackground(int idx);

    // used to set certain properties of a cell
    Qt::ItemFlags flags(const QModelIndex& index) const override;

    void updateInternalData();
};
