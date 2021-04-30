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
    
private:
    GameEngine gameEngine_;
    bool in_starting_screen_;

    const int kWindowWidth = 1440;
    const int kWindowHeight = 800;
    const size_t kCardHeight = 250;
    const size_t kCardWidth = 180;
    const size_t kCardCornerRadius = 10;
    const size_t kCardCornerSegments = 10;
    const size_t kButtonWidth = 100;
    const size_t kButtonHeight = 50;
    const size_t kBackOfCardMargin = 10;
    const size_t kCardMargin = 200;
    const vec2 kPlayerCardPos = vec2(200,500);
    const vec2 kDealerCardPos = vec2(200,100);
    const vec2 kHitButtonPos = vec2(300, 400);
    const vec2 kStandButtonPos = vec2(450, 400);
    const vec2 kDealButtonPos = vec2(600, 400);
    const vec2 kDealerValuePos = vec2(70, 150);
    const vec2 kPlayerValuePos = vec2(70, 600);
    const vec2 kEndRoundMessagePos = vec2(300, 410);
    const vec2 kTitlePos = vec2(720, 50);
    const vec2 kBalancePos = vec2(1400, 50);

    const string kClubString = "c";
    const string kSpadeString = "s";
    const string kHitString = "Hit";
    const string kStandString = "Stand";
    const string kDealString = "Deal";
    const string kTitleString = "Blackjack";
    const string kBalanceString = "Balance: ";
    const ci::Font kCardFont = ci::Font("arial", 200);
    const ci::Font kButtonFont = ci::Font("arial", 20);
    const ci::Font kValueFont = ci::Font("arial", 50);
    const ci::Font kEndRoundMessageFont = ci::Font("arial", 50);
    const ci::Font kTitleFont = ci::Font("arial", 200);
    const ci::Font kBalanceFont = ci::Font("arial", 30);
    const ci::Color kBackgroundColor = ci::Color("green");
    const ci::Color kTitleColor = ci::Color("black");
    const ci::Color kCardBackgroundColor = ci::Color("white");
    const ci::Color kCardOutlineColor = ci::Color("black");
    const ci::Color kRedCardColor = ci::Color("red");
    const ci::Color kBlackCardColor = ci::Color("black");
    const ci::Color kBackCardColor = ci::Color("blue");
    const ci::Color kButtonColor = ci::Color("yellow");
    const ci::Color kButtonLabelColor = ci::Color("black");
    const ci::Color kButtonOutlineColor = ci::Color("black");
    const ci::Color kValueColor = ci::Color("black");
    const ci::Color kMessageColor = ci::Color("black");
    const ci::Color kBalanceColor = ci::Color("black");





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
    
    void DrawValue(const vec2& pos, const vector<Card>& cards);
    
    void DrawRoundEndMessage();
    
    void DrawBalance();
};

}
}
