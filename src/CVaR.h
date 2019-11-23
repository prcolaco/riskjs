// Portfolio VaR through MC simulation
// from test_ptf_mc_var.cpp

#pragma once


#include <string>
#include <vector>


namespace RiskJS {

// Vectors types for function arguments
typedef std::vector<std::string> priceRow;
typedef std::vector<priceRow> priceData;
typedef std::vector<double> weightData;

double CVaRMonteCarlo(priceData rawPrices, weightData weights, double alphatest);
double CVaRHistorical(priceData rawPrices, weightData weights, double alphatest);
double CVaRVarianceCovariance(priceData rawPrices, weightData weights, double alphatest);

}  // namespace RiskJS
