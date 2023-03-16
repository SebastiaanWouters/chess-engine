#include "PrincipalVariation.hpp"

#include <ostream>
#include <vector>
#include "Move.hpp"
#include "Board.hpp"

#include <iosfwd>
#include <cstddef>
#include <iostream>

using MoveIter = std::vector<Move>::const_iterator;

PrincipalVariation::PrincipalVariation(std::vector<Move> movesIter, Board board) {
    moves_ = movesIter;
    board_ = board;
}

bool PrincipalVariation::isMate() const {
    if (board_.kingChecked(board_.turn(), {})) {
        std::vector<Move> moves_;
        board_.pseudoLegalMoves(moves_);
        if (moves_.size() == 0) {
            return true;
        }
    }
    return false;
}

bool PrincipalVariation::isStaleMate() const {
    std::vector<Move> moves_;
    board_.pseudoLegalMoves(moves_);
    if (moves_.size() == 0) {
        return true;
    }
    return false;
}

int PrincipalVariation::score() const {
    if (isMate()) {
        return this->length();
    } else if (isStaleMate()) {
        return 0;
    }
    return board_.evaluate();
}

std::size_t PrincipalVariation::length() const {
    return moves_.size();
}

PrincipalVariation::MoveIter PrincipalVariation::begin() const {
    return moves_.begin();
}

PrincipalVariation::MoveIter PrincipalVariation::end() const {
    return moves_.end();
}

std::ostream& operator<<(std::ostream& os, const PrincipalVariation& pv) {
    for (MoveIter move = pv.begin(); move != pv.end(); ++move){
        os << "From: " << move->from() << " To: " << move->to() << "\n\n";
        os << pv.score() << std::endl;
    }
    return os;
}
