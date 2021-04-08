#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlQuery>
#include <QDataWidgetMapper>
#include <QComboBox>
#include <QSettings>
#include <QMap>
#include <QCompleter>
#include "dialogsettings.h"
#include "modelro.h"
#include "dialogcmd.h"
#include "tprinter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    ModelRo *modelPart;
    QDataWidgetMapper *mapper;
    QString getCodPSmall(int dpi);
    QString getCodGSmall(int dpi);
    void loadSettings();
    void saveSettings();
    TPrinter *printerPSmall;
    int getDots(double mm, int dpi);

private slots:
    void updPart();
    void refreshData(QModelIndex index);
    void createPSmallLabel();
    void createGSmallLabel();
    void settingsPrintPSmall();
    void viewCmdPSmall();
    void viewCmdGSmall();
};

#endif // MAINWINDOW_H
