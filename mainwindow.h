#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QStyle>
#include <QToolButton>
#include "formdata.h"
#include "labels.h"

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
    FormData *data;
    LabelE4570 *labelE4570;
    LabelG4570 *labelG4570;
    void createActions(LabelBase *l);

    void loadSettings();
    void saveSettings();
};

#endif // MAINWINDOW_H
