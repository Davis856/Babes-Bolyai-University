#include <QFont>
#include "TableModel.h"
#include <QBrush>

TableModel::TableModel(RepoStars& repository, QObject* parent) : repository{ repository }, QAbstractTableModel(parent), indexes{ std::vector<int>{} } {
}

TableModel::~TableModel() {

}

int TableModel::rowCount(const QModelIndex& parent) const {
    return this->repository.getStars().size();
}

int TableModel::columnCount(const QModelIndex& parent) const {
    return 5;
}

QVariant TableModel::data(const QModelIndex& index, int role) const {
    int row = index.row();
    int column = index.column();
    if (role == Qt::DisplayRole)
    {
        std::vector<Star> Stars = this->repository.getStars();
        Star f = Stars[row];
        switch (column)
        {
        case 0:
            return QString::fromStdString(f.getName());

        case 1:
            return QString::fromStdString(f.getCons());

        case 2:
            return QString::fromStdString(std::to_string(f.getRA()));

        case 3:
            return QString::fromStdString(std::to_string(f.getDec()));

        case 4:
            return QString::fromStdString(std::to_string(f.getDiameter()));

        default:
            break;

        }

    }

    return QVariant{};
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            switch (section) {
            case 0:
                return QString{ "Name" };

            case 1:
                return QString{ "Constellation" };

            case 2:
                return QString{ "RA" };

            case 3:
                return QString{ "Dec" };

            case 4:
                return QString{ "Diameter" };

            default:
                break;
            }
        }
    }

    return QVariant{};
}

Qt::ItemFlags TableModel::flags(const QModelIndex& index) const {
    return Qt::ItemIsSelectable | Qt::ItemIsEditable | Qt::ItemIsEnabled;
}

void TableModel::updateInternalData() {
    endResetModel();
}

bool TableModel::setData(const QModelIndex& index, const QVariant& value, int role) {

    return true;
}

bool TableModel::addBackground(int idx) {
    this->indexes.push_back(idx);

    return true;
}