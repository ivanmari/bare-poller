#ifndef BLINKER_H
#define BLINKER_H

#include "PrecisionTimer.h"
#include "Switch.h"

/** \brief Blinker
 *
 * Utility class that allows an Output to toggle from On to Off periodically
 *
 */


class Blinker
{
public:
    Blinker(Platform* plat, int output_pin, long int time_on, long int time_off, bool active_level);

    void execute();
    void reset();

private:

    Platform* m_plat;
    PrecisionTimer m_blinkOffTimer;
    PrecisionTimer m_blinkOnTimer;
    const int m_output_pin;
    const bool m_active_level;
};
#endif //BLINKER_H
