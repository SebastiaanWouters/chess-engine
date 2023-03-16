#include "EngineFactory.hpp"
#include "EngineImpl.hpp"

std::unique_ptr<EngineImpl> EngineFactory::createEngine() {
    std::unique_ptr<EngineImpl> enginePtr;
    enginePtr = std::unique_ptr<EngineImpl>(new EngineImpl);
    return enginePtr;
}
