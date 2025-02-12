#ifndef SCALARFUNCTION_SCALE_JG
#define SCALARFUNCTION_SCALE_JG
/**
 * Pure virtual base class ScalarFunction
 */
class ScalarFunction{
    public:
    
    virtual double operator()(double x) const = 0;
};

#endif