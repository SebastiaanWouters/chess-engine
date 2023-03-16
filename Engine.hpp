#ifndef CHESS_ENGINE_ENGINE_HPP
#define CHESS_ENGINE_ENGINE_HPP

#include "PrincipalVariation.hpp"
#include "Board.hpp"
#include "Move.hpp"
#include "TimeInfo.hpp"

#include <string>
#include <optional>
#include <cstddef>


const int MAX_DEPTH = 3; 
const int NEGATIVE_INFINITY = -100000000;
const int POSITIVE_INFINITY = 100000000;

typedef struct LINE {
    int cmove;              // Number of moves in the line.
    std::optional<Move> argmove[MAX_DEPTH];  // The line.
}   LINE;


struct HashInfo {
    std::size_t defaultSize;
    std::size_t minSize;
    std::size_t maxSize;
};

class Engine {
public:
    virtual ~Engine() = default;
    virtual std::string name() const = 0;
    virtual std::string version() const = 0;
    virtual std::string author() const = 0;

    virtual void newGame() = 0;
    virtual PrincipalVariation pv(
        const Board& board,
        const TimeInfo::Optional& timeInfo = std::nullopt
    ) = 0;
    virtual bool isTerminal(Board board) = 0;
    virtual int AlphaBeta(Board board, int depth, int alpha, int beta, LINE* pline) = 0;

    virtual std::optional<HashInfo> hashInfo() const = 0;
    virtual void setHashSize(std::size_t size) = 0;
};

#endif
