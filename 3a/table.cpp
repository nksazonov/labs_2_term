#include "table.h"
#include <QDebug>
#include <QHeaderView>

table::table()
{
    m_table = nullptr;
}

table::table(QTableWidget *table) : QTableWidget()
{
    m_table = table;

    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode( QAbstractItemView::SingleSelection);
}

void table::setSize(int rowCount, int rowHeight, std::vector<int> columnWidths, std::vector<QString> headLabelsStr)
{
    m_table->setRowCount(rowCount);
    m_table->setColumnCount(columnWidths.size());

    for (unsigned int i = 0; i < columnWidths.size(); i++) {
        m_table->setColumnWidth(i, columnWidths[i]);
    }

    QHeaderView *verticalHeader = m_table->verticalHeader();

    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(rowHeight);
    verticalHeader->setVisible(false);


    if (headLabelsStr.size() == 0) return;

    QStringList headLabels;

    for (QString Qst : headLabelsStr) {
        headLabels << Qst;
    }

    m_table->setHorizontalHeaderLabels(headLabels);
}

void table::insertDataRow(std::vector<QString> data, int after)
{
    if (m_table->height() < getRowsHeight() && m_table->width() < getColumnsWidth()+22)
    {
        squeezeColumns(22);
    }

    m_table->insertRow(after);

    for (uint data_idx = 0; data_idx < data.size(); data_idx++)
    {
        QTableWidgetItem * item = new QTableWidgetItem();
        item->setTextAlignment(Qt::AlignCenter);
        item->setText(data[data_idx]);
        m_table->setItem(after, data_idx, item);
    }
}

int table::getRowsHeight()
{
    int height = 75;

    for(int row = 0; row < getTable()->rowCount(); row++)
    {
        height += getTable()->rowHeight(row);
    }

    return height;
}

int table::getColumnsWidth()
{
    int width = 0;

    for(int column = 0; column < getTable()->columnCount(); column++)
    {
        width += getTable()->columnWidth(column);
    }

    return width;
}

void table::squeezeColumns(int shift)
{
    int oneShift = shift/getTable()->columnCount();

    for(int column = 0; column < getTable()->columnCount(); column++)
    {
        getTable()->setColumnWidth(column, getTable()->columnWidth(column) - oneShift);
    }
}


QTableWidget *table::getTable()
{
    return m_table;
}