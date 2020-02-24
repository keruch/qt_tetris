    #include "tetrispiece.h"

TetrisPiece::TetrisPiece(TetrisShape shape) :
    pieceShape{shape}
{}

/*   left rotation: x ->  y
 *                  y -> -x
 *
 *  right rotation: x -> -y
 *                  y ->  x
 */
TetrisPiece TetrisPiece::rotate(Direction dir)
{
    for(int i = 0; i < 4; ++i) {
        std::swap(coordinates[i][0], coordinates[i][1]);
        coordinates[i][dir] *= -1;
    }
    return *this;
}

void TetrisPiece::initShape(TetrisShape shape)
{
    // all existing shapes
    constexpr qint8 shapes[8][4][2]{
        {{ 0, 0 }, { 0, 0 }, { 0, 0 }, { 0, 0 }},
        {{ 0, 1 }, { 0, 0 }, { 0,-1 }, { 1,-1 }},
        {{ 0, 1 }, { 0, 0 }, { 0,-1 }, {-1,-1 }},
        {{-1, 1 }, { 0, 1 }, { 0, 0 }, { 1, 0 }},
        {{ 1, 1 }, { 0, 1 }, { 0, 0 }, {-1, 0 }},
        {{ 0, 2 }, { 0, 1 }, { 0, 0 }, { 0,-1 }},
        {{ 0, 0 }, { 0, 1 }, { 1, 1 }, { 1, 0 }},
        {{-1, 0 }, { 0, 0 }, { 1, 0 }, { 0, 1 }}
    };
    for(int i = 0; i < 4; ++i) {
        coordinates[i][0] = shapes[shape][i][0];
        coordinates[i][1] = shapes[shape][i][1];
    }
    pieceShape = shape;
}
