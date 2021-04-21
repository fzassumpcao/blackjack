#include "../include/visualizer/blackjack_simulation.h"

using namespace blackjack;
using namespace visualizer;

void prepareSettings(BlackjackSimulation::Settings* settings) {
    settings->setResizable(false);
}

CINDER_APP(BlackjackSimulation, ci::app::RendererGl, prepareSettings);
