#ifndef LINEARELASTICITY_HPP
#define LINEARELASTICITY_HPP
#include "TrialFunction.hpp"
#include "TestFunctionGalerkin.hpp"
#include "Form.hpp"
#include "TrialFunctionNeumannSurface.hpp"
#include "TrialFunctionNeumannLine.hpp"
#include "LocalIntegration.hpp"
#include "PreDefinedElasticityTensor.hpp"
namespace PreDefinedModels
{
class LinearElastic: public LocalIntegrator<TrialFunction>
{
public:
    LinearElastic(Form<TrialFunction>& a, TrialFunction& u, TestFunctionGalerkin<TrialFunction>& v, sp_mat& C):
        C_Internal(C),
        LocalIntegrator (a,u,v)
    {
    }
    sp_mat weak_form(Form<TrialFunction>& a, TrialFunction& u, TestFunctionGalerkin<TrialFunction>& v)
    {
        return a.inner(a.sym_grad(v),C_Internal*a.sym_grad(u))*a.dX(u);
    }
private:
    double E_Internal, nu_Internal;
    sp_mat& C_Internal;
};

class LinearElastic_BodyForce: public LocalIntegrator<TrialFunction>
{
public:
    LinearElastic_BodyForce(Form<TrialFunction>& a, TrialFunction& u, TestFunctionGalerkin<TrialFunction>& v, vec& BodyForce):
        BodyForce_Internal(BodyForce),
        LocalIntegrator (a,u,v)
    {
    }
    mat weak_form_vector(Form<TrialFunction>& a, TrialFunction& u, TestFunctionGalerkin<TrialFunction>& v)
    {
        return a.dot(v,BodyForce_Internal)*a.dX(u);
    }
private:
    vec &BodyForce_Internal;
};

class LinearElastic_TractionArea: public LocalIntegrator <TrialFunctionNeumannSurface>
{
public:
    LinearElastic_TractionArea(Form<TrialFunctionNeumannSurface>& a, TrialFunctionNeumannSurface& u,
                            TestFunctionGalerkin<TrialFunctionNeumannSurface>& v, vec& TractionForce):
        TractionForce_Internal(TractionForce),
        LocalIntegrator (a,u,v)
    {
    }

    mat weak_form_vector(Form<TrialFunctionNeumannSurface>& a, TrialFunctionNeumannSurface& u,
                         TestFunctionGalerkin<TrialFunctionNeumannSurface>& v)
    {
        return a.dot(v,TractionForce_Internal)*a.dS(u);
    }
private:
vec& TractionForce_Internal;
};


class LinearElastic_TractionLine: public LocalIntegrator<TrialFunctionNeumannLine>
{
public:
    LinearElastic_TractionLine(Form<TrialFunctionNeumannLine>& a, TrialFunctionNeumannLine& u,
                            TestFunctionGalerkin<TrialFunctionNeumannLine>& v,  vec& TractionForce):
        TractionForce_Internal(TractionForce),
        LocalIntegrator (a,u,v)
    {
    }
    mat weak_form_vector(Form<TrialFunctionNeumannLine>& a, TrialFunctionNeumannLine& u,
                     TestFunctionGalerkin<TrialFunctionNeumannLine>& v)
    {
        return a.dot(v,TractionForce_Internal)*a.dL(u);
    }
private:
vec& TractionForce_Internal;
};
}
#endif // LINEARELASTICITY_HPP
