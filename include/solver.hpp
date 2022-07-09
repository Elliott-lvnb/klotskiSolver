#pragma once

#include <vector>
#include "../include/board.hpp"

typedef struct {
    std::vector<move_t> moves;
    Board               board;
} solver_result_t;


solver_result_t         bfs(Board board, std::vector<piece_t> pieces, std::vector<rule_t> rules);