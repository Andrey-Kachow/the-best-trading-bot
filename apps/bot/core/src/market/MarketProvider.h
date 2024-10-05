#pragma once
#include <string>
#include "PriceData.h"
#include <memory>

class MarketProvider {
  public:
    virtual std::unique_ptr<PriceData> getCurrentPriceData(const std::string& asset) = 0;
};
