// Portfolio VaR through MC simulation
// from test_ptf_mc_var.cpp

#pragma once


#include <string>
#include <vector>


namespace RiskJS {

// typedef for Javascript array of arrays of strings
typedef std::vector< std::vector<std::string>> dataArray;

double portfolioMonteCarloVaR(dataArray data);

}
