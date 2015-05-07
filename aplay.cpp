#include "aplay.h"
#include "ui_aplay.h"
#include <QFileDialog>
#include <QUrl>
#include <QMediaPlayer>
#include <QStandardPaths>
#include <QTime>
#include <QThread>

APlay::APlay(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::APlay),
    defaultVolume(50)
{
    ui->setupUi(this);
    player = new QMediaPlayer;
    player->setVolume(defaultVolume);
    ui->volumeSlider->setValue(defaultVolume);
}

APlay::~APlay()
{
    delete ui;
}

void APlay::seek(int seconds)
{
    player->setPosition(seconds * 1000);
}

void APlay::on_m_selectFileBut_clicked()
{
    QString selfilter = tr("MP3 files (*.mp3)");
    const QString filePath =
        QFileDialog::getOpenFileName(this, tr("Open File"), QDir::homePath(),
                                     tr("MP3 files (*.mp3);;WAV files (*.wav);;Apple Lossless (*.aac);;All files (*.*)"), &selfilter);
    if (!filePath.isEmpty())
            player->setMedia(QUrl::fromLocalFile(filePath));
}

void APlay::on_actionExit_triggered()
{
    this->close();
}

void APlay::on_m_playBut_clicked()
{
    player->play();
    APlay::ui->durationSlider->setRange(0, player->duration()/1000);
    connect(APlay::ui->durationSlider, SIGNAL(sliderMoved(int)), this, SLOT(seek(int)));
    connect(player, SIGNAL(durationChanged(qint64)), SLOT(durationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), SLOT(positionChanged(qint64)));
    durationChanged(player->duration());
}

void APlay::on_m_pauseBut_clicked()
{
    player->pause();
}

void APlay::durationChanged(qint64 duration)
{
    this->duration = duration / 1000;
    APlay::ui->durationSlider->setMaximum(this->duration);
}

void APlay::positionChanged(qint64 progress)
{
    if (!APlay::ui->durationSlider->isSliderDown()) {
        APlay::ui->durationSlider->setValue(progress / 1000);
    }
    updateDurationInfo(progress / 1000);
}
void APlay::updateDurationInfo(qint64 currentInfo)
{
    QString tStr1;
    QString tStr2;
    if (currentInfo || duration) {
        QTime currentTime(int(currentInfo/3600), int((currentInfo%3600)/60), int(currentInfo%60));
        QTime totalTime(int(duration/3600), int((duration%3600)/60), int(duration%60));
        QString format = "mm:ss";
        if (duration > 3600)
            format = "hh:mm:ss";
        tStr1 = currentTime.toString(format);
        tStr2 = totalTime.toString(format);
    }
    APlay::ui->currentTime->setText(tStr1);
    APlay::ui->totalDuration->setText(tStr2);
}

void APlay::on_volumeSlider_valueChanged(int value)
{
    player->setVolume(value);
}
