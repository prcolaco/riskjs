//test_ptf_mc_var.cpp

//test portfolio VaR through MC simulation

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include<memory>

#include <Eigen/Dense>

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

using namespace Eigen;
using namespace std;

void readCSV(std::istream &input, std::vector< std::vector<std::string> > &output)
//https://www.gamedev.net/topic/444193-c-how-to-load-in-a-csv-file/
{
	std::string csvLine;
	// read every line from the stream
	while( std::getline(input, csvLine) )
	{
		std::istringstream csvStream(csvLine);
		std::vector<std::string> csvColumn;
		std::string csvElement;
		// read every element from the line that is seperated by commas
		// and put it into the vector or strings
		while( std::getline(csvStream, csvElement, ',') )
		{
			csvColumn.push_back(csvElement);
		}
		output.push_back(csvColumn);
	}
}


int main()
{

    try{

    // Read daily price history for crypto assets, in USD
    //Date,EOS,DAPP
    //2018-11-19,3.5,0.5
    //2018-11-20,3.6,0.6 

	std::fstream file("/home/gg/VaR/test/data.csv", ios::in);
	if(!file.is_open())
	{
		std::cout << "File not found!\n";
		return 1;
	}
	// typedef to save typing for the following object
	typedef std::vector< std::vector<std::string> > csvVector;
	csvVector csvData;

	readCSV(file, csvData);

    //test
    for(size_t i = 0;i < 5; ++i){
        for(size_t j = 0;j < csvData[i].size();++j){
            cout << csvData[i][j] << '\t';

        }

        cout << endl;
    }
    cout << endl;

    // Remove lines with missing values

    size_t n(csvData.size() - 1);
    size_t m(csvData[0].size() - 1);

    Mat _prices;
    _prices.resize(m,Vec(n));

    for(size_t i = 1;i < n+1;++i){
        for(size_t j = 1;j < csvData[i].size();++j){
            std::string tmp = csvData[i][j];
            if(tmp.empty()){
                _prices[j-1][i-1] = 99999.;
            }
            else{
                _prices[j-1][i-1] = std::stod(tmp);
            }
        }
    }

    std::vector<std::string> indexNames(csvData[0].size() - 1);

    for(size_t i = 1;i < csvData[0].size();++i){
        indexNames[i-1] = csvData[0][i];
    }

	//Remove missing values to compute trailling returns
    //Asynchornous time series. Shift to the next value
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
	double a = double(1./m);
	std::vector<double> weights{a,a}; //initialization. Equi-weighted asset for mere convenience
	Ptf _ptf;
	for(size_t i = 0;i < m;++i){
        shared_ptr<Instrument> instrument(new DeltaOne());
        auto p = std::make_pair(i,instrument);
		_ptf.push_back(p);
	}
	shared_ptr<Portfolio> ptf(new Portfolio(_ptf, weights, cr, false, 1.e+07));

    HistoricalVaR model;

    double alphatest = .95; // set alpha level, example 0.9 for 95% CVaR

   // CVaRMonteCarlo
   // Simulate crypto rtn using AR(1)xGARCH(1,1) through brute force Monte-Carlo
	std::vector<AR1xGARCH11> processes(2);
    processes[0] = AR1xGARCH11(); // first crypto asset AR1xGARCH11( 0.,0.5,omega, alpha=.24, beta=.76); note beta, alpha, omega correspond to python arch_model
    processes[1] = AR1xGARCH11(); // 2nd crypto asset
    Path1x1 process;
    rng _rng;
    VaRPtfMCCompute<HistoricalVaR, AR1xGARCH11> VaRMonteCarlo(ptf,model, processes, _rng, 1.0-alphatest);
    double CVaRMonteCarlo = VaRMonteCarlo.computeVaR();
	cout << "CVaRMonteCarlo: " << CVaRMonteCarlo << endl;

    return 0;

    } catch (const std::exception& e) { // caught by reference to base
        std::cout << " a standard exception was caught, with message '"
                  << e.what() << "'\n";
    }

}


