#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    printerPSmall = new TPrinter("psmall",this);

    loadSettings();

    ui->dateEditBeg->setDate(QDate::currentDate().addDays(-QDate::currentDate().dayOfYear()+1));
    ui->dateEditEnd->setDate(QDate(QDate::currentDate().year(),12,31));

    ui->tableViewPart->verticalHeader()->setDefaultSectionSize(ui->tableViewPart->verticalHeader()->fontMetrics().height()*1.5);

    ui->actionPart->setIcon(this->style()->standardIcon(QStyle::SP_BrowserReload));
    ui->actionPSmall->setIcon(QIcon::fromTheme("document-print"));
    ui->actionGSmall->setIcon(QIcon::fromTheme("document-print"));
    ui->actionExit->setIcon(this->style()->standardIcon(QStyle::SP_DialogCancelButton));

    ui->toolButtonPSmall->setDefaultAction(ui->actionPSmall);
    ui->toolButtonGSmall->setDefaultAction(ui->actionGSmall);
    ui->toolButtonUpd->setDefaultAction(ui->actionPart);

    modelPart = new ModelRo(this);
    ui->tableViewPart->setModel(modelPart);

    mapper = new QDataWidgetMapper(this);

    mapper->setModel(modelPart);

    mapper->addMapping(ui->lineEditPart,1);
    mapper->addMapping(ui->dateEditPart,2);
    mapper->addMapping(ui->lineEditMark,3);
    mapper->addMapping(ui->lineEditDiam,4);
    mapper->addMapping(ui->lineEditPackEd,6);
    mapper->addMapping(ui->lineEditPackGr,7);
    mapper->addMapping(ui->lineEditKvoEd,8);
    mapper->addMapping(ui->lineEditKvoGr,9);
    mapper->addMapping(ui->lineEditEanEd,10);
    mapper->addMapping(ui->lineEditEanGr,11);

    connect(ui->tableViewPart->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),mapper,SLOT(setCurrentModelIndex(QModelIndex)));
    connect(ui->tableViewPart->selectionModel(),SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,SLOT(refreshData(QModelIndex)));

    connect(ui->actionPart,SIGNAL(triggered(bool)),this,SLOT(updPart()));

    connect(ui->actionPSmall,SIGNAL(triggered(bool)),this,SLOT(createPSmallLabel()));
    connect(ui->actionGSmall,SIGNAL(triggered(bool)),this,SLOT(createGSmallLabel()));

    connect(ui->actionSetPrintPSmall,SIGNAL(triggered(bool)),this,SLOT(settingsPrintPSmall()));

    connect(ui->actionViewPSmall,SIGNAL(triggered(bool)),this,SLOT(viewCmdPSmall()));
    connect(ui->actionViewGSmall,SIGNAL(triggered(bool)),this,SLOT(viewCmdGSmall()));

    connect(ui->actionExit,SIGNAL(triggered(bool)),this,SLOT(close()));

    updPart();
}

MainWindow::~MainWindow()
{
    saveSettings();
    delete ui;
}

