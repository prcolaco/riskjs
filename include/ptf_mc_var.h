// Portfolio VaR through MC simulation
// from test_ptf_mc_var.cpp

#include <string>
#include <vector>

#ifndef PTF_MC_VAR_H
#define PTF_MC_VAR_H

namespace RiskJS {

// typedef for Javascript array of arrays of strings
typedef std::vector< std::vector<std::string>> dataArray;

double portfolioMonteCarloVaR(dataArray data);

}

#endif //PTF_MC_VAR_H
