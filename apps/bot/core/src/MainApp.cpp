#include "MainApp.h"
#include <market/AlphaVantageMarketProvider.h>

MainApp::MainApp() : _marketProvider(std::make_unique<AlphaVantageMarketProvider>()) {
}

void MainApp::start() {

	auto assetPrice = _marketProvider->getCurrentPriceData("GLD");
}
