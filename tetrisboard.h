#ifndef TETRISBOARD_H_147891934_73291965_168
#define TETRISBOARD_H_147891934_73291965_168

#include "tetrispiece.h"
#include <QFrame>
#include <QBasicTimer>
#include <QTimerEvent>
#include <QPainter>
#include <QEvent>
#include <QKeyEvent>
//#include <QGamepad>

class TetrisBoard : public QFrame
{
    Q_OBJECT
public:
    explicit TetrisBoard(QWidget *parent = nullptr);

signals:
    void scoreChanged(int score);
    void levelChanged(int level);
    void linesRemovedChanged(int numLines);

public slots:
    void start();
    void pause();

/*
private slots:
    void bLeft();
    void bRight();
    void bRotateLeft();
    void bRotateRight();
    void bDropDown();
    void bDown();
    void bStart();
    void bPause();
    void bQuit();
*/
private:
    enum Coordinates { Height = 22, Width = 10 };

    TetrisShape& shapeAt(int x, int y) { return board[x][y]; }
    inline int timeout() const { return 500/(level + 1); }
    inline int squareHeight() const { return contentsRect().height() / Height; }
    inline int squareWidth() const { return contentsRect().width() / Width ; }
    void draw(QPainter& painter, int x, int y, TetrisShape shape) const;
    bool tryMove(const TetrisPiece& piece, int x, int y);
    void removeFullLines();
    void pieceDropped();
    void newPiece();
    void oneLineDown();
    void clear();

    bool started;
    bool paused;
    bool waiting; // waiting a new piece
    int level;
    int score;
    int linesRemoved;
    int curX;
    int curY;
    int pieceNum;

    
    TetrisPiece current;
    TetrisPiece next;

    TetrisShape board[Width][Height];

    QBasicTimer timer;

    //QGamepad gamepad;

protected:
    void paintEvent(QPaintEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

};

#endif
