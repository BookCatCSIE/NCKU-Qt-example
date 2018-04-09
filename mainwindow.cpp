#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Toggle playback mode while pushbutton clicked, use Qt4 style connect(Only use this syntax if Qt5 style not work).
    connect(ui->pushButton, SIGNAL(clicked(bool)), this, SLOT(togglePlayback()));

    // Change slider position while music playing, use Qt5 style connect function(RECOMMAND!)
    connect(&player, &QMediaPlayer::positionChanged, ui->horizontalSlider, &QSlider::setSliderPosition);

    // Change music location while slider position changed.
    connect(ui->horizontalSlider, &QSlider::sliderMoved, &player, &QMediaPlayer::setPosition);

    // Set slider range while music file loaded.
    // This part use C++11 lambda expression, it's advanced and optional, search for it if you're interested.
    connect(&player, &QMediaPlayer::durationChanged, [&](qint64 duration){
        ui->horizontalSlider->setRange(0, duration);
    });

    // Change time text while music playing.
    connect(&player, &QMediaPlayer::positionChanged, [&](qint64 position){
        ui->label_2->setText(QString("%1:%2").arg(position / 1000 / 60, 2, 10, QChar('0')).arg(position / 1000 % 60, 2, 10, QChar('0')));
    });

    // Change play button state
    connect(&player, &QMediaPlayer::stateChanged, [&](QMediaPlayer::State status) {
        if(status == QMediaPlayer::PlayingState) {
            ui->pushButton->setText("Pause");
        }
        else {
            ui->pushButton->setText("Play");
        }
    });

    // Load music from resource file: res.qrc
    player.setMedia(QMediaContent(QUrl("qrc:/music/resources/Cutie Panther.m4a")));

    // Set the music position.
    player.setPosition(67140);
}

// This function will be called when key pressed
void MainWindow::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_P) {
        // slot functions can also be called directly
        togglePlayback();
    }
}

MainWindow::~MainWindow()
{
    player.stop();
    delete ui;
}

void MainWindow::togglePlayback()
{
    ui->label->setText("\\Qt Python わたし/");
    if(player.state() == QMediaPlayer::PlayingState) {
        player.pause();
    }
    else {
        player.play();
    }
}
