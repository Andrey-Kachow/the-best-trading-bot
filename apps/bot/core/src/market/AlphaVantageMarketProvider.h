#pragma once
#include "MarketProvider.h"

class AlphaVantageMarketProvider : public MarketProvider {
  private:
    void fetch();

  public:
    virtual std::unique_ptr<PriceData> getCurrentPriceData(const std::string& asset) override;
};
