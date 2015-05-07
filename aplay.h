#ifndef APLAY_H
#define APLAY_H

#include <QStringList>
#include <QMainWindow>
#include <QMediaPlayer>
#include <QThread>

namespace Ui {
class APlay;
}

class APlay : public QMainWindow
{
    Q_OBJECT

public:
    explicit APlay(QWidget *parent = 0);
    QMediaPlayer* player;
    QStringList codecs;
    ~APlay();


public slots:
    void seek(int);

    void positionChanged(qint64);

    void durationChanged(qint64);

    void updateDurationInfo(qint64);

private slots:
    void on_m_selectFileBut_clicked();

    void on_actionExit_triggered();

    void on_m_playBut_clicked();

    void on_m_pauseBut_clicked();

    void on_volumeSlider_valueChanged(int value);

private:
    Ui::APlay *ui;
    qint64 duration;
    int defaultVolume;

};

#endif // APLAY_H
