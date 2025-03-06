#ifndef VALIDATION_TEST_1_HPP
#define VALIDATION_TEST_1_HPP

#include "cadmium/modeling/devs/coupled.hpp" //cadmium header
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "validation.hpp"                   //validation coupled model file

using namespace cadmium;

struct validation_test_1: public Coupled {

  validation_test_1(const std::string& id): Coupled(id){
    auto validation_model = addComponent<validation>("validation model");
    auto card_number_in_file = addComponent<lib::IEStream<uint16_t>>("card_number_in file", "/home/owen/DEVS_ATM/test_inputs/validation_inputs/test_case_1/card_number_in.txt");
    auto pin_in_file = addComponent<lib::IEStream<uint16_t>>("pin_in file",  "/home/owen/DEVS_ATM/test_inputs/validation_inputs/test_case_1/pin_in.txt");

    //Internal Couplings
    addCoupling(card_number_in_file->out, validation_model->card_number_in);
    addCoupling(pin_in_file->out, validation_model->pin_in);

  }

};


#endif