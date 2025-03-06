#ifndef CARD_READER_TEST_2_HPP
#define CARD_READER_TEST_2_HPP

#include "cadmium/modeling/devs/coupled.hpp" //cadmium header
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "card_reader.hpp"                   //card_reader atomic model file

using namespace cadmium;

struct card_reader_test_2: public Coupled {

  card_reader_test_2(const std::string& id): Coupled(id){
    auto card_reader_model = addComponent<card_reader>("card_reader model");
    auto eject_in_file = addComponent<lib::IEStream<bool>>("eject_in file",  "/home/owen/DEVS_ATM/test_inputs/card_reader_inputs/test_case_2/eject_in.txt");

    //Internal Couplings
    addCoupling(eject_in_file->out, card_reader_model->eject_in);
  }

};


#endif