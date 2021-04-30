#include "visualizer/blackjack_simulation.h"

namespace blackjack {
namespace visualizer {

BlackjackSimulation::BlackjackSimulation() : gameEngine_(1000), in_starting_screen_(true) {
    ci::app::setWindowSize(kWindowWidth, kWindowHeight);
}

void BlackjackSimulation::draw() {
    
    if (gameEngine_.GetBalance() == 0) {
        gameEngine_.Reset(1000);
        in_starting_screen_ = true;
    }
    
    //TODO images for cards? Also option to choose balance? maybe change restart in game engine to take in a value
    
    ci::gl::clear(kBackgroundColor);
    
    DrawCards(gameEngine_.GetPlayerCards(), kPlayerCardPos, kCardMargin);
    DrawCards(gameEngine_.GetDealerCards(), kDealerCardPos, kCardMargin);
    DrawBalance();
    
    //Draw deal button, message, and dealer card count if game is finished, hit and stand buttons if not
    if (gameEngine_.IsGameFinished()) {
        
        DrawButton(kDealButtonPos, kDealString);
        if (in_starting_screen_) {
            ci::gl::drawStringCentered(kTitleString, kTitlePos, kTitleColor, kTitleFont);
            
        } else {
            DrawRoundEndMessage();
            DrawValue(kDealerValuePos, gameEngine_.GetDealerCards());
            DrawValue(kPlayerValuePos, gameEngine_.GetPlayerCards());
        }
        
    } else {
        DrawButton(kHitButtonPos, kHitString);
        DrawButton(kStandButtonPos, kStandString);
        DrawValue(kPlayerValuePos, gameEngine_.GetPlayerCards());
    }
}

void BlackjackSimulation::mouseDown(ci::app::MouseEvent event) {
    vec2 pos = event.getPos();
    
    if (gameEngine_.IsGameFinished()) {
        //Check if mouse is inside deal button only when game is finished
        if (pos.x >= kDealButtonPos.x && pos.x <= (kDealButtonPos.x + kButtonWidth)
            && pos.y >= kDealButtonPos.y && pos.y <= (kDealButtonPos.y + kButtonHeight)) {
            std::random_device rd;
            gameEngine_.StartDeal(std::default_random_engine(rd()), 100);
            
            //Starting screen disappears first time deal button is pressed
            in_starting_screen_ = false;
        }
        
    } else {
        
        //Check if mouse click is inside hit button rectangle
        if (pos.x >= kHitButtonPos.x && pos.x <= (kHitButtonPos.x + kButtonWidth)
            && pos.y >= kHitButtonPos.y && pos.y <= (kHitButtonPos.y + kButtonHeight)) {
            gameEngine_.Hit();

            //Check if mouse click is inside stand button rectangle
        } else if (pos.x >= kStandButtonPos.x && pos.x <= (kStandButtonPos.x + kButtonWidth)
                   && pos.y >= kStandButtonPos.y && pos.y <= (kStandButtonPos.y + kButtonHeight)) {
            gameEngine_.Stand();
        }
    }
}

void BlackjackSimulation::DrawCard(const Card& card, const vec2& pos) {
    
    //Draws black card outline and white background
    ci::gl::color(kCardBackgroundColor);
    ci::gl::drawSolidRoundedRect(cinder::Rectf(pos.x, pos.y, pos.x + kCardWidth, pos.y +kCardHeight), kCardCornerRadius, 
                                 kCardCornerSegments, pos,vec2(pos.x + kCardWidth, pos.y + kCardHeight));
    ci::gl::color(kCardOutlineColor);
    ci::gl::drawStrokedRoundedRect(cinder::Rectf(pos.x, pos.y, pos.x + kCardWidth, pos.y +kCardHeight), 
                                   kCardCornerRadius,kCardCornerSegments);

    if (card.IsFaceUp()) {
        //Sets the color of the card symbols to black if the card is a club or spade and to red for hearts and diamonds
        ci::ColorAT<float> colorAT;
        colorAT = card.GetSuit() == kClubString || card.GetSuit() == kSpadeString ? kBlackCardColor : kRedCardColor;

        //Draws card name/symbol
        ci::gl::drawStringCentered(card.GetName(), vec2(pos.x + kCardWidth / 2, pos.y + kCardHeight / 5),
                                   colorAT, kCardFont);
        
    } else {
        ci::gl::color(kBackCardColor);
        ci::gl::drawSolidRect(cinder::Rectf(pos.x + kBackOfCardMargin, pos.y + kBackOfCardMargin, 
                            pos.x + kCardWidth - kBackOfCardMargin, pos.y + kCardHeight - kBackOfCardMargin));
    }
}

void BlackjackSimulation::DrawCards(const vector<Card> &cards, const vec2 &pos, int horizontal_margin) {
    for (size_t i = 0; i < cards.size(); i++) {
        DrawCard(cards[i], vec2(pos.x + horizontal_margin * i, pos.y));
    }
}

void BlackjackSimulation::DrawButton(const vec2 &pos, const string& label) {
    
    //Draw button background
    ci::gl::color(kButtonColor);
    cinder::Rectf rectf(pos.x, pos.y, pos.x + kButtonWidth, pos.y + kButtonHeight);
    ci::gl::drawSolidRect(rectf);
    
    //Draw outline
    ci::gl::color(kButtonOutlineColor);
    ci::gl::drawStrokedRect(rectf, 3);
    
    //Draw label
    ci::gl::drawStringCentered(label, vec2(pos.x + kButtonWidth/2, pos.y + kButtonHeight/3),
                               kButtonLabelColor, kButtonFont);
}

void BlackjackSimulation::DrawValue(const vec2& pos, const vector<Card>& cards) {
    size_t value = gameEngine_.CalculateTotalValue(cards);
    ci::gl::drawStringCentered(std::to_string(value), pos, kValueColor, kValueFont);
}

void BlackjackSimulation::DrawRoundEndMessage() {
    ci::gl::drawStringCentered(gameEngine_.GetMessage(), kEndRoundMessagePos, kMessageColor, kEndRoundMessageFont);
}

void BlackjackSimulation::DrawBalance() {
    string balance_string = kBalanceString + std::to_string(gameEngine_.GetBalance());
    ci::gl::drawStringRight(balance_string, kBalancePos, kBalanceColor, kBalanceFont);
}

}
}
