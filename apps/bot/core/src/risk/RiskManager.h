#pragma once
#include "Trade.h"

class RiskManager {
	public:
    virtual bool assessRisk(Trade& trade) = 0;
};

class AlwaysConfidentRiskManager : public RiskManager {
  public:
    bool assessRisk(Trade& trade) override {
        return true;
    }
};
