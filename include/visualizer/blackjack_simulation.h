#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "core/game_engine.h"

using glm::vec2;
using std::string;
using std::vector;

namespace blackjack {
    
namespace visualizer {

class BlackjackSimulation : public ci::app::App {
public:
    BlackjackSimulation();
    
    void draw() override;
    void mouseDown(ci::app::MouseEvent event) override;
    
    const int kWindowWidth = 1440;
    const int kWindowHeight = 800;
    const size_t kCardHeight = 250;
    const size_t kCardWidth = 180;
    const size_t kCardCornerRadius = 10;
    const size_t kCardCornerSegments = 10;
    const size_t kButtonWidth = 100;
    const size_t kButtonHeight = 50;
    const vec2 kHitButtonPos = vec2(300, 400);
    const vec2 kStandButtonPos = vec2(450, 400);
    const vec2 kDealButtonPos = vec2(400, 400);
    const size_t kBackOfCardMargin = 10;
    
    const string kClubString = "c";
    const string kSpadeString = "s";
    const string kHitString = "Hit";
    const string kStandString = "Stand";
    const string kDealString = "Deal";
    const ci::Font kCardFont = ci::Font("arial", 200);
    const ci::Font kButtonFont = ci::Font("arial", 20);
    
private:
    GameEngine gameEngine_;
    
    /**
     * Draws a card outline and card info, with color corresponding to suit of card.
     * @param card card to draw
     * @param pos position of where to draw the card
     */
    void DrawCard(const Card& card, const vec2& pos);
    
    /**
     * Draws multiple cards next to each other.
     * @param cards list of cards to draw
     * @param pos position of where to draw the first card
     * @param horizontal_margin margin between each card
     */
    void DrawCards(const vector<Card>& cards, const vec2& pos, int horizontal_margin);
    
    
    void DrawButton(const vec2& pos, const string& label);
};

}
}
