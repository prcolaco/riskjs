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

describe('CVaR Monte Carlo', () => {
  var value;

  it('RiskJS.CVaRMonteCarlo() should be a function', () => {
    RiskJS.CVaRMonteCarlo.should.be.a.Function;
  });

  it('Should throw error when tried with wrong arguments', () => {
    (() => RiskJS.CVaRMonteCarlo()).should.throw('needs three arguments');
    (() => RiskJS.CVaRMonteCarlo(data, [0.5,0.5])).should.throw('needs three arguments');
    (() => value = RiskJS.CVaRMonteCarlo(data, [0.5,0.5], 0.95)).should.not.throw();
  });

  it('Should return a string with the same result value', () => {
    const res = RiskJS.CVaRMonteCarlo(data, [0.5,0.5], 0.95);
    res.should.be.a.String;
    res.should.equal(value);
    // console.log('CVaR Monte Carlo = %s', res);
  });
});
