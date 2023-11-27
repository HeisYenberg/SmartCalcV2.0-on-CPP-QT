# SmartCalcV2.0-on-CPP-QT

## Implementation of SmartCalc.

## Usage :

- To install the app run `make install`
- To open app run `make open`
- To see tests run `make test`, might need to install `gtest`
- To see tests code coverage run `make gcov_report`, might need to install `lcov`

### Overview of "SmartCalc" functions

| Operator name  | Arithmetic operators | Function description       | Functions |
|----------------|----------------------|----------------------------|-----------|
| Brackets       | (a + b)              | Computes cosine            | cos(x)    |
| Addition       | a + b                | Computes sine              | sin(x)    |
| Subtraction    | a - b                | Computes tangent           | tan(x)    |
| Multiplication | a * b                | Computes arc cosine        | acos(x)   |
| Division       | a / b                | Computes arc sine          | asin(x)   |
| Power          | a ^ b                | Computes arc tangent       | atan(x)   |
| Modulus        | a mod b              | Computes square root       | sqrt(x)   |
| Unary plus     | +a                   | Computes natural logarithm | ln(x)     |
| Unary minus    | -a                   | Computes common logarithm  | log(x)    |

Graph of function:

- Builds a graph of a provided function.

Credit calculator:

- Input: total credit amount, term, interest rate, type (annuity, differentiated)
- Output: monthly payment, overpayment on credit, total payment

Deposit calculator:

- Input: deposit amount, deposit term, interest rate, tax rate, periodicity of payments, capitalization of interest,
  replenishments list, partial withdrawals list
- Output: accrued interest, tax amount, deposit amount by the end of the term