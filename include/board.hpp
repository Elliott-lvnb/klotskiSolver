#pragma once

#include <vector>
#include <string>


typedef struct {
    int     x;
    int     y;
} coordinates_t;

typedef struct {
    int             id;
    coordinates_t   coords;
} rule_t;

typedef rule_t move_t;

typedef struct {
    int             id;
    int             width;
    int             height;
} piece_t;

class Board {
    public:
        Board(int w, int h, std::vector<piece_t> pieces, std::vector<coordinates_t> pCoords);
        ~Board();

        void                            move(move_t move, std::vector<piece_t> pieces); // O(width * height)
        bool                            hasArrived(std::vector<rule_t> rules); // Temps constant
        bool                            isLegalMove(move_t move, std::vector<piece_t> pieces);

        void                            show();

        int                             hash();
        Board                           boardAfterMove(std::vector<piece_t> pieces, move_t move);
        
        std::vector<move_t>             possibleMoves(std::vector<piece_t> pieces);
        std::vector<coordinates_t>      null;
        int**                           matrix;

        std::vector<coordinates_t>      piecesCoordinates;
        int                             width;
        int                             height;
};