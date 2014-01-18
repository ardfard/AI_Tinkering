#ifndef OBJECTIVEFUNCTION_H
#define OBJECTIVEFUNCTION_H
#include <armadillo>

typedef arma::vec Vector;
class ObjectiveFunction
{
public:
    ObjectiveFunction();
    virtual double call(Vector values) = 0;
};

#endif // OBJECTIVEFUNCTION_H
