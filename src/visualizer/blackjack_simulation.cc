#include "visualizer/blackjack_simulation.h"

using glm::vec2;

namespace blackjack {
namespace visualizer {

    BlackjackSimulation::BlackjackSimulation() : gameEngine_(true) {
        ci::app::setWindowSize(kWindowWidth, kWindowHeight);
    }
    
    void BlackjackSimulation::draw() {
        ci::Color background_color("green");
        ci::gl::clear(background_color);
        DrawCard(Card("as", true), vec2(500, 500));
    }
    
    void BlackjackSimulation::update() {
        AppBase::update();
    }

    void BlackjackSimulation::DrawCard(const Card& card, const vec2& pos) {
        ci::gl::color(ci::Color("white"));
        ci::gl::drawSolidRoundedRect(cinder::Rectf(pos.x, pos.y, pos.x + kCardWidth, pos.y +kCardHeight), kCardCornerRadius, 
                                     10, pos,vec2(pos.x + kCardWidth, pos.y + kCardHeight));

        ci::gl::color(ci::Color(card.GetSuit() == "c" || card.GetSuit() == "s" ? "black" : "red"));
        
        //TODO
        ci::gl::drawStringCentered(card.GetName(), vec2(pos.x + kCardWidth/2, pos.y + kCardHeight/2), cinder::ColorA(),
                                   cinder::Font("arial", 20));
        
    }

}
}
