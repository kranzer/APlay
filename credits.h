#ifndef CREDITS_H
#define CREDITS_H

#include <QWidget>
#include <QtWidgets>
#include <QString>

namespace Ui {
class Credits;
}

class Credits : public QWidget
{
    Q_OBJECT

public:
    explicit Credits(QWidget *parent = 0);
    ~Credits();

private slots:
    void on_closeCreditsButton_clicked();

private:
    Ui::Credits *ui;
};


#endif // CREDITS_H
