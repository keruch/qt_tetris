#include "tetris.h"
#include "./ui_tetris.h"

Tetris::Tetris(QWidget *parent)
    : QWidget{parent}
    , ui_{new Ui::Tetris}
{
    ui_->setupUi(this);
}

Tetris::~Tetris() = default;

void Tetris::on_quitButton_clicked() { QWidget::close(); }

void Tetris::on_startButton_clicked() { ui_->frame->start(); }

void Tetris::on_pauseButton_clicked() { ui_->frame->pause(); }

void Tetris::on_frame_levelChanged(int level) { ui_->lcdLevel->display(level); }

void Tetris::on_frame_scoreChanged(int score) { ui_->lcdScore->display(score); }

void Tetris::on_frame_linesRemovedChanged(int linesRemoved) { ui_->lcdLineRemoved->display(linesRemoved); }
