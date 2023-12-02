#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
class QTableWidgetItem;
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void do_pushButtonSetHeader_clicked();
    void do_pushButtonSetRowsNumber_clicked();
private slots:
    void on_pushButtonTableInit_clicked();

    void on_pushButtonInsert_clicked();

    void on_pushButtonAppend_clicked();

    void on_pushButtonDeleteCurrentRow_clicked();

    void on_pushButtonAutoHeight_clicked();

    void on_pushButtonAutoWidth_clicked();

    void on_pushButtonReadContent2Text_clicked();

    void on_checkBoxEditable_stateChanged(int arg1);

    void on_checkBoxRowStriping_stateChanged(int arg1);

    void on_checkBoxHorizonalHeaderDisplay_stateChanged(int arg1);

    void on_checkBoxVerticalHeadersDisplay_stateChanged(int arg1);

    void on_radioButtonSheetSelectMode_clicked();

    void on_radioButtoRowSelectMode_clicked();

    void statusBarFit(int, int, int, int);
private:
    Ui::MainWindow *ui;
    QList<QTableWidgetItem*> CreateItemsRow(QList<QString>);
};
#endif // MAINWINDOW_H
