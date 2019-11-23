# RiskJS

The goal of this project is to port [Calvin456/VaR](https://github.com/calvin456/VaR) library into JavaScript for Portfolio Value at Risk calculation.

This library for now includes CVaR computation using the following methods:
- Historical
- Monte Carlo
- Variance Covariance (used now in Vigor project)

Many other quantitative finance computations might be added in the future to facilitate the use of such functionality in JavaScript Blockchain Oracles.

This is part of our team work to participate in LiquidApps Global Hackathon 2019.

## Installation

+ **OS X** (XCode & Command Line Tools)
+ **Linux** (GCC >= 4.8):

```bash
$ npm install riskjs
```

+ **Windows7/8** (Visual Studio 2012):

```bash
$ npm install riskjs --msvs_version=2012
```

## Testing

There is a small but important suite of tests to check that this code runs correctly.

```bash
$ npm run test

> riskjs@0.0.5 test ./vigorish/riskjs
> mocha test/*.js

Loading data from "./test/data.csv"
Loading data from "./test/data.csv"
Loading data from "./test/data.csv"


  CVaR Historical
    ✓ RiskJS.CVaRHistorical() should be a function
    ✓ Should throw error when tried with wrong arguments
    ✓ Should return a string with the same result value

  CVaR Monte Carlo
    ✓ RiskJS.CVaRMonteCarlo() should be a function
    ✓ Should throw error when tried with wrong arguments (111ms)
    ✓ Should return a string with the same result value (99ms)

  CVaR Variance Covariance
    ✓ RiskJS.CVaRVarianceCovariance() should be a function
    ✓ Should throw error when tried with wrong arguments
    ✓ Should return a string with the same result value


  9 passing (221ms)
```

#### Dependencies

Included in the project are both dependencies to build this library, please check `include` folder.
