# DEVS ATM
|  Linux | Windows| ESP32 | MSP432 |
|:--|:--|:--|:--|
|:heavy_check_mark:|:heavy_check_mark:|:x:|:x:|

## Introduction
This repository contains cadmium_v2 implementation ATM system DEVS model

## Dependencies
This project assumes that you have Cadmium installed in a location accessible by the environment variable $CADMIUM.
_This dependency would be met by default if you are using the DEVSsim servers. To check, try `echo $CADMIUM` in the terminal_

## Build
To build this project, run:
```sh
source build_sim.sh
```
__NOTE__: Everytime you run build_sim.sh, the contents of `build/` and `bin/` will be replaced.

## Execute
To run the testers in this project and generate the results file , run any of the following:
```sh
./bin/account_balance_tester
./bin/card_reader_tester
./bin/cash_manager_tester
./bin/pin_verifier_tester
./bin/request_handler_tester
./bin/top_tester
./bin/validation_tester
```


For more information about the models in this repository, and to learn more about modeling in Cadmium, look at the developer's manual found [here](https://devssim.carleton.ca/manuals/developer/).