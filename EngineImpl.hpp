#ifndef CHESS_ENGINE_ENGINEIMP_HPP
#define CHESS_ENGINE_ENGINEIMP_HPP

#include "Engine.hpp"
#include <string>

class EngineImpl : public Engine{
    public:
        EngineImpl();
        ~EngineImpl() = default;
        std::string name() const;
        std::string version() const;
        std::string author() const;

        void newGame();
        PrincipalVariation pv(
            const Board& board,
            const TimeInfo::Optional& timeInfo = std::nullopt
        );
        bool isTerminal(Board board);
        virtual int AlphaBeta(Board board, int depth, int alpha, int beta, LINE * pline);

        std::optional<HashInfo> hashInfo() const;
        void setHashSize(std::size_t size);
};

#endif
