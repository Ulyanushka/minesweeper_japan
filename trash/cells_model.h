#ifndef CELLS_MODEL_H
#define CELLS_MODEL_H

#include <QObject>
#include <QAbstractTableModel>
#include <QStandardItem>

/*
class CellItem : public QStandardItem
{
    Q_OBJECT
public:
    CellItem(QStandardItem* parent = nullptr) : QStandardItem() {}
    ~CellItem();

    QVariant data(int role = Qt::UserRole + 1) const override;
    void setData(const QVariant &value, int role = Qt::UserRole + 1) override;

private:
    void SetMine() { is_mine = true; }
    void SetNearMinesCounter(int counter) { near_mines_counter = counter; }

    bool IsMine() const { return is_mine; }
    int GetNearMinesCounter() const { return near_mines_counter; }

private:

    bool is_mine = false;
    int near_mines_counter = 0;
};
*/
/*
class CellsModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    CellsModel(int rows, int columns, QObject* parent = nullptr);
    ~CellsModel();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /*
    enum CustomRoles{
        RoleType=Qt::UserRole+1,
        ButtonRole,
        CheckboxRole,
    };
*/
/*
private:
    int rows;
    int columns;
};
*/
#endif // CELLS_MODEL_H
