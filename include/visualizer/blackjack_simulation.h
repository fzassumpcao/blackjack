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
    
    //TODO figure out how to organize what draws stuff (maybe have another class)
    
    const int kWindowWidth = 1440;
    const int kWindowHeight = 800;
    const size_t kCardHeight = 250;
    const size_t kCardWidth = 180;
    const size_t kCardCornerRadius = 10;
    
private:
    GameEngine gameEngine_;
    void DrawCard(const Card& card, const glm::vec2& pos);
};

}
}
