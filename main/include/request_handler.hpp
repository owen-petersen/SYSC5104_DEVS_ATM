#ifndef REQUEST_HANDLER_HPP
#define REQUEST_HANDLER_HPP

#include <iostream>
#include <iomanip>
#include <limits>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;
using limits = std::numeric_limits<double>;

enum class RequestHandlerStateEn : int {
    passive = 0,
    cardAccepted = 1,
    requestReceived = 2,
    pendingApproval = 3,
    requestApproved = 4,
    requestDenied = 5
};


struct request_handler_state_st {
    RequestHandlerStateEn state;
    uint32_t request_amount;
    double sigma;

    explicit request_handler_state_st():state(RequestHandlerStateEn::passive),\
                                    sigma(limits::infinity())
                                    {}
};

#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const request_handler_state_st& state) {
    out  << "Next State = " << (int)state.state;
    return out;
}
#endif

class request_handler : public Atomic<request_handler_state_st> {
    private:
        
    public:
    // Input ports
    Port<bool> pin_valid_in;
    Port<uint32_t> amount_in;
    Port<bool> approved_in;
    // Output ports
    Port<uint32_t> request_out;
    Port<uint32_t> dispense_out;
    Port<bool> eject_out;

    request_handler(const std::string id) : Atomic<request_handler_state_st>(id, request_handler_state_st())
    {
        pin_valid_in = addInPort<bool>("pin_valid_in");
        amount_in = addInPort<uint32_t>("amount_in");
        approved_in = addInPort<bool>("approved_in");
        request_out = addOutPort<uint32_t>("request_out");
        dispense_out = addOutPort<uint32_t>("dispense_out");
        eject_out = addOutPort<bool>("eject_out");
    }

    void internalTransition(request_handler_state_st& state) const override {
        switch(state.state) {
        case RequestHandlerStateEn::requestReceived:
            state.state = RequestHandlerStateEn::pendingApproval;
            state.sigma = limits::infinity();
            break;
        case RequestHandlerStateEn::requestApproved:
            state.state = RequestHandlerStateEn::passive;
            state.sigma = limits::infinity();
            break;
        case RequestHandlerStateEn::requestDenied:
            state.state = RequestHandlerStateEn::passive;
            state.sigma = limits::infinity();
            break;
        default:
            break;
        }
    }

    // external transition
    void externalTransition(request_handler_state_st& state, double e) const override {
        if (!pin_valid_in->empty()) {
            for (const auto &input : pin_valid_in->getBag()) {
                if (state.state == RequestHandlerStateEn::passive) {
                    state.state = RequestHandlerStateEn::cardAccepted;
                    state.sigma = limits::infinity();
                    return;
                }
            }
        }
        if (!amount_in->empty()) {
            for (const auto &input : amount_in->getBag()) {
                if (state.state == RequestHandlerStateEn::cardAccepted) {
                    state.state = RequestHandlerStateEn::requestReceived;
                    state.sigma = 0;
                    return;
                }
                if (state.state == RequestHandlerStateEn::passive) {
                    state.state = RequestHandlerStateEn::requestDenied;
                    state.sigma = 0;
                }
            }
        }
        if (!approved_in->empty()) {
            for (const auto &input : approved_in->getBag()) {
                if (state.state == RequestHandlerStateEn::pendingApproval) {
                    if (input) {
                        state.state = RequestHandlerStateEn::requestApproved;
                    } else {
                        state.state = RequestHandlerStateEn::requestDenied;
                    }
                    state.sigma = 0;
                    return;
                }
            }
        }
        
        state.sigma -= e;
    }
    
    // output function
    void output(const request_handler_state_st& state) const override {
        switch(state.state) {
            case RequestHandlerStateEn::requestReceived:
                request_out->addMessage(state.request_amount);
                break;
            case RequestHandlerStateEn::requestApproved:
                dispense_out->addMessage(state.request_amount);
                break;
            case RequestHandlerStateEn::requestDenied:
                eject_out->addMessage(true);
                break;
            default:
                break;
            }
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const request_handler_state_st& state) const override {
        return state.sigma;
    }
};

#endif