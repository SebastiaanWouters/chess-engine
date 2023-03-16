#ifndef CHESS_ENGINE_ENGINEFACTORY_HPP
#define CHESS_ENGINE_ENGINEFACTORY_HPP

#include "EngineImpl.hpp"

#include <memory>

class EngineFactory {
public:

    static std::unique_ptr<EngineImpl> createEngine();
};

#endif
