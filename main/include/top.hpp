#ifndef TOP_HPP
#define TOP_HPP

#include "cadmium/modeling/devs/coupled.hpp"
#include "card_reader.hpp"
#include "cash_manager.hpp"
#include "validation.hpp"

using namespace cadmium;
struct topSystem : public Coupled {

    // The Ports
    Port<bool> card_in;
    Port<uint16_t> pin_in;
    Port<uint32_t> amount_in;
    Port<bool> card_out;
    Port<uint32_t> cash_out;

    /**
     * Constructor function for the blinkySystem model.
     * @param id ID of the blinkySystem model.
     */
    topSystem(const std::string& id) : Coupled(id) {
        card_in = addInPort<bool>("card_in");
        pin_in = addInPort<uint16_t>("pin_in");
        amount_in = addInPort<uint32_t>("amount_in");
        card_out = addOutPort<bool>("card_out");
        cash_out = addOutPort<uint32_t>("cash_out");

        // Components
        auto card_reader_model = addComponent<card_reader>("card_reader");
        auto validation_model = addComponent<validation>("validation");
        auto cash_manager_model = addComponent<cash_manager>("cash_manager");

        // Internal Couplings
        addCoupling(card_reader_model->card_number_out, validation_model->card_number_in);
        addCoupling(validation_model->eject_out, card_reader_model->eject_in);
        addCoupling(validation_model->dispense_out, cash_manager_model->dispense_in);
        // External Input Couplings
        addCoupling(this->card_in, card_reader_model->card_in);
        addCoupling(this->pin_in, validation_model->pin_in);
        addCoupling(this->amount_in, validation_model->amount_in);
        // External Output Couplings
        addCoupling(card_reader_model->card_out, this->card_out);
        addCoupling(cash_manager_model->cash_out, this->cash_out);
    }
};

#endif