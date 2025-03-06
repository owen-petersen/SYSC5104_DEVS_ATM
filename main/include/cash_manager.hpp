#ifndef CASH_MANAGER_HPP
#define CASH_MANAGER_HPP

#include <iostream>
#include <iomanip>
#include <limits>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;
using limits = std::numeric_limits<double>;

enum class CashManagerStateEn : int {
    passive = 0,
    dispensingCash = 1
};

struct cash_manager_state_st {
    CashManagerStateEn state;
    uint32_t cash_to_dispense;
    double sigma;

    explicit cash_manager_state_st():state(CashManagerStateEn::passive),\
                                    sigma(limits::infinity()),
                                    cash_to_dispense(0)
                                    {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const cash_manager_state_st& state) {
    out  << "Next State = " << (int)state.state;
    return out;
}
#endif

class cash_manager : public Atomic<cash_manager_state_st> {
    private:
        
    public:
    // Input ports
    Port<uint32_t> dispense_in;
    // Output ports
    Port<uint32_t> cash_out;

    cash_manager(const std::string id) : Atomic<cash_manager_state_st>(id, cash_manager_state_st())
    {
        dispense_in = addInPort<uint32_t>("dispense_in");
        cash_out = addOutPort<uint32_t>("cash_out");
    }

    void internalTransition(cash_manager_state_st& state) const override {
        switch(state.state) {
        case CashManagerStateEn::dispensingCash:
            state.state = CashManagerStateEn::passive;
            state.sigma = limits::infinity();
            break;
        default:
            break;
        }
    }

    // external transition
    void externalTransition(cash_manager_state_st& state, double e) const override {
        if (!dispense_in->empty()) {
            for (const auto &input : dispense_in->getBag()) {
                if (state.state == CashManagerStateEn::passive) {
                    state.state = CashManagerStateEn::dispensingCash;
                    state.cash_to_dispense = input;
                    state.sigma = 1.0;
                    return;
                }
            }
        }
        state.sigma -= e;
    }
    
    // output function
    void output(const cash_manager_state_st& state) const override {
        switch(state.state){
        case CashManagerStateEn::dispensingCash:
            cash_out->addMessage(state.cash_to_dispense);
            break;
        default:
            break;
        }
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const cash_manager_state_st& state) const override {
        return state.sigma;
    }
};

#endif