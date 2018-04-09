#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia/QMediaPlayer>
#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    void keyPressEvent(QKeyEvent *e);
    ~MainWindow();

private slots:
    void togglePlayback();

private:
    Ui::MainWindow *ui;
    QMediaPlayer player;
};

#endif // MAINWINDOW_H
