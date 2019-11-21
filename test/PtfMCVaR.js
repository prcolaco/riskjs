const
    RiskJS = require('../index.js'),
    should = require('should'),
    fs = require('fs'),
    csv = require('csv-parse/lib/sync');

const source = './test/data.csv';

// Load data from csv file
console.log('Loading data from "%s"', source);
const data = csv(fs.readFileSync(source, 'utf8'), {
  skip_empty_lines: true
});
// console.log(data);

describe('Portfolio Monte Carlo VaR', () => {
  var value;

  it('RiskJS.portfolioMonteCarloVaR() should be a function', () => {
    RiskJS.portfolioMonteCarloVaR.should.be.a.Function;
  });

  it('Should throw error when tried with wrong arguments', () => {
    (() => RiskJS.portfolioMonteCarloVaR()).should.throw('needs one argument with the price data array');
    (() => RiskJS.portfolioMonteCarloVaR(0)).should.throw('needs one argument with the price data array');
    (() => value = RiskJS.portfolioMonteCarloVaR(data)).should.not.throw();
  });

  it('Should return a string with the same result value', () => {
    const res = RiskJS.portfolioMonteCarloVaR(data);
    res.should.be.a.String;
    res.should.equal(value);
    // console.log('Portfolio Monte Carlo VaR = %s', res);
  });
});
