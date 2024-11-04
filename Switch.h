// Switch.h
#ifndef SWITCH_H
#define SWITCH_H

#include "ASi.h"
#include "PrecisionTimer.h"

/** \brief Debounced Digital Input
 *
 * This class represents an analog switch connected to a digital Input.
 * The active level of the switch is configurable, as it is the pin the
 * switch is connected to.
 * The debouncing technique is to sample the input looking for the active level
 * and, once it is found, starts a timer. When the latter times out, we decide if
 * the signal is stable on that level. The level should be active for at least 
 * DEBOUNCE_PERIOD micro seconds to be considered a valid transition.
 *
 * \param
 * \param
 * \return
 *
 */


class Switch
{
public:

    Switch(int m_pin, bool level, ASi* asi);

    bool isOn();

private:
    int m_pin;
    bool m_active_level;
    PrecisionTimer m_debounceTimer;
    Platform* m_platform;
};

#endif //SWITCH_H
