#include "tetrisboard.h"
#include <iostream>

TetrisBoard::TetrisBoard(QWidget *parent)
    : QFrame(parent)
{
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    setFocusPolicy(Qt::StrongFocus);
    started = false;
    paused = false;

    clear();

    next.getRandomShape();
}

void TetrisBoard::start()
{
    //log
    std::cout << "Start slot called.\n";

    clear();

    pieceNum = 0;
    started = true;
    paused = false;
    waiting = true;
    level = 1;
    score = 0;
    linesRemoved = 0;

    emit levelChanged(level);
    emit scoreChanged(score);
    emit linesRemovedChanged(linesRemoved);

    timer.start(timeout(), this);
}

void TetrisBoard::pause()
{
    //log
    std::cout << "Pause slot called.\n";

    if(paused) {
        timer.start(timeout(),this);
    }
    else {
        timer.stop();
    }
    paused = !paused;
}

void TetrisBoard::oneLineDown()
{
    if(!tryMove(current, curX, curY+1)) {
        pieceDropped();
    }
    else {
        ++curY;
    }
}

void TetrisBoard::pieceDropped()
{
    for (int i = 0; i < 4; ++i) {
        int x = curX + current.x(i);
        int y = curY - current.y(i);
        shapeAt(x, y) = current.shape();
    }
    waiting = true;

    //log
    std::cout << "Piece " << pieceNum << " dropped.\n";

    removeFullLines();
}

void TetrisBoard::removeFullLines()
{
    int numFullLines = 0;
    for(int j = 0; j < Height; ++j) {
        bool full = true;
        for(int i = 0; i < Width; ++i)
            if(shapeAt(i, j) == NoShape) {
                full = false;
                break;
            }
        if(full) {
            ++numFullLines;
            for(int k = j; k > 1; --k)
                for(int i = 0; i < Width; ++i)
                    shapeAt(i, k) = shapeAt(i, k - 1);
            for(int i = 0; i < Width; ++i)
                shapeAt(i, 0) = NoShape;
        }
    }

    if(numFullLines > 0) {
        linesRemoved += numFullLines;
        score += (numFullLines == 4) * 15 + (numFullLines % 4) * 10; //18 for tetris, 12 for one
        level += linesRemoved / 10; //++level every 10 lines
        emit levelChanged(level);
        emit scoreChanged(score);
        emit linesRemovedChanged(linesRemoved);

        //log
        std::cout << "Removed " << numFullLines << " lines. " << score << " score added.\n";

        timer.start(timeout(), this);
        current.initShape(NoShape);
    }

}

void TetrisBoard::timerEvent(QTimerEvent *event)
{
    if (event->timerId() == timer.timerId()) {
        if (waiting) {
            newPiece();
            waiting = false;
        }
        else {
            oneLineDown();   
        }
        update();
    }
    else {
        QWidget::timerEvent(event);
    }
}

void TetrisBoard::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);
    QPainter painter{this};

    for(int i = 0; i < Width; ++i)
        for(int j = 0; j < Height; ++j)
            if(shapeAt(i, j) != NoShape)
                draw(painter, i * squareWidth(), j * squareHeight(), board[i][j]);

    if(current.shape() != NoShape) {
        for(int i = 0; i < 4; ++i) {
            int x = curX + current.x(i);
            int y = curY - current.y(i);
            draw(painter, x * squareWidth(),
                       y * squareHeight(),
                       current.shape());
        }
    }

}

void TetrisBoard::draw(QPainter& painter, int x, int y, TetrisShape shape) const
{
    constexpr QRgb colors[]{0xFFFFFF/*for NoShape*/, 0xCC6666, 0x66CC66, 0x6666CC,
                            0xCCCC66, 0xCC66CC, 0x66CCCC, 0xDAAA00};
    painter.fillRect(x + 1, y + 1, squareWidth() - 1, squareHeight() - 1, colors[shape]);
    painter.drawRect(x, y, squareWidth(), squareHeight());
}

void TetrisBoard::clear()
{
    for(int i = 0; i < Width; ++i)
        for(int j = 0; j < Height; ++j)
            board[i][j] = NoShape;
}

void TetrisBoard::newPiece()
{
    ++pieceNum;
    current = next;
    curX = Width / 2;
    curY = 0;
    next.getRandomShape();
    //TODO: next.showNext();

    //log
    std::cout << "Creating piece #" << pieceNum << " with shape " << current.shape() << " in (" << curX << "; " << curY << ").\n";

    if (!tryMove(current, curX, curY)) {
        timer.stop();
        started = false;

        //log
        std::cout << "newPiece(): failed to create new piece. Stopeed.\n";
    }
    else {
        //log
        std::cout << "Piece created.\n";
    }
}

bool TetrisBoard::tryMove(const TetrisPiece& piece, int x, int y)
{
    for(int i = 0; i < 4; ++i) {
        int newX = x + piece.x(i);
        int newY = y - piece.y(i);
        if (newX < 0 || newX > Width-1 || newY < -2 || newY > Height-1) {
            return false;
        }
        if (shapeAt(newX, newY) != NoShape && newY >= 0) {
            return false;
        }
    }
    return true;
}

void TetrisBoard::keyPressEvent(QKeyEvent *event)
{
    if (!started || paused || current.shape() == NoShape) {
        QFrame::keyPressEvent(event);
        return;
    }

    switch (event->key()) {
    case Qt::Key_Left:
        if(tryMove(current, curX - 1, curY))
            --curX;
        break;
    case Qt::Key_Right:
        if(tryMove(current, curX + 1, curY))
            ++curX;
        break;
    case Qt::Key_Down:
        if(!tryMove(current.rotate(TetrisPiece::right), curX, curY))
            current.rotate(TetrisPiece::left);
        break;
    case Qt::Key_Up:
        if(!tryMove(current.rotate(TetrisPiece::left), curX, curY))
            current.rotate(TetrisPiece::right);
        break;
//    case Qt::Key_Space:
//        dropDown();
//        break;

    case Qt::Key_D:
        oneLineDown();
        break;
    default:
        QFrame::keyPressEvent(event);
    }

//    std::cout << "\n\n" << event->key() << "\n\n";
    update();
}
