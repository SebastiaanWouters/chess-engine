#include "EngineImpl.hpp"
#include "Move.hpp"
#include "Square.hpp"
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstring>

EngineImpl::EngineImpl() {}

std::string EngineImpl::name() const {
    return "chessinator96";
}

::std::string EngineImpl::author() const {
    return "Sebastiaan Wouters";
}

std::string EngineImpl::version() const {
    return "1";
}

PrincipalVariation EngineImpl::pv(
        const Board& board,
        const TimeInfo::Optional& timeInfo
) {
    (void)timeInfo;
    LINE pline;
    /*change to while!!!!!!*/
    AlphaBeta(board, MAX_DEPTH, NEGATIVE_INFINITY, POSITIVE_INFINITY, &pline);

    Board tempBoard = board;
    std::vector<Move> moves;
    /*copy line into pv*/
    for (std::optional<Move> move : pline.argmove) {
        if (move.has_value()){
            moves.push_back(move.value());
            tempBoard.makeMove(move.value());
        }
    }
    return PrincipalVariation(moves, tempBoard);
}

bool EngineImpl::isTerminal(Board board) {
    std::vector<Move> moves_;
    board.pseudoLegalMoves(moves_);
    if (moves_.size() == 0) {
        return true;
    }
    return false;
}

struct more_than_key
{
    inline bool operator() (const Move& move1, const Move& move2)
    {
        return (move1.score() > move2.score());
    }
};


int EngineImpl::AlphaBeta(Board board, int depth, int alpha, int beta, LINE * pline) {
    
    LINE line;

    if (depth == 0 || isTerminal(board)) {
        pline->cmove = 0;
        return board.evaluate();
    }

    std::vector<Move> moves;
    board.pseudoLegalMoves(moves);
    std::sort(moves.begin(), moves.end(), more_than_key());

    for (Move move : moves) {
        Board tempBoard = board;
        tempBoard.makeMove(move);

        int val = -AlphaBeta(tempBoard, depth - 1, -beta, -alpha, &line);

        if (val >= beta) {
            return beta;
        }
        if (val > alpha) {
            alpha = val;
            pline->argmove[0] = move;
            std::memcpy(pline->argmove + 1, line.argmove, line.cmove * sizeof(Move));
            pline->cmove = line.cmove + 1;            
        }   
    }
    return alpha;
}

void EngineImpl::newGame() {
    
}

std::optional<HashInfo> EngineImpl::hashInfo() const {
    return {};
};
void EngineImpl::setHashSize(std::size_t size) {
    (void) size;
};
