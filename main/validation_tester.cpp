#include "cadmium/simulation/root_coordinator.hpp"
#include <limits>
#include "test_cases/validation/validation_test_1.hpp"
#include "test_cases/validation/validation_test_2.hpp"
#include "test_cases/validation/validation_test_3.hpp"

#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"

using namespace cadmium;


int main()
{
	auto model = std::make_shared<validation_test_1> ("validation_test_1");
	auto rootCoordinator = cadmium::RootCoordinator(model);

	//rootCoordinator.setLogger<STDOUTLogger>(";");
	rootCoordinator.setLogger<cadmium::CSVLogger>("test_results/validation_tests/validation_test_1.csv", ";");

	rootCoordinator.start();
	rootCoordinator.simulate(8.0);
	rootCoordinator.stop();
	

	auto model2 = std::make_shared<validation_test_2> ("validation_test_2");
	auto rootCoordinator2 = cadmium::RootCoordinator(model2);

	//rootCoordinator2.setLogger<STDOUTLogger>(";");
	rootCoordinator2.setLogger<cadmium::CSVLogger>("test_results/validation_tests/validation_test_2.csv", ";");

	rootCoordinator2.start();
	rootCoordinator2.simulate(8.0);
	rootCoordinator2.stop();

	
	auto model3 = std::make_shared<validation_test_3> ("validation_test_3");
	auto rootCoordinator3 = cadmium::RootCoordinator(model3);

	//rootCoordinator2.setLogger<STDOUTLogger>(";");
	rootCoordinator3.setLogger<cadmium::CSVLogger>("test_results/validation_tests/validation_test_3.csv", ";");

	rootCoordinator3.start();
	rootCoordinator3.simulate(8.0);
	rootCoordinator3.stop();
	
	return 0;
}


