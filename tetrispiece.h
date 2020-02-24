#ifndef TETRISPIECE_H_147891934_73291965_168
#define TETRISPIECE_H_147891934_73291965_168

#include <QtGlobal> // for qint8
#include <random> // for mt and distributions
#include <QRandomGenerator>

enum TetrisShape : int {
    NoShape, LShape, MLshape, ZShape, MZShape, IShape, SShape, TShape };

class TetrisPiece
{
public:
    enum Direction {
        left, right };

    explicit TetrisPiece(TetrisShape shape = NoShape);

    TetrisPiece rotate(Direction dir);
    void initShape(TetrisShape shape);

    inline qint8 x(int i) const { return  coordinates[i][0]; }
    inline qint8 y(int i) const { return  coordinates[i][1]; }
    inline qint8 maxX() const { return qMax(qMax(x(0), x(1)), qMax(x(2), x(3))); }
    inline qint8 minX() const { return qMin(qMin(x(0), x(1)), qMin(x(2), x(3))); }
    inline qint8 maxY() const { return qMax(qMax(y(0), y(1)), qMax(y(2), y(3))); }
    inline qint8 minY() const { return qMin(qMin(y(0), y(1)), qMin(y(2), y(3))); }
    inline TetrisShape shape() const { return pieceShape; }
    inline void getRandomShape()
    {
        std::uniform_int_distribution<int> dist(1, 7);
        initShape(TetrisShape{dist(*QRandomGenerator::global())});
    }

private:
    qint8 coordinates[4][2];
    TetrisShape pieceShape;
};

#endif
