# RiskJS

The goal of this project is to port [Calvin456/VaR](https://github.com/calvin456/VaR) library into JavaScript for Value at Risk calculation.

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

> riskjs@0.0.1 test ./vigorish/riskjs
> mocha test/*.js

Loading data from "./test/data.csv"


  Portfolio Monte Carlo VaR
    ✓ RiskJS.portfolioMonteCarloVaR() should be a function
    ✓ Should throw error when tried with wrong arguments (103ms)
    ✓ Should return a string with the same result value (104ms)


  3 passing (213ms)


```

#### Dependencies

Included in the project are both dependencies to build this library, please check `include` folder.
