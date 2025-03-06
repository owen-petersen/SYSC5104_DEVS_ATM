#include "cadmium/simulation/root_coordinator.hpp"
#include <limits>
#include "test_cases/pin_verifier/pin_verifier_test_1.hpp"
#include "test_cases/pin_verifier/pin_verifier_test_2.hpp"
#include "test_cases/pin_verifier/pin_verifier_test_3.hpp"


#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"

using namespace cadmium;


int main()
{
	auto model = std::make_shared<pin_verifier_test_1> ("pin_verifier_test_1");
	auto rootCoordinator = cadmium::RootCoordinator(model);

	//rootCoordinator.setLogger<STDOUTLogger>(";");
	rootCoordinator.setLogger<cadmium::CSVLogger>("test_results/pin_verifier_tests/pin_verifier_test_1.csv", ";");

	rootCoordinator.start();
	rootCoordinator.simulate(4.0);
	rootCoordinator.stop();

	auto model2 = std::make_shared<pin_verifier_test_2> ("pin_verifier_test_2");
	auto rootCoordinator2 = cadmium::RootCoordinator(model2);

	//rootCoordinator.setLogger<STDOUTLogger>(";");
	rootCoordinator2.setLogger<cadmium::CSVLogger>("test_results/pin_verifier_tests/pin_verifier_test_2.csv", ";");

	rootCoordinator2.start();
	rootCoordinator2.simulate(3.0);
	rootCoordinator2.stop();

	auto model3 = std::make_shared<pin_verifier_test_3> ("pin_verifier_test_3");
	auto rootCoordinator3 = cadmium::RootCoordinator(model3);

	//rootCoordinator.setLogger<STDOUTLogger>(";");
	rootCoordinator3.setLogger<cadmium::CSVLogger>("test_results/pin_verifier_tests/pin_verifier_test_3.csv", ";");

	rootCoordinator3.start();
	rootCoordinator3.simulate(8.0);
	rootCoordinator3.stop();

	return 0;
}


