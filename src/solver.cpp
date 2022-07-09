#include <queue>
#include <iostream>
#include <unordered_set>

#include "../include/solver.hpp"

solver_result_t         bfs(Board board, std::vector<piece_t> pieces, std::vector<rule_t> rules)
{
    std::queue<solver_result_t>     q;
    std::vector<move_t>             empty;
    q.push((solver_result_t){empty, board});
    std::unordered_set<int>         hashSet;
    std::vector<move_t>             moves;
    Board                           b2 = board;
    int n = 0;
    while (!q.empty())
    {
        solver_result_t             element = q.front();
        q.pop();
        b2 = element.board;
        moves = element.moves;
        if (b2.hasArrived(rules))
        {
            b2.show();
            return (element);
        }
        int h = b2.hash();
        if (hashSet.find(h) == hashSet.end())
        {
            n++;
            hashSet.insert(h);
            std::vector<move_t>     pMoves = b2.possibleMoves(pieces);
            int                     nbMoves = pMoves.size();
            for (int i = 0; i < nbMoves; i++)
            {
                std::vector<move_t> newMoves = {pMoves.at(i)};
                newMoves.insert(newMoves.end(), moves.begin(), moves.end());
                Board newBoard = b2.boardAfterMove(pieces, pMoves.at(i));
                q.push((solver_result_t){newMoves, newBoard});
            }
        }
    }
    std::cout << n << std::endl;
    return ((solver_result_t){moves,b2});
}