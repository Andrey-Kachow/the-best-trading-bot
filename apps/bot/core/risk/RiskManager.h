#pragma once
#include "Trade.h"

class RiskManager {
	public:
    virtual bool assessRisk(Trade& trade) = 0;
};

class BraveRiskManager : public RiskManager {
  public:
    bool assessRisk(Trade& trade) {
        return true;
    }
};
