#pragma once
#include <string>
class MarketProvider {
  public:
    virtual double getCurrentPrice(const std::string& asset) = 0;
};
