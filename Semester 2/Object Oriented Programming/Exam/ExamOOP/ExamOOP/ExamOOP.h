#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ExamOOP.h"

class ExamOOP : public QMainWindow
{
    Q_OBJECT

public:
    ExamOOP(QWidget *parent = Q_NULLPTR);

private:
    Ui::ExamOOPClass ui;
};
