#ifndef TOP_TEST_1_HPP
#define TOP_TEST_1_HPP

#include "cadmium/modeling/devs/coupled.hpp" //cadmium header
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "top.hpp"                   //top coupled model file

using namespace cadmium;

struct top_test_1: public Coupled {

  top_test_1(const std::string& id): Coupled(id){
    auto top_model = addComponent<topSystem>("top model");
    auto card_in_file = addComponent<lib::IEStream<bool>>("card_in file", "/home/owen/DEVS_ATM/test_inputs/top_inputs/test_case_1/card_in.txt");
    auto pin_in_file = addComponent<lib::IEStream<uint16_t>>("pin_in file",  "/home/owen/DEVS_ATM/test_inputs/top_inputs/test_case_1/pin_in.txt");
    auto amount_in_file = addComponent<lib::IEStream<uint32_t>>("amount_in file",  "/home/owen/DEVS_ATM/test_inputs/top_inputs/test_case_1/amount_in.txt");

    //Internal Couplings
    addCoupling(card_in_file->out, top_model->card_in);
    addCoupling(pin_in_file->out, top_model->pin_in);
    addCoupling(amount_in_file->out, top_model->amount_in);

  }

};


#endif