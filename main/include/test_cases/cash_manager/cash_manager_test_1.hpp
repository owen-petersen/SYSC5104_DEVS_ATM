#ifndef CASH_MANAGER_TEST_1_HPP
#define CASH_MANAGER_TEST_1_HPP

#include "cadmium/modeling/devs/coupled.hpp" //cadmium header
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "cash_manager.hpp"                   //cash_manager atomic model file

using namespace cadmium;

struct cash_manager_test_1: public Coupled {

  cash_manager_test_1(const std::string& id): Coupled(id){
    auto cash_manager_model = addComponent<cash_manager>("cash_manager model");
    auto dispense_in_file = addComponent<lib::IEStream<uint32_t>>("dispense_in file", "/home/owen/DEVS_ATM/test_inputs/cash_manager_inputs/test_case_1/dispense_in.txt");

    //Internal Couplings
    addCoupling(dispense_in_file->out, cash_manager_model->dispense_in);
  }

};


#endif