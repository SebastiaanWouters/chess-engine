#ifndef CHESS_ENGINE_PRINCIPALVARIATION_HPP
#define CHESS_ENGINE_PRINCIPALVARIATION_HPP

#include "Move.hpp"
#include "Piece.hpp"
#include "Board.hpp"

#include <iosfwd>
#include <cstddef>
#include <list>
#include <vector>

class PrincipalVariation {
public:

    using MoveIter = std::vector<Move>::const_iterator;

    PrincipalVariation(std::vector<Move> movesIter, Board board);

    bool isMate() const;
    bool isStaleMate() const;
    int score() const;

    std::size_t length() const;
    MoveIter begin() const;
    MoveIter end() const;

private:
    std::vector<Move> moves_;
    Board board_;
};

std::ostream& operator<<(std::ostream& os, const PrincipalVariation& pv);

#endif
