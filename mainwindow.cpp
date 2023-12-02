#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QApplication>
#include <QFont>
#include <QMessageBox>
#include <QDate>
#include <QRandomGenerator64>
#include <Qlabel>
#include <QLayout>
#include <QHBoxLayout>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setMaximum(99999999);
    connect(ui->pushButtonSetHeader, SIGNAL(clicked()), this, SLOT(do_pushButtonSetHeader_clicked()));
    connect(ui->pushButtonSetRowsNumber, SIGNAL(clicked()), this, SLOT(do_pushButtonSetRowsNumber_clicked()));

    this->setStatusBar(new QStatusBar(this));
    QWidget *statusWidget = new QWidget(this);
    this->statusBar()->addPermanentWidget(statusWidget, 1);
    QLayout* layout = new QHBoxLayout(statusWidget);
    QLabel *labelCellIndex = new QLabel("行\t列\t");
    layout->addWidget(labelCellIndex);
    QLabel *labelCellType = new QLabel("类型：\t");
    layout->addWidget(labelCellType);
    QLabel *labelId = new QLabel("学生Id:\t");
    layout->addWidget(labelId);
    connect(ui->tableWidget, SIGNAL(currentCellChanged(int, int, int, int)), this, SLOT(statusBarFit(int, int, int, int)));
//    this->dumpObjectTree();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::do_pushButtonSetHeader_clicked() {
    ui->tableWidget->clear();
    QStringList headerText;
    headerText << "姓名" << "性别" << "出生日期" << "民族" << "分数" << "是否为党员";
        int size = headerText.size();
    ui->tableWidget->setColumnCount(size);
    ui->tableWidget->setHorizontalHeaderLabels(headerText);
    for (int i = 0; i < size; i++) {
        QTableWidgetItem * headerItem = new QTableWidgetItem(headerText[i]);
        QFont font = headerItem->font();
        font.setBold(true);
        font.setPointSize(11);
        headerItem->setFont(font);
        headerItem->setForeground(QBrush(Qt::red));  // foreground字体颜色
        headerItem->setBackground(Qt::blue);
        ui->tableWidget->setHorizontalHeaderItem(i, headerItem);
    }
    ui->tableWidget->setRowCount(10);  // 默认10行
}

void MainWindow::do_pushButtonSetRowsNumber_clicked() {
    if (ui->spinBox->value() > 0)
        ui->tableWidget->setRowCount(ui->spinBox->value());
    else {
        QMessageBox::information(this, "警告", "请确认值是否正确!");
    }
}

void MainWindow::on_pushButtonTableInit_clicked()
{
    ui->tableWidget->clearContents();  // 不清空表头
    QDate birth(2000, 2, 2);
    QRandomGenerator qrg = QRandomGenerator(1);
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        QString strName = QString("学生%1").arg(i);
                              QString strGender = QString("%1").arg(i % 2?"男":"女");
        QString strBirth = QString("%1").arg(birth.toString());
        QString strPeople = QString("汉族");
        QString mark = QString::number(qrg.bounded(60, 100));
        // QRandomGenerator::global()->bounded(low, high);
        QString isParty = QString("%1").arg(i%2?"是":"否");
        QList<QString> strList = {strName, strGender, strBirth, strPeople, mark, isParty};
        int n = strList.size();
        QList<QTableWidgetItem*> items = CreateItemsRow(strList);
        for (int j = 0; j < n; j++)
            ui->tableWidget->setItem(i, j, items[j]);
    }
}

QList<QTableWidgetItem*> MainWindow::CreateItemsRow(QList<QString> itemsText)
{
    QList<QTableWidgetItem*> list;
    for (auto& str: itemsText) {
        list.append(new QTableWidgetItem(str));
        // list.append(new QTableWidgetItem(str, type1000开始));
    }
    return list;
}




void MainWindow::on_pushButtonInsert_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->currentIndex().row());
    ui->tableWidget->setCurrentIndex(ui->tableWidget->currentIndex().sibling(ui->tableWidget->currentIndex().row()-1, ui->tableWidget->currentIndex().column()));
}


void MainWindow::on_pushButtonAppend_clicked()
{
    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
}


void MainWindow::on_pushButtonDeleteCurrentRow_clicked()
{
    int currentRowIndex = ui->tableWidget->currentIndex().row();
    if (currentRowIndex >= 0)
        ui->tableWidget->removeRow(currentRowIndex);  // 删除一行
}




void MainWindow::on_pushButtonAutoHeight_clicked()
{
    ui->tableWidget->resizeRowsToContents();
}




void MainWindow::on_pushButtonAutoWidth_clicked()
{
    ui->tableWidget->resizeColumnsToContents();
}


void MainWindow::on_pushButtonReadContent2Text_clicked()
{
    ui->TextEdit->clear();
    int col = ui->tableWidget->columnCount();
    int row = ui->tableWidget->rowCount();
    ui->TextEdit->setWordWrapMode(QTextOption::WrapMode::NoWrap);
    for (int j = 0; j < col; j++) {
        QTableWidgetItem *item = ui->tableWidget->horizontalHeaderItem(j);
        ui->TextEdit->insertPlainText(item?item->text() + "\t":"\t");
    }
    ui->TextEdit->appendPlainText("");
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            QTableWidgetItem *item = ui->tableWidget->item(i, j);
            ui->TextEdit->insertPlainText(item?item->text() + "\t":"\t");
        }
        ui->TextEdit->appendPlainText("");
    }
}


void MainWindow::on_checkBoxEditable_stateChanged(int arg1)
{
    if (arg1) {
    ui->tableWidget->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked);  // 双击或选中后单击
    }
    else {
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}


void MainWindow::on_checkBoxRowStriping_stateChanged(int arg1)
{
    ui->tableWidget->setAlternatingRowColors(arg1);
}

void MainWindow::on_checkBoxHorizonalHeaderDisplay_stateChanged(int arg1)
{
    ui->tableWidget->horizontalHeader()->setHidden(arg1);
}


void MainWindow::on_checkBoxVerticalHeadersDisplay_stateChanged(int arg1)
{
    ui->tableWidget->verticalHeader()->setHidden(arg1);
}

void MainWindow::on_radioButtonSheetSelectMode_clicked()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectItems);
}


void MainWindow::on_radioButtoRowSelectMode_clicked()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
}

void MainWindow::statusBarFit(int row, int col, int lastrow, int lastcol)
{
    Q_UNUSED(lastrow);
    Q_UNUSED(lastcol);
    QList<QLabel*> labelList = this->statusBar()->findChildren<QLabel*>(Qt::FindChildrenRecursively); // 获取label
    labelList[0]->setText(QString("行:%1, 列:%2").arg(row+1).arg(col+1));
    labelList[1]->setText(QString("类型:") + ui->tableWidget->horizontalHeaderItem(col)->text());
    QString const &name = ui->tableWidget->item(row, 0)->text();
    labelList[2]->setText(QString("编号:") + name.right(name.length() - name.indexOf("学生") - QString("学生").length()));
}

