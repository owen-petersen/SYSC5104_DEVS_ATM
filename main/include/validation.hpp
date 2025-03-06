#ifndef VALIDATION_HPP
#define VALIDATION_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "pin_verifier.hpp"
#include "account_balance.hpp"
#include "request_handler.hpp"

using namespace cadmium;
struct validation : public Coupled {

    // Ports
    Port<uint16_t> card_number_in;
    Port<uint16_t> pin_in;
    Port<uint32_t> amount_in;
    Port<bool> eject_out;
    Port<uint32_t> dispense_out;

    /**
     * Constructor function for the blinkySystem model.
     * @param id ID of the blinkySystem model.
     */
    validation(const std::string& id) : Coupled(id) {
        card_number_in = addInPort<uint16_t>("card_number_in");
        pin_in = addInPort<uint16_t>("pin_in");
        amount_in = addInPort<uint32_t>("amount_in");
        eject_out = addOutPort<bool>("eject_out");
        dispense_out = addOutPort<uint32_t>("dispense_out");

        // Components
        auto pin_verifier_model = addComponent<pin_verifier>("pin_verifier");
        auto request_handler_model = addComponent<request_handler>("request_handler");
        auto account_balance_model = addComponent<account_balance>("account_balance");

        // Internal Couplings
        addCoupling(pin_verifier_model->pin_valid_out, request_handler_model->pin_valid_in);
        addCoupling(request_handler_model->request_out, account_balance_model->request_in);
        addCoupling(account_balance_model->approved_out, request_handler_model->approved_in);
        // External Input Couplings
        addCoupling(this->card_number_in, pin_verifier_model->card_number_in);
        addCoupling(this->pin_in, pin_verifier_model->pin_in);
        addCoupling(this->amount_in, request_handler_model->amount_in);
        // External Output Couplings
        addCoupling(request_handler_model->eject_out, this->eject_out);
        addCoupling(request_handler_model->dispense_out, this->dispense_out);
    }
};

#endif