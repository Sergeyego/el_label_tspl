#ifndef FORMDATA_H
#define FORMDATA_H

#include <QWidget>
#include "modelro.h"
#include <QDataWidgetMapper>

namespace Ui {
class FormData;
}

class FormData : public QWidget
{
    Q_OBJECT

public:
    explicit FormData(QWidget *parent = 0);
    ~FormData();
    QString marka();
    QString diametr();
    QString part();
    QString datePart();
    QString packEd();
    QString packGr();
    QString masEd();
    QString masGr();
    QString eanEd();
    QString eanGr();
    QString count();

private:
    Ui::FormData *ui;
    ModelRo *modelPart;
    QDataWidgetMapper *mapper;

private slots:
    void refreshData(QModelIndex index);

public slots:
    void updPart();
};

#endif // FORMDATA_H
