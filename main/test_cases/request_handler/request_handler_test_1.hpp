#ifndef REQUEST_HANDLER_TEST_1_HPP
#define REQUEST_HANDLER_TEST_1_HPP

#include "cadmium/modeling/devs/coupled.hpp" //cadmium header
#include "cadmium/lib/iestream.hpp"          //iestream header
#include "request_handler.hpp"                   //request_handler atomic model file

using namespace cadmium;

struct request_handler_test_1: public Coupled {

  request_handler_test_1(const std::string& id): Coupled(id){
    auto request_handler_model = addComponent<request_handler>("request_handler model");
    auto amount_in_file = addComponent<lib::IEStream<uint32_t>>("amount_in file", "/home/owen/DEVS_ATM/test_inputs/request_handler_inputs/test_case_1/amount_in.txt");
    auto approved_in_file = addComponent<lib::IEStream<bool>>("approved_in file",  "/home/owen/DEVS_ATM/test_inputs/request_handler_inputs/test_case_1/approved_in.txt");
    auto pin_valid_in_file = addComponent<lib::IEStream<bool>>("pin_valid_in file",  "/home/owen/DEVS_ATM/test_inputs/request_handler_inputs/test_case_1/pin_valid_in.txt");

    //Internal Couplings
    addCoupling(amount_in_file->out, request_handler_model->amount_in);
    addCoupling(approved_in_file->out, request_handler_model->approved_in);
    addCoupling(pin_valid_in_file->out, request_handler_model->pin_valid_in);

  }

};


#endif