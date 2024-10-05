#pragma once
#include "MarketProvider.h"

class AlphaVantageMarketProvider : public MarketProvider {
  private:
    void fetch();
};
