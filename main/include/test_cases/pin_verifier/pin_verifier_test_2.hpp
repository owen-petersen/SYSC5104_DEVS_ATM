#ifndef PIN_VERIFIER_TEST_2_HPP
#define PIN_VERIFIER_TEST_2_HPP

#include "cadmium/modeling/devs/coupled.hpp" //cadmium header
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "pin_verifier.hpp"                   //pin_verifier atomic model file

using namespace cadmium;

struct pin_verifier_test_2: public Coupled {

  pin_verifier_test_2(const std::string& id): Coupled(id){
    auto pin_verifier_model = addComponent<pin_verifier>("pin_verifier model");
    auto pin_in_file = addComponent<lib::IEStream<uint16_t>>("pin_in file",  "/home/owen/DEVS_ATM/test_inputs/pin_verifier_inputs/test_case_2/pin_in.txt");

    //Internal Couplings
    addCoupling(pin_in_file->out, pin_verifier_model->pin_in);
  }

};


#endif