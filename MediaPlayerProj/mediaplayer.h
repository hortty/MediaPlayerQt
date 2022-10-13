#ifndef MEDIAPLAYER_H
#define MEDIAPLAYER_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QUrl>
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MediaPlayer; }
QT_END_NAMESPACE

class MediaPlayer : public QMainWindow
{
    Q_OBJECT

public:
    MediaPlayer(QWidget *parent = nullptr);
    ~MediaPlayer();
    void iniciarPlayer();

private slots:
    void on_positionChanged(qint64 position);
    void on_durationChanged(qint64 position);
    void on_stop_clicked();
    void on_start_clicked();
    void on_posicao_sliderMoved(int position);
    void on_volume_sliderMoved(int position);
    void on_pushButton_clicked();

private:
    Ui::MediaPlayer *ui;
    QMediaPlayer *player = new QMediaPlayer;
    QVideoWidget *vw = new QVideoWidget;
};
#endif // MEDIAPLAYER_H
