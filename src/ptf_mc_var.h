// Portfolio VaR through MC simulation
// from test_ptf_mc_var.cpp

#pragma once


#include <string>
#include <vector>


namespace RiskJS {

// typedef for Javascript array of arrays of strings
typedef std::vector<std::string> priceRow;
typedef std::vector<priceRow> priceData;

double portfolioMonteCarloVaR(priceData data);

}  // namespace RiskJS
