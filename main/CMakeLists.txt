# Link main file to executable namee
add_executable(main main.cpp)
add_executable(card_reader_tester card_reader_tester.cpp)
add_executable(request_handler_tester request_handler_tester.cpp)
add_executable(top_tester top_tester.cpp)
add_executable(pin_verifier_tester pin_verifier_tester.cpp)
add_executable(validation_tester validation_tester.cpp)
add_executable(cash_manager_tester cash_manager_tester.cpp)
add_executable(account_balance_tester account_balance_tester.cpp)



# Add required libraries and include directories
target_include_directories(main PRIVATE "." "include" $ENV{CADMIUM})
target_include_directories(card_reader_tester PRIVATE "." "include" $ENV{CADMIUM})
target_include_directories(request_handler_tester PRIVATE "." "include" $ENV{CADMIUM})
target_include_directories(top_tester PRIVATE "." "include" $ENV{CADMIUM})
target_include_directories(pin_verifier_tester PRIVATE "." "include" $ENV{CADMIUM})
target_include_directories(validation_tester PRIVATE "." "include" $ENV{CADMIUM})
target_include_directories(cash_manager_tester PRIVATE "." "include" $ENV{CADMIUM})
target_include_directories(account_balance_tester PRIVATE "." "include" $ENV{CADMIUM})



# set c++ standard
target_compile_options(main PUBLIC -std=gnu++2b)
target_compile_options(card_reader_tester PUBLIC -std=gnu++2b)
target_include_directories(request_handler_tester PRIVATE "." "include" $ENV{CADMIUM})
target_compile_options(top_tester PUBLIC -std=gnu++2b)
target_compile_options(pin_verifier_tester PUBLIC -std=gnu++2b)
target_compile_options(validation_tester PUBLIC -std=gnu++2b)
target_compile_options(cash_manager_tester PUBLIC -std=gnu++2b)
target_compile_options(account_balance_tester PUBLIC -std=gnu++2b)