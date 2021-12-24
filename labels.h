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

class LabelE5040 : public LabelBase
{
public:
    LabelE5040(QString nam, double w, double h, double g, FormData *d, QObject *parent);
protected:
    virtual QString getCod();
};

class LabelG5040 : public LabelBase
{
public:
    LabelG5040(QString nam, double w, double h, double g, FormData *d, QObject *parent);
protected:
    virtual QString getCod();
};

class LabelPal5040 : public LabelBase
{
public:
    LabelPal5040(QString nam, double w, double h, double g, FormData *d, QObject *parent);
protected:
    virtual QString getCod();
};
#endif // LABELS_H
