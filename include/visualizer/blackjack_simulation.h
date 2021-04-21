#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/game_engine.h"

namespace blackjack {
    
namespace visualizer {

class BlackjackSimulation : public ci::app::App {
public:
    BlackjackSimulation();
    
    void draw() override;
    void update() override;
    
    const int kWindowSize = 875;
    const int kMargin = 100;
    
private:
    GameEngine gameEngine_;
};

}
}
