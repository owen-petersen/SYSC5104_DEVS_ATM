#ifndef CARD_READER_TEST_1_HPP
#define CARD_READER_TEST_1_HPP

#include "cadmium/modeling/devs/coupled.hpp" //cadmium header
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "card_reader.hpp"                   //card_reader atomic model file

using namespace cadmium;

struct card_reader_test_1: public Coupled {

  card_reader_test_1(const std::string& id): Coupled(id){
    auto card_reader_model = addComponent<card_reader>("card_reader model");
    auto card_in_file = addComponent<lib::IEStream<bool>>("card_in file", "/home/owen/DEVS_ATM/test_inputs/card_reader_inputs/test_case_1/card_in.txt");
    auto eject_in_file = addComponent<lib::IEStream<bool>>("eject_in file",  "/home/owen/DEVS_ATM/test_inputs/card_reader_inputs/test_case_1/eject_in.txt");

    //Internal Couplings
    addCoupling(card_in_file->out, card_reader_model->card_in);
    addCoupling(eject_in_file->out, card_reader_model->eject_in);
  }

};


#endif