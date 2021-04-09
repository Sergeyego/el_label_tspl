#ifndef LABELS_H
#define LABELS_H

#include <QObject>
#include "labelbase.h"

class LabelE4570 : public LabelBase
{
public:
    LabelE4570(QString nam, double w, double h, double g, FormData *d, QObject *parent);
protected:
    virtual QString getCod();
};

class LabelG4570 : public LabelBase
{
public:
    LabelG4570(QString nam, double w, double h, double g, FormData *d, QObject *parent);
protected:
    virtual QString getCod();
};

#endif // LABELS_H
