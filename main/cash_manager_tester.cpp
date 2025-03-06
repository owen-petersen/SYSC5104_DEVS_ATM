#include "cadmium/simulation/root_coordinator.hpp"
#include <limits>
#include "test_cases/cash_manager/cash_manager_test_1.hpp"

#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"

using namespace cadmium;


int main()
{
	auto model = std::make_shared<cash_manager_test_1> ("cash_manager_test_1");
	auto rootCoordinator = cadmium::RootCoordinator(model);

	//rootCoordinator.setLogger<STDOUTLogger>(";");
	rootCoordinator.setLogger<cadmium::CSVLogger>("test_results/cash_manager_tests/cash_manager_test_1.csv", ";");

	rootCoordinator.start();
	rootCoordinator.simulate(3.0);
	rootCoordinator.stop();
	
	return 0;
}


