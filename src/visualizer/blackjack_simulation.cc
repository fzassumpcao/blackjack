#include "visualizer/blackjack_simulation.h"

namespace blackjack {
namespace visualizer {

    BlackjackSimulation::BlackjackSimulation() : gameEngine_(true) {
        ci::app::setWindowSize(kWindowWidth, kWindowHeight);
        gameEngine_.StartDeal(std::default_random_engine(time(nullptr)));
    }
    
    void BlackjackSimulation::draw() {
        ci::Color background_color("green");
        ci::gl::clear(background_color);
        
        DrawCards(gameEngine_.GetPlayerCards(), vec2(200,500), 200);
        DrawCards(gameEngine_.GetDealerCards(), vec2(200,100), 200);
        
        //Draw deal button if game is finished, hit and stand buttons if not
        if (gameEngine_.IsGameFinished()) {
            DrawButton(kDealButtonPos, k)
            
        } else {
            DrawButton(kHitButtonPos, kHitString);
            DrawButton(kStandButtonPos, kStandString);
        }
    }

    void BlackjackSimulation::mouseDown(ci::app::MouseEvent event) {
        vec2 pos = event.getPos();
        
        if (gameEngine_.IsGameFinished()) {
            
        }
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

    void BlackjackSimulation::DrawCard(const Card& card, const vec2& pos) {
        
        
        //TODO Change outline to draw thicker rectangle and four circles at the corners
        //Draws black card outline and white background
        ci::gl::color(ci::Color("white"));
        ci::gl::drawSolidRoundedRect(cinder::Rectf(pos.x, pos.y, pos.x + kCardWidth, pos.y +kCardHeight), kCardCornerRadius, 
                                     kCardCornerSegments, pos,vec2(pos.x + kCardWidth, pos.y + kCardHeight));
        ci::gl::color(ci::Color("black"));
        ci::gl::drawStrokedRoundedRect(cinder::Rectf(pos.x, pos.y, pos.x + kCardWidth, pos.y +kCardHeight), 
                                       kCardCornerRadius,kCardCornerSegments);

        //Sets the color of the card symbols to black if the card is a club or spade and to red for hearts and diamonds
        ci::ColorAT<float> colorAT = 
                ci::Color(card.GetSuit() == kClubString || card.GetSuit() == kSpadeString ? "black" : "red");
        
        //Draws card name/symbol
        ci::gl::drawStringCentered(card.GetName(), vec2(pos.x + kCardWidth/2, pos.y + kCardHeight/5), 
                                   colorAT, kCardFont);
    }

    void BlackjackSimulation::DrawCards(const vector<Card> &cards, const vec2 &pos, int horizontal_margin) {
        for (size_t i = 0; i < cards.size(); i++) {
            DrawCard(cards[i], vec2(pos.x + horizontal_margin * i, pos.y));
        }
    }

    void BlackjackSimulation::DrawButton(const vec2 &pos, const string& label) {
        
        //Draw button background
        ci::gl::color(ci::Color("yellow"));
        cinder::Rectf rectf(pos.x, pos.y, pos.x + kButtonWidth, pos.y + kButtonHeight);
        ci::gl::drawSolidRect(rectf);
        ci::gl::color(ci::Color("black"));
        
        //Draw outline
        ci::gl::drawStrokedRect(rectf, 3);
        
        //Draw label
        ci::gl::drawStringCentered(label, vec2(pos.x + kButtonWidth/2, pos.y + kButtonHeight/3),
                                   ci::Color("black"), kButtonFont);
    }

}
}
