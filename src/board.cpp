#include <vector>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <unordered_map>


#include "../include/board.hpp"

std::hash<std::vector<short int>> hasher;

Board::Board(int w, int h, std::vector<piece_t> pieces, std::vector<coordinates_t> pCoords)
{
    int     nbPieces = pieces.size();

    width = w;
    height = h;

    matrix = (int**)malloc(h * sizeof(int*));
    for (int y = 0; y < h; ++y)
    {
        matrix[y] = (int*)malloc(w * sizeof(int));
    }

    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            matrix[y][x] = -1;
        }
    }

    for (int i = 0; i < nbPieces; i++)
    {
        coordinates_t coords = pCoords.at(i);
        piecesCoordinates.push_back(coords);
        // Placing ith-piece
        for (int y = 0; y < pieces.at(i).height; y++)
        {
            for (int x = 0; x < pieces.at(i).width; x++)
            {
                matrix[y + coords.y][x + coords.x] = i;
            }
        }
    }
    for (int y = 0; y < h; y++)
    {
        for (int x = 0; x < w; x++)
        {
            if (matrix[y][x] == (-1))
            {
                null.push_back((coordinates_t){x,y});
            }
        }
    }
}

Board::~Board()
{
}

int         abs(int a) { return (a > 0 ? a : (-a));}

bool        Board::isLegalMove(move_t move, std::vector<piece_t> pieces)
{
    int             id = move.id;
    coordinates_t   deltaCoords = move.coords;
    // Verification de la legalite (deplacement unitaire et dans la matrice)
    coordinates_t   pCoords = piecesCoordinates.at(id);
    int             pWidth = pieces.at(id).width;
    int             pHeight = pieces.at(id).height;
    if ((abs(deltaCoords.x) + abs(deltaCoords.y) != 1) || (pCoords.x + deltaCoords.x < 0 || pCoords.x + deltaCoords.x +  pWidth > width || pCoords.y + deltaCoords.y < 0 || pCoords.y + deltaCoords.y + pHeight > height))
    {
        return (false);
    }

    // Verification disponibilite
    bool        isAvailable = true;
    for (int y = 0; y < pHeight; y++)
    {
        for (int x = 0; x < pWidth; x++)
        {
            if (matrix[y + pCoords.y + deltaCoords.y][x + pCoords.x + deltaCoords.x] != (-1) && matrix[y + pCoords.y + deltaCoords.y][x + pCoords.x + deltaCoords.x] != id)
            {
                isAvailable = false;
            }
        }
    }
    return(isAvailable);
}

void        Board::move(move_t move, std::vector<piece_t> pieces)
{
    int             id = move.id;
    coordinates_t   deltaCoords = move.coords;
    coordinates_t   pCoords = piecesCoordinates.at(id);
    int             pWidth = pieces.at(id).width;
    int             pHeight = pieces.at(id).height;
    if (deltaCoords.x != 0)
    {
        for (int y = 0; y < pHeight; y++)
        {
            matrix[y + pCoords.y][deltaCoords.x > 0 ? (pCoords.x) : (deltaCoords.x + pCoords.x + pWidth)] = -1;
            matrix[y + pCoords.y][deltaCoords.x < 0 ? (pCoords.x - 1) : (deltaCoords.x + pCoords.x + pWidth - 1)] = id;
            for (int i = 0; i < null.size(); i ++)
                if (null.at(i).x == (deltaCoords.x < 0 ? (pCoords.x) : (deltaCoords.x + pCoords.x + pWidth)) && null.at(i).y == y + pCoords.y)
                    null.at(i).x = deltaCoords.x > 0 ? (pCoords.x) : (deltaCoords.x + pCoords.x + pWidth);
        }
    }
    else
    {
        for (int x = 0; x < pWidth; x++)
        {
            matrix[deltaCoords.y > 0 ? (pCoords.y) : (deltaCoords.y + pCoords.y + pHeight)][x + pCoords.x] = -1;
            matrix[deltaCoords.y < 0 ? (pCoords.y - 1) : (deltaCoords.y + pCoords.y + pHeight - 1)][x + pCoords.x] = id;
            for (int i = 0; i < null.size(); i ++)
                if (null.at(i).x == x + pCoords.x && null.at(i).y == deltaCoords.y < 0 ? (pCoords.y) : (deltaCoords.y + pCoords.y + pHeight))
                    null.at(i).y = deltaCoords.y > 0 ? (pCoords.y) : (deltaCoords.y + pCoords.y + pHeight);
        }
    }
    piecesCoordinates.at(id).x += deltaCoords.x;
    piecesCoordinates.at(id).y += deltaCoords.y;
}

void    Board::show()
{
    for (int y = 0; y < height; y++)
    {
        std::cout << "[ ";
        for (int x = 0; x < width-1; x++)
        {
            std::cout << matrix[y][x] << ", ";
        }
        std::cout << matrix[y][width-1] << " ]" << std::endl;
    }
    std::cout << std::endl;
}

bool    Board::hasArrived(std::vector<rule_t> rules)
{
    bool    result = true;
    int     len = rules.size();
    for (int i = 0; i < len; i++)
    {
        coordinates_t   c = piecesCoordinates.at(rules.at(i).id);
        coordinates_t   r = rules.at(i).coords;
        if (c.x != r.x || c.y != r.y)
            result = false;
    }
    return result;
}
int     Board::hash()
{
    std::vector<short int> temp;
    int nbPieces = piecesCoordinates.size();
    for (int i =0; i < nbPieces; i++)
    {
        temp.push_back(piecesCoordinates.at(i).x);
        temp.push_back(piecesCoordinates.at(i).y);
    }
    return (hasher(temp));
}

std::vector<move_t>     Board::possibleMoves(std::vector<piece_t> pieces)
{
    std::vector<move_t> moves;
    int                 nbZeros = null.size();
    for (int i = 0; i < nbZeros; i++)
    {
        int             x = null.at(i).x;
        int             y = null.at(i).y;
        if (x > 0)
        {
            int     id = matrix[y][x-1];
            move_t  move = (move_t){id, (coordinates_t){1, 0}};
            if (id != -1)
                if (isLegalMove(move, pieces))
                    moves.push_back(move);
        }
        if (x < width - 1)
        {
            int     id = matrix[y][x+1];
            move_t  move = (move_t){id, (coordinates_t){-1, 0}};
            if (id != -1)
                if (isLegalMove(move, pieces))
                    moves.push_back(move);
        }
        if (y > 0)
        {
            int     id = matrix[y-1][x];
            move_t  move = (move_t){id, (coordinates_t){0, 1}};
            if (id != -1)
                if (isLegalMove(move, pieces))
                    moves.push_back(move);
        }
        if (y < height - 1)
        {
            int     id = matrix[y+1][x];
            move_t  move = (move_t){id, (coordinates_t){0, -1}};
            if (id != -1)
                if (isLegalMove(move, pieces))
                    moves.push_back(move);
        }
    }
    return (moves);
}

Board       Board::boardAfterMove(std::vector<piece_t> pieces, move_t move)
{
    std::vector<coordinates_t>  newCoordinates;
    int                         nbPieces = piecesCoordinates.size();
    for (int i = 0; i < nbPieces; i++)
        newCoordinates.push_back(piecesCoordinates.at(i));
    Board newBoard = Board(width, height, pieces, newCoordinates);
    newBoard.move(move, pieces);
    return(newBoard);
}