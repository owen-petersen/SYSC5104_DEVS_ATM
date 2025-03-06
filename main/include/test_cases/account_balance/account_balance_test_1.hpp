#ifndef ACCOUNT_BALANCE_TEST_1_HPP
#define ACCOUNT_BALANCE_TEST_1_HPP

#include "cadmium/modeling/devs/coupled.hpp" //cadmium header
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "account_balance.hpp"                   //account_balance atomic model file

using namespace cadmium;

struct account_balance_test_1: public Coupled {

  account_balance_test_1(const std::string& id): Coupled(id){
    auto account_balance_model = addComponent<account_balance>("account_balance model");
    auto request_in_file = addComponent<lib::IEStream<uint32_t>>("request_in file", "/home/owen/DEVS_ATM/test_inputs/account_balance_inputs/test_case_1/request_in.txt");

    //Internal Couplings
    addCoupling(request_in_file->out, account_balance_model->request_in);
  }

};


#endif