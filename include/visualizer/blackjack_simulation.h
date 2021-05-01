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
    size_t current_bet_;

    const size_t kPlayerBalance = 1000;
    const size_t kWindowWidth = 1440;
    const size_t kWindowHeight = 800;
    const size_t kCardHeight = 250;
    const size_t kCardWidth = 180;
    const size_t kCardCornerRadius = 10;
    const size_t kCardCornerSegments = 10;
    const size_t kButtonWidth = 100;
    const size_t kButtonHeight = 50;
    const size_t kBackOfCardMargin = 10;
    const size_t kCardMargin = 200;
    const size_t kLargeBetButtonRadius = 30;
    const size_t kSmallBetButtonRadius = 20;
    const vec2 kPlayerCardPos = vec2(130,500);
    const vec2 kDealerCardPos = vec2(130,100);
    const vec2 kHitButtonPos = vec2(300, 400);
    const vec2 kStandButtonPos = vec2(450, 400);
    const vec2 kDealButtonPos = vec2(600, 400);
    const vec2 kDealerValuePos = vec2(70, 180);
    const vec2 kPlayerValuePos = vec2(70, 600);
    const vec2 kEndRoundMessagePos = vec2(300, 410);
    const vec2 kTitlePos = vec2(720, 50);
    const vec2 kBalancePos = vec2(1400, 50);
    const vec2 kDecreaseButtonPos = vec2(830, 425);
    const vec2 kDecreaseButtonLabelPos = vec2(830, 375);
    const vec2 kSmallDecreaseButtonPos = vec2(900, 425);
    const vec2 kSmallDecreaseButtonLabelPos = vec2(900, 400);
    const vec2 kBetPos = vec2(980, 410);
    const vec2 kSmallIncreaseButtonPos = vec2(1060, 425);
    const vec2 kSmallIncreaseButtonLabelPos = vec2(1060, 408);
    const vec2 kIncreaseButtonPos = vec2(1130, 425);
    const vec2 kIncreaseButtonLabelPos = vec2(1130, 392);
    const vec2 kBetStringPos = vec2(970, 370);
    const string kClubString = "c";
    const string kSpadeString = "s";
    const string kHitString = "Hit";
    const string kStandString = "Stand";
    const string kDealString = "Deal";
    const string kTitleString = "Blackjack";
    const string kBalanceString = "Balance: ";
    const string kBetString = "Choose amount to bet:";
    const string kIncreaseBetString = "+";
    const string kDecreaseBetString = "-";
    const ci::Font kCardFont = ci::Font("arial", 200);
    const ci::Font kButtonFont = ci::Font("georgia", 20);
    const ci::Font kValueFont = ci::Font("georgia", 50);
    const ci::Font kEndRoundMessageFont = ci::Font("Garamond", 40);
    const ci::Font kTitleFont = ci::Font("brush script mt", 200);
    const ci::Font kBalanceFont = ci::Font("georgia", 30);
    const ci::Font kBetFont = ci::Font("georgia", 30);
    const ci::Font kBetStringFont = ci::Font("georgia", 30);
    const ci::Font kIncreaseBetFont = ci::Font("arial", 100);
    const ci::Font kSmallIncreaseBetFont = ci::Font("arial", 50);
    const ci::Font kDecreaseBetFont = ci::Font("arial", 120);
    const ci::Font kSmallDecreaseBetFont = ci::Font("arial", 60);
    const ci::Color kBackgroundColor = ci::Color("forestgreen");
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
    const ci::Color kDecreaseBetButtonColor = ci::Color("maroon");
    const ci::Color kIncreaseBetButtonColor = ci::Color("green");
    const ci::Color kBetColor = ci::Color("black");
    const ci::Color kBetStringColor = ci::Color("black");
    const ci::Color kBetButtonLabelColor = ci::Color("black");
    const float kLargeBetChangeFactor = 0.1;
    const float kSmallBetChangeFactor = 0.01;
    const float kDefaultBetFactor = 0.1;

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
    
    /**
     * Draws a button with an outline and label
     * @param pos position of button
     * @param label button label
     */
    void DrawButton(const vec2& pos, const string& label);
    
    /**
     * Draws the value of the sum of the given cards
     * @param pos position of value
     * @param cards cards to count value of
     */
    void DrawValue(const vec2& pos, const vector<Card>& cards);
    
    /**
     * Draws the round-end message
     */
    void DrawRoundEndMessage();
    
    /**
     * Draws player balance
     */
    void DrawBalance();
    
    /**
     * Draws the 4 buttons to change bet amount, displays the current bet amount, and displays a default string
     */
    void DrawBetUI();
    
    /**
     * Checks if any of the bet buttons were pressed and updates the current bet accordingly
     * @param pos 
     */
    void CheckBetButtonPressed(const vec2& pos);
};

}
}
