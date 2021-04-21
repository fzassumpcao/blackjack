#include "visualizer/blackjack_simulation.h"

namespace blackjack {
namespace visualizer {

BlackjackSimulation::BlackjackSimulation() : gameEngine_() {
    ci::app::setWindowSize(kWindowSize, kWindowSize);
}

void BlackjackSimulation::draw() {
    ci::Color background_color("green");
    ci::gl::clear(background_color);
}

void BlackjackSimulation::update() {
    AppBase::update();
}

}
}
