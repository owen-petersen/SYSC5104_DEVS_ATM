#ifndef ACCOUNT_BALANCE_HPP
#define ACCOUNT_BALANCE_HPP

#include <iostream>
#include <iomanip>
#include <limits>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;
using limits = std::numeric_limits<double>;

enum class AccountBalanceStateEn : int {
    passive = 0,
    processing = 1
};

struct account_balance_state_st {
    AccountBalanceStateEn state;
    uint32_t request_amount;
    uint32_t account_balance;
    double sigma;

    explicit account_balance_state_st():state(AccountBalanceStateEn::passive),
                                    request_amount(0),
                                    account_balance(1500),
                                    sigma(limits::infinity())
                                    {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const account_balance_state_st& state) {
    out  << "Next State = " << (int)state.state;
    return out;
}
#endif

class account_balance : public Atomic<account_balance_state_st> {
    private:
        
    public:
    // Input ports
    Port<uint32_t> request_in;
    // Output ports
    Port<bool> approved_out;

    account_balance(const std::string id) : Atomic<account_balance_state_st>(id, account_balance_state_st())
    {
        request_in = addInPort<uint32_t>("request_in");
        approved_out = addOutPort<bool>("approved_out");
    }

    void internalTransition(account_balance_state_st& state) const override {
        switch(state.state) {
        case AccountBalanceStateEn::processing:
            if (state.account_balance >= state.request_amount) {
                state.account_balance -= state.request_amount;
            }
            state.state = AccountBalanceStateEn::passive;
            state.sigma = limits::infinity();
            break;
        default:
            break;
        }
    }

    // external transition
    void externalTransition(account_balance_state_st& state, double e) const override {
        if (!request_in->empty()) {
            for (const auto &input : request_in->getBag()) {
                if (state.state == AccountBalanceStateEn::passive) {
                    state.state = AccountBalanceStateEn::processing;
                    state.request_amount = input;
                    state.sigma = 0.1;
                    return;
                }
            }
        }
        state.sigma -= e;
    }
    
    // output function
    void output(const account_balance_state_st& state) const override {
        switch(state.state){
        case AccountBalanceStateEn::processing:
            approved_out->addMessage(state.account_balance >= state.request_amount);
            break;
        default:
            break;
        }
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const account_balance_state_st& state) const override {
        return state.sigma;
    }
};

#endif