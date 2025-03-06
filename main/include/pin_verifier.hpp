#ifndef PIN_VERIFIER_HPP
#define PIN_VERIFIER_HPP

#include <iostream>
#include <iomanip>
#include <limits>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;
using limits = std::numeric_limits<double>;

enum class PinVerifierStateEn : int {
    passive = 0,
    numberReceived = 1,
    validatingPin = 2
};

struct pin_verifier_state_st {
    PinVerifierStateEn state;
    uint16_t entered_pin;
    double sigma;

    explicit pin_verifier_state_st():state(PinVerifierStateEn::passive),\
                                    sigma(limits::infinity()),
                                    entered_pin(0)
                                    {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const pin_verifier_state_st& state) {
    out  << "Next State = " << (int)state.state;
    return out;
}
#endif

class pin_verifier : public Atomic<pin_verifier_state_st> {
    private:
    static const uint16_t EXPECTED_PIN = 1234;
        
    public:
    // Input ports
    Port<uint16_t> card_number_in;
    Port<uint16_t> pin_in;
    // Output ports
    Port<bool> pin_valid_out;

    pin_verifier(const std::string id) : Atomic<pin_verifier_state_st>(id, pin_verifier_state_st())
    {
        card_number_in = addInPort<uint16_t>("card_number_in");
        pin_in = addInPort<uint16_t>("pin_in");
        pin_valid_out = addOutPort<bool>("pin_valid_out");
    }

    void internalTransition(pin_verifier_state_st& state) const override {
        switch(state.state) {
        case PinVerifierStateEn::validatingPin:
            if (state.entered_pin == EXPECTED_PIN) {
                state.state = PinVerifierStateEn::passive;
                state.sigma = limits::infinity();
            } else {
                state.state = PinVerifierStateEn::numberReceived;
                state.sigma = limits::infinity();
            }
            break;
        default:
            break;
        }
    }

    // external transition
    void externalTransition(pin_verifier_state_st& state, double e) const override {
        if (!card_number_in->empty()) {
            for (const auto &input : card_number_in->getBag()) {
                if (state.state == PinVerifierStateEn::passive) {
                    state.state = PinVerifierStateEn::numberReceived;
                    state.sigma = limits::infinity();
                    return;
                }
            }
        }
        if (!pin_in->empty()) {
            for (const auto &input : pin_in->getBag()) {
                if (state.state == PinVerifierStateEn::numberReceived) {
                    state.entered_pin = input;
                    state.state = PinVerifierStateEn::validatingPin;
                    state.sigma = 0.5;
                    return;
                }
            }
        }
        state.sigma -= e;
    }
    
    // output function
    void output(const pin_verifier_state_st& state) const override {
        switch(state.state){
        case PinVerifierStateEn::validatingPin:
            if (state.entered_pin == EXPECTED_PIN) {
                pin_valid_out->addMessage(true);
            } else {
                pin_valid_out->addMessage(false);
            }
            break;
        default:
            break;
        }
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const pin_verifier_state_st& state) const override {
        return state.sigma;
    }
};

#endif