#pragma once
#include <memory>
#include "market/MarketProvider.h"
#include "Logger.h"
#include "risk/RiskManager.h"

class MainApp {

  private:
    std::unique_ptr<MarketProvider> _marketProvider;
    std::unique_ptr<Logger> _logger;
    std::unique_ptr<RiskManager> _riskManager;

  public:
    MainApp();
      
    void start();
};
