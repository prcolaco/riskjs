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


double CVaRHistorical(priceData rawPrices, weightData weights, double alphatest) {
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
    // Asynchornous time series. Shift to the next value
    Mat prices;
    prices.resize(m,Vec(0));

		for(size_t i = 0;i < _prices.size();++i){
	        for(size_t j = 0;j < _prices[i].size();++j){
	            if(!((_prices[i][j] == 99999) || (_prices[i][j] == 0)))
	                prices[i].push_back(_prices[i][j]);
	        }
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

    // CVaRhistorical
    model.setAlpha(1.0-alphatest);
    double CVaRHistorical = model(0,ptf->getReturns());

    return CVaRHistorical;
}

}
