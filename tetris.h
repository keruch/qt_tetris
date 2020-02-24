#ifndef TETRIS_H_147891934_73291965_168
#define TETRIS_H_147891934_73291965_168

#include <QWidget>
#include "tetrisboard.h"
#include "tetrispiece.h"

// ?
QT_BEGIN_NAMESPACE
namespace Ui {
    class Tetris;
}
QT_END_NAMESPACE

class Tetris     : public QWidget
{
    Q_OBJECT

public:
    explicit Tetris    (QWidget *parent = nullptr);
    ~Tetris();
private:
    QScopedPointer<Ui::Tetris>     ui_;
private slots:
    void on_quitButton_clicked();
    void on_startButton_clicked();
    void on_pauseButton_clicked();
    void on_frame_levelChanged(int level);
    void on_frame_scoreChanged(int score);
    void on_frame_linesRemovedChanged(int linesRemoved);
};
#endif