QString MainWindow::getCodPSmall(int dpi)
{
    QString cod;
    cod.push_back("DIRECTION 1,0\n");
    cod.push_back("CLS\n");
    cod.push_back("SIZE 45 mm,70 mm\n");
    cod.push_back("GAP 2 mm\n");
    cod.push_back("CODEPAGE 1251\n");
    cod.push_back("DENSITY 15\n");
    cod.push_back(QString::fromUtf8("PUTBMP %1,%2, \"logo.BMP\",1,100\n").arg(getDots(2,dpi)).arg(getDots(2,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Марка - %3\"\n").arg(getDots(5,dpi)).arg(getDots(39,dpi)).arg(ui->lineEditMark->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Диаметр, мм - %3\"\n").arg(getDots(5,dpi)).arg(getDots(43,dpi)).arg(QLocale().toString(ui->lineEditDiam->text().toDouble(),'f',1)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Партия - %3\"\n").arg(getDots(5,dpi)).arg(getDots(47,dpi)).arg(ui->lineEditPart->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Тип упаковки - %3\"\n").arg(getDots(5,dpi)).arg(getDots(51,dpi)).arg(ui->lineEditPackEd->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Масса нетто, кг - %3\"\n").arg(getDots(5,dpi)).arg(getDots(55,dpi)).arg(ui->lineEditKvoEd->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Дата изг. - %3\"\n").arg(getDots(5,dpi)).arg(getDots(59,dpi)).arg(ui->dateEditPart->date().toString("dd.MM.yyyy")));
    if (!ui->lineEditEanEd->text().isEmpty()){
        cod.push_back(QString("BARCODE %1,%2,\"EAN13\",%3,2,0,%4,%5,\"%6\"\n").arg(getDots(5,dpi)).arg(getDots(22,dpi)).arg(getDots(9,dpi)).arg(getDots(0.375,dpi)).arg(getDots(0.375,dpi)).arg(ui->lineEditEanEd->text().left(12)));
    }
    cod.push_back(QString("PRINT %1\n").arg(ui->spinBox->value()));
    return cod;
}

QString MainWindow::getCodGSmall(int dpi)
{
    QString cod;
    cod.push_back("DIRECTION 1,0\n");
    cod.push_back("CLS\n");
    cod.push_back("SIZE 45 mm,70 mm\n");
    cod.push_back("GAP 2 mm\n");
    cod.push_back("CODEPAGE 1251\n");
    cod.push_back("DENSITY 15\n");
    cod.push_back(QString::fromUtf8("PUTBMP %1,%2, \"logo.BMP\",1,100\n").arg(getDots(2,dpi)).arg(getDots(2,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Марка - %3\"\n").arg(getDots(5,dpi)).arg(getDots(39,dpi)).arg(ui->lineEditMark->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Диаметр, мм - %3\"\n").arg(getDots(5,dpi)).arg(getDots(43,dpi)).arg(QLocale().toString(ui->lineEditDiam->text().toDouble(),'f',1)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Партия - %3\"\n").arg(getDots(5,dpi)).arg(getDots(47,dpi)).arg(ui->lineEditPart->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Тип упаковки :\"\n").arg(getDots(5,dpi)).arg(getDots(51,dpi)));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"%3\"\n").arg(getDots(5,dpi)).arg(getDots(55,dpi)).arg(ui->lineEditPackGr->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Масса нетто, кг - %3\"\n").arg(getDots(5,dpi)).arg(getDots(59,dpi)).arg(ui->lineEditKvoGr->text()));
    cod.push_back(QString::fromUtf8("TEXT %1,%2,\"0\",0,10,10,\"Дата изг. - %3\"\n").arg(getDots(5,dpi)).arg(getDots(63,dpi)).arg(ui->dateEditPart->date().toString("dd.MM.yyyy")));
    if (!ui->lineEditEanGr->text().isEmpty()){
        cod.push_back(QString("BARCODE %1,%2,\"EAN13\",%3,2,0,%4,%5,\"%6\"\n").arg(getDots(5,dpi)).arg(getDots(22,dpi)).arg(getDots(9,dpi)).arg(getDots(0.375,dpi)).arg(getDots(0.375,dpi)).arg(ui->lineEditEanGr->text().left(12)));
    }
    cod.push_back(QString("PRINT %1\n").arg(ui->spinBox->value()));
    return cod;
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


int MainWindow::getDots(double mm, int dpi)
{
    return dpi*mm/25;
}

void MainWindow::updPart()
{
    QSqlQuery query;
    query.prepare("select p.id, p.n_s, p.dat_part, e.marka, p.diam, i.nam, ep.pack_ed, ep.pack_group, ep.mass_ed, ep.mass_group, ee.ean_ed, ee.ean_group "
                  "from parti as p "
                  "inner join elrtr as e on p.id_el=e.id "
                  "inner join istoch as i on p.id_ist=i.id "
                  "inner join el_pack as ep on ep.id=p.id_pack "
                  "left join ean_el ee on ee.id_el = p.id_el and ee.id_diam = (select d.id from diam d where d.diam=p.diam) and ee.id_pack = p.id_pack "
                  "where p.dat_part between :d1 and :d2 "
                  "order by p.dat_part, p.n_s");
    query.bindValue(":d1",ui->dateEditBeg->date());
    query.bindValue(":d2",ui->dateEditEnd->date());
    if (modelPart->execQuery(query)){
        ui->tableViewPart->setColumnHidden(0,true);
        ui->tableViewPart->resizeColumnsToContents();
        modelPart->setHeaderData(1,Qt::Horizontal,QString::fromUtf8("Парт."));
        modelPart->setHeaderData(2,Qt::Horizontal,QString::fromUtf8("Дата"));
        modelPart->setHeaderData(3,Qt::Horizontal,QString::fromUtf8("Марка"));
        modelPart->setHeaderData(4,Qt::Horizontal,QString::fromUtf8("Диам."));
        modelPart->setHeaderData(5,Qt::Horizontal,QString::fromUtf8("Источник"));
        modelPart->setHeaderData(6,Qt::Horizontal,QString::fromUtf8("Упаковка"));
        for (int i=7; i<modelPart->columnCount(); i++){
            ui->tableViewPart->setColumnHidden(i,true);
        }
        if (modelPart->rowCount()){
            ui->tableViewPart->selectRow(modelPart->rowCount()-1);
        }
    }
}

void MainWindow::refreshData(QModelIndex /*index*/)
{
    ui->spinBox->setValue(1);
}


void MainWindow::createPSmallLabel()
{
    QString c=getCodPSmall(printerPSmall->getDpi());
    printerPSmall->printDecode(c);
}

void MainWindow::createGSmallLabel()
{
    QString c=getCodGSmall(printerPSmall->getDpi());
    printerPSmall->printDecode(c);
}

void MainWindow::settingsPrintPSmall()
{
    DialogSettings d(printerPSmall);
    d.setWindowTitle(d.windowTitle()+": "+ui->actionSetPrintPSmall->text());
    d.setLblSize(70,45,2);
    d.exec();
}

void MainWindow::viewCmdPSmall()
{
    DialogCmd c(getCodPSmall(printerPSmall->getDpi()),printerPSmall);
    c.exec();
}

void MainWindow::viewCmdGSmall()
{
    DialogCmd c(getCodGSmall(printerPSmall->getDpi()),printerPSmall);
    c.exec();
}
