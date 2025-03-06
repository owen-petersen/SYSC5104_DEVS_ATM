#ifndef PIN_VERIFIER_TEST_3_HPP
#define PIN_VERIFIER_TEST_3_HPP

#include "cadmium/modeling/devs/coupled.hpp" //cadmium header
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "pin_verifier.hpp"                   //pin_verifier atomic model file

using namespace cadmium;

struct pin_verifier_test_3: public Coupled {

  pin_verifier_test_3(const std::string& id): Coupled(id){
    auto pin_verifier_model = addComponent<pin_verifier>("pin_verifier model");
    auto card_number_in_file = addComponent<lib::IEStream<uint16_t>>("card_number_in file", "/home/owen/DEVS_ATM/test_inputs/pin_verifier_inputs/test_case_3/card_number_in.txt");
    auto pin_in_file = addComponent<lib::IEStream<uint16_t>>("pin_in file",  "/home/owen/DEVS_ATM/test_inputs/pin_verifier_inputs/test_case_3/pin_in.txt");

    //Internal Couplings
    addCoupling(card_number_in_file->out, pin_verifier_model->card_number_in);
    addCoupling(pin_in_file->out, pin_verifier_model->pin_in);
  }

};


#endif