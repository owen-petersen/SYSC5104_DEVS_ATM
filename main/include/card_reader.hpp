#ifndef CARD_READER_HPP
#define CARD_READER_HPP

#include <iostream>
#include <iomanip>
#include "cadmium/modeling/devs/atomic.hpp"

using namespace cadmium;

enum class cardReaderStateEn : int {
    passive = 0,
    cardReceived = 1,
    hasCard = 2,
    ejectCard = 3
};


#ifndef NO_LOGGING
std::ostream& operator<<(std::ostream &out, const cardReaderStateEn& state) {
    out  << "Next State = " << (int)state;
    return out;
}
#endif

class card_reader : public Atomic<cardReaderStateEn> {
    private:
        
    public:
    // Input ports
    Port<bool> card_in;
    Port<bool> eject_in;
    // Output ports
    Port<uint16_t> card_number_out;
    Port<bool> card_out;

    card_reader(const std::string id) :   Atomic<cardReaderStateEn>(id, cardReaderStateEn::passive)
    {
        card_in = addInPort<bool>("card_in");
        eject_in = addInPort<bool>("eject_in");
        card_number_out = addOutPort<uint16_t>("card_number_out");
        card_out = addOutPort<bool>("card_out");
    }

    void internalTransition(cardReaderStateEn& state) const override {
        switch(state){
        case cardReaderStateEn::cardReceived:
            state = cardReaderStateEn::hasCard;
            break;
        case cardReaderStateEn::ejectCard:
            state = cardReaderStateEn::passive;
            break;
        default:
            break;
        }
    }

    // external transition
    void externalTransition(cardReaderStateEn& state, double e) const override {
        if (!card_in->empty()) {
            if (state == cardReaderStateEn::passive) {
                state = cardReaderStateEn::cardReceived;
                return;
            }
        }
        if (!eject_in->empty()) {
            if (state == cardReaderStateEn::hasCard) {
                state = cardReaderStateEn::ejectCard;
                return;
            }
        }
    }
    
    // output function
    void output(const cardReaderStateEn& state) const override {
        switch(state){
        case cardReaderStateEn::cardReceived:
            card_number_out->addMessage(111); // Hardcoded card number
            break;
        case cardReaderStateEn::ejectCard:
            card_out->addMessage(1);
            break;
        default:
            break;
        }
    }

    // time_advance function
    [[nodiscard]] double timeAdvance(const cardReaderStateEn& state) const override {
        

        return 1.0; // handles illegal conditions
    }
};

#endif