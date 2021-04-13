#include "labelbase.h"

LabelBase::LabelBase(QString nam, double w, double h, double g, FormData *d, QObject *parent) : QObject(parent), name(nam), width(w), height(h), gap(g), data(d)
{
    printer = new TPrinter(name,this);
    dpi=printer->getDpi();
}

void LabelBase::setActions(QAction *actionCfg, QAction *actionCmd, QAction *actionPrint)
{
    connect(actionCfg,SIGNAL(triggered(bool)),this,SLOT(cfgPrinter()));
    connect(actionCmd,SIGNAL(triggered(bool)),this,SLOT(viewCmd()));
    connect(actionPrint,SIGNAL(triggered(bool)),this,SLOT(printLabel()));
}

QString LabelBase::getName()
{
    return name;
}

QString LabelBase::getCod()
{
    QString cod;
    cod.push_back("DIRECTION 1,0\n");
    cod.push_back("CLS\n");
    cod.push_back(QString("SIZE %1 mm,%2 mm\n").arg(width).arg(height));
    cod.push_back(QString("GAP %1 mm\n").arg(gap));
    cod.push_back("CODEPAGE 1251\n");
    cod.push_back("DENSITY 15\n");
    return cod;
}

int LabelBase::getDots(double mm)
{
    return dpi*mm/25;
}

QString LabelBase::ean13(double x, double y, QString ean, double h, double s, int rotation)
{
    QString c;
    if (ean.size()==12){
        c=QString("BARCODE %1,%2,\"EAN13\",%3,2,%7,%4,%5,\"%6\"\n").arg(getDots(x)).arg(getDots(y)).arg(getDots(h)).arg(getDots(s)).arg(getDots(s)).arg(ean).arg(rotation);
    }
    return c;
}

QString LabelBase::print()
{
    return QString("PRINT %1\n").arg(data->count());
}

QString LabelBase::logo(double x, double y)
{
    return QString::fromUtf8("PUTBMP %1,%2, \"logo.BMP\",1,100\n").arg(getDots(x)).arg(getDots(y));
}

QString LabelBase::text(double x, double y, QString t, int size, int rotation)
{
    QString s=t.replace("\"","'");
    return QString::fromUtf8("TEXT %1,%2,\"0\",%6,%3,%4,\"%5\"\n").arg(getDots(x)).arg(getDots(y)).arg(size).arg(size).arg(s).arg(rotation);
}

void LabelBase::cfgPrinter()
{
    DialogSettings d(printer);
    d.setWindowTitle(d.windowTitle()+": "+name);
    d.setLblSize(width,height,gap);
    d.exec();
    dpi=printer->getDpi();
}

void LabelBase::viewCmd()
{
    DialogCmd c(getCod(),printer);
    c.exec();
}

void LabelBase::printLabel()
{
    QString c=getCod();
    printer->printDecode(c);
}
