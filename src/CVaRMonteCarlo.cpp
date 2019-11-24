// Portfolio VaR through MC simulation
// from test_ptf_mc_var.cpp

#include <string>
#include <vector>

#include <Eigen/Dense>

#include "CVaR.h"

#include "compute_returns_eigen.h"
#include "compute_var.h"
#include "path.h"
#include "mc_engine.h"
#include "rng.h"
#include "pca.h"
#include "portfolio.h"
#include "ptf_var.h"

#include <boost/math/special_functions/erf.hpp>
using boost::math::erfc_inv;

namespace RiskJS {


using namespace Eigen;
using namespace std;


double CVaRMonteCarlo(priceData rawPrices, weightData weights, double alphatest) {
    // Remove lines with missing values
    size_t n(rawPrices.size() - 1);
    size_t m(rawPrices[0].size() - 1);

    Mat _prices;
    _prices.resize(m,Vec(n));

    for(size_t i = 1;i < n+1;++i){
        for(size_t j = 1;j < rawPrices[i].size();++j){
            string tmp = rawPrices[i][j];
            if(tmp.empty()){
                _prices[j-1][i-1] = 99999.;
            }
            else{
                _prices[j-1][i-1] = stod(tmp);
            }
        }
    }

    vector<string> indexNames(rawPrices[0].size() - 1);

    for(size_t i = 1;i < rawPrices[0].size();++i){
        indexNames[i-1] = rawPrices[0][i];
    }

		// Remove missing values to compute trailling returns
    Mat prices;
    prices.resize(m,Vec(0));

    bool goodrow = true;
    for(size_t j = 0;j < _prices[0].size();++j){
        for(size_t i = 0;i < _prices.size();++i){
            if((_prices[i][j] == 99999) || (_prices[i][j] == 0))
                goodrow = false;
        }
        if (goodrow)
            for(size_t i = 0;i < _prices.size();++i){
                prices[i].push_back(_prices[i][j]);
            }
            goodrow = true;
        }
    unsigned int windowsize = prices[0].size()-2;
    std::shared_ptr<ComputeReturn> cr(new ComputeReturn(prices,1,windowsize,true));

    // create portfolio
  	Ptf _ptf;
  	for(size_t i = 0;i < m;++i){
          shared_ptr<Instrument> instrument(new DeltaOne());
          auto p = std::make_pair(i,instrument);
  		_ptf.push_back(p);
  	}
  	shared_ptr<Portfolio> ptf(new Portfolio(_ptf, weights, cr, false, 1.e+07));

    HistoricalVaR model;

    // CVaRMonteCarlo
    // Simulate crypto rtn using AR(1)xGARCH(1,1) through brute force Monte-Carlo
	  std::vector<AR1xGARCH11> processes(2);
    processes[0] = AR1xGARCH11(); // first crypto asset AR1xGARCH11( 0.,0.5,omega, alpha=.24, beta=.76); note beta, alpha, omega correspond to python arch_model
    processes[1] = AR1xGARCH11(); // 2nd crypto asset
    Path1x1 process;
    rng _rng;
    VaRPtfMCCompute<HistoricalVaR, AR1xGARCH11> VaRMonteCarlo(ptf,model, processes, _rng, 1.0-alphatest);
    double CVaRMonteCarlo = VaRMonteCarlo.computeVaR();

    return CVaRMonteCarlo;
}

}
