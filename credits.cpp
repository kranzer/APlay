#include "credits.h"
#include "ui_credits.h"

Credits::Credits(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Credits)
{
    ui->setupUi(this);
}

Credits::~Credits()
{
    delete ui;
}

void Credits::on_closeCreditsButton_clicked()
{
    this->close();
}
