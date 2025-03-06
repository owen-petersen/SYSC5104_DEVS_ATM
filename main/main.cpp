#include "cadmium/simulation/root_coordinator.hpp"
#include <limits>
#include "include/top.hpp"

#include "cadmium/simulation/logger/stdout.hpp"
#include "cadmium/simulation/logger/csv.hpp"

using namespace cadmium;


int main()
{
	std::shared_ptr<topSystem> model = std::make_shared<topSystem> ("topSystem");
	auto rootCoordinator = cadmium::RootCoordinator(model);

	rootCoordinator.setLogger<STDOUTLogger>(";");
	//rootCoordinator.setLogger<cadmium::CSVLogger>("trafficLightLog.csv", ";");

	rootCoordinator.start();
	rootCoordinator.simulate(23.0);
	rootCoordinator.stop();

	return 0;
}


