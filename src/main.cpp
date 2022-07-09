#include "../include/board.hpp"
#include "../include/solver.hpp"
#include <iostream>
#include <vector>

using namespace std;

void    printPossibleMoves(Board b, vector<piece_t> p);

int main()
{
    vector<piece_t>             pieces;
    vector<coordinates_t>       coordinates;
    vector<rule_t>              rules;

    rules.push_back((rule_t){1, (coordinates_t){1,3}});

    pieces.push_back((piece_t){0, 1, 2});
    coordinates.push_back((coordinates_t){0,0});
    pieces.push_back((piece_t){1, 2, 2});
    coordinates.push_back((coordinates_t){1,0});
    pieces.push_back((piece_t){2, 1, 2});
    coordinates.push_back((coordinates_t){3,0});
    pieces.push_back((piece_t){3, 1, 2});
    coordinates.push_back((coordinates_t){0,2});
    pieces.push_back((piece_t){4, 2, 1});
    coordinates.push_back((coordinates_t){1,2});
    pieces.push_back((piece_t){5, 1, 2});
    coordinates.push_back((coordinates_t){3,2});
    pieces.push_back((piece_t){6, 1, 1});
    coordinates.push_back((coordinates_t){1,3});
    pieces.push_back((piece_t){7, 1, 1});
    coordinates.push_back((coordinates_t){2,3});
    pieces.push_back((piece_t){8, 1, 1});
    coordinates.push_back((coordinates_t){0,4});
    pieces.push_back((piece_t){9, 1, 1});
    coordinates.push_back((coordinates_t){3,4});
    Board board = Board(4, 5, pieces, coordinates);
    board.show();

    solver_result_t res = bfs(board, pieces, rules);
    
    return(0);
}