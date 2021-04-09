#include "labels.h"

LabelE4570::LabelE4570(QString nam, double w, double h, double g, FormData *d, QObject *parent) : LabelBase(nam,w,h,g,d,parent)
{

}

QString LabelE4570::getCod()
{
    QString cod=LabelBase::getCod();
    cod.push_back(logo(2,2));
    cod.push_back(ean13(5,22,data->eanEd()));
    cod.push_back(text(5,39,QString::fromUtf8("Марка - ")+data->marka()));
    cod.push_back(text(5,43,QString::fromUtf8("Диаметр, мм - ")+data->diametr()));
    cod.push_back(text(5,47,QString::fromUtf8("Партия - ")+data->part()));
    cod.push_back(text(5,51,QString::fromUtf8("Тип упаковки - ")+data->packEd()));
    cod.push_back(text(5,55,QString::fromUtf8("Масса нетто, кг - ")+data->masEd()));
    cod.push_back(text(5,59,QString::fromUtf8("Дата изг. - ")+data->datePart()));
    cod.push_back(print());
    return cod;
}

LabelG4570::LabelG4570(QString nam, double w, double h, double g, FormData *d, QObject *parent) : LabelBase(nam,w,h,g,d,parent)
{

}

QString LabelG4570::getCod()
{
    QString cod=LabelBase::getCod();
    cod.push_back(logo(2,2));
    cod.push_back(ean13(5,22,data->eanGr()));
    cod.push_back(text(5,39,QString::fromUtf8("Марка - ")+data->marka()));
    cod.push_back(text(5,43,QString::fromUtf8("Диаметр, мм - ")+data->diametr()));
    cod.push_back(text(5,47,QString::fromUtf8("Партия - ")+data->part()));
    cod.push_back(text(5,51,QString::fromUtf8("Тип упаковки :")));
    cod.push_back(text(5,55,data->packGr()));
    cod.push_back(text(5,59,QString::fromUtf8("Масса нетто, кг - ")+data->masGr()));
    cod.push_back(text(5,63,QString::fromUtf8("Дата изг. - ")+data->datePart()));
    cod.push_back(print());
    return cod;
}
