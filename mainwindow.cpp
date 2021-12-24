#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    loadSettings();

    data = new FormData(this);
    ui->verticalLayoutData->addWidget(data);

    labelE4570 = new LabelE4570(QString::fromUtf8("Этикетка 45*70 пачка"),45,70,2,data,this);
    createActions(labelE4570);

    labelG4570 = new LabelG4570(QString::fromUtf8("Этикетка 45*70 гофрокороб"),45,70,2,data,this);
    createActions(labelG4570);

    labelE5040 = new LabelE5040(QString::fromUtf8("Этикетка 50*40 пачка"),50,40,2.5,data,this);
    createActions(labelE5040);

    labelG5040 = new LabelG5040(QString::fromUtf8("Этикетка 50*40 гофрокороб"),50,40,2.5,data,this);
    createActions(labelG5040);

    labelPal5040 = new LabelPal5040(QString::fromUtf8("Этикетка 50*40 поддон"),50,40,2.5,data,this);
    createActions(labelPal5040);

    ui->actionPart->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));
    connect(ui->actionPart,SIGNAL(triggered(bool)),data,SLOT(updPart()));
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

void MainWindow::createActions(LabelBase *l)
{
    QAction *printAction=ui->menuFile->addAction(QIcon::fromTheme("document-print"), l->getName());
    QAction *viewAction=ui->menuView->addAction(QString::fromUtf8("Команды ")+l->getName());
    QAction *cfgAction=ui->menuCfg->addAction(QString::fromUtf8("Принтер для ")+l->getName());
    l->setActions(cfgAction,viewAction,printAction);
    QToolButton *b = new QToolButton(this);
    b->setDefaultAction(printAction);
    b->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    ui->horizontalLayoutToolButton->addWidget(b);
}

void MainWindow::loadSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    this->restoreGeometry(settings.value("main_geometry").toByteArray());
}

void MainWindow::saveSettings()
{
    QSettings settings("szsm", QApplication::applicationName());
    settings.setValue("main_geometry", this->saveGeometry());
}
