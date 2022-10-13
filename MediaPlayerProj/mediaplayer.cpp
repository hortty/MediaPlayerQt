#include "mediaplayer.h"
#include "ui_mediaplayer.h"

MediaPlayer::MediaPlayer(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MediaPlayer)
{
    ui->setupUi(this);
    QMessageBox::information(this,"Choose File","Por favor, selecione um arquivo para iniciar o MediaPlayer.");
    ui->volume->hide();
    ui->posicao->hide();
    ui->start->hide();
    ui->stop->hide();
    ui->posicaoLabel->hide();
    ui->volumeLabel->hide();
}

MediaPlayer::~MediaPlayer()
{
    delete ui;
    delete player;
    delete vw;
}

void MediaPlayer::iniciarPlayer()
{
    player->setVideoOutput(vw);
    vw->setGeometry(600,600,600,600);
    vw->show();
    player->play();
    ui->volume->setValue(50);
    player->setVolume(50);
    connect(player, &QMediaPlayer::positionChanged, this, &MediaPlayer::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MediaPlayer::on_durationChanged);
}

void MediaPlayer::on_positionChanged(qint64 position)
{
    ui->posicao->setValue(position);
}

void MediaPlayer::on_durationChanged(qint64 position)
{
    ui->posicao->setMaximum(position);
}

void MediaPlayer::on_stop_clicked()
{
    player->stop();
}

void MediaPlayer::on_start_clicked()
{
    player->play();
}

void MediaPlayer::on_posicao_sliderMoved(int position)
{
    player->setPosition(position);
}

void MediaPlayer::on_volume_sliderMoved(int position)
{
    player->setVolume(position);
    qDebug() << player->volume();
}


void MediaPlayer::on_pushButton_clicked()
{
    QString nome_arquivo = QFileDialog::getOpenFileName(this,"Open",QDir::homePath(),"*.*");
    QFile arquivo(nome_arquivo);
    qDebug() << nome_arquivo << arquivo;
    if(!arquivo.open(QFile::ReadOnly)) {
        QMessageBox::warning(this,"erro","Infelizmente não foi possível abrir o arquivo");
    }
    else {
        ui->pushButton->hide();
        player->setMedia(QUrl::fromLocalFile(nome_arquivo));
        ui->volume->show();
        ui->posicao->show();
        ui->start->show();
        ui->stop->show();
        ui->posicaoLabel->show();
        ui->volumeLabel->show();
        iniciarPlayer();
    }
}

