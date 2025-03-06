#include "cadmium/simulation/root_coordinator.hpp"
#include <limits>
#include "test_cases/account_balance/account_balance_test_1.hpp"
#include "test_cases/account_balance/account_balance_test_2.hpp"

#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"

using namespace cadmium;


int main()
{
	auto model = std::make_shared<account_balance_test_1> ("account_balance_test_1");
	auto rootCoordinator = cadmium::RootCoordinator(model);

	//rootCoordinator.setLogger<STDOUTLogger>(";");
	rootCoordinator.setLogger<cadmium::CSVLogger>("test_results/account_balance_tests/account_balance_test_1.csv", ";");

	rootCoordinator.start();
	rootCoordinator.simulate(4.0);
	rootCoordinator.stop();

	auto model2 = std::make_shared<account_balance_test_2> ("account_balance_test_2");
	auto rootCoordinator2 = cadmium::RootCoordinator(model2);

	//rootCoordinator.setLogger<STDOUTLogger>(";");
	rootCoordinator2.setLogger<cadmium::CSVLogger>("test_results/account_balance_tests/account_balance_test_2.csv", ";");

	rootCoordinator2.start();
	rootCoordinator2.simulate(6.0);
	rootCoordinator2.stop();

	return 0;
}


