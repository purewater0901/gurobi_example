#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <cmath>
#include <fstream>
#include "gurobi_c++.h"

int main()
{

    try
    {
        /* Create Environment */

        GRBEnv env = GRBEnv();
        GRBModel model = GRBModel(env);

        GRBVar x1 = model.addVar(-GRB_INFINITY, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "x1");
        GRBVar x2 = model.addVar(-GRB_INFINITY, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "x2");
        GRBVar x3 = model.addVar(-GRB_INFINITY, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "x3");
        GRBVar z1 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "z1");
        GRBVar z2 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "z2");
        GRBVar z3 = model.addVar(0.0, GRB_INFINITY, 0.0, GRB_CONTINUOUS, "z3");

        GRBLinExpr J = -x1 + 3*x2 + 2*x3;
        model.setObjective(J, GRB_MINIMIZE);

        // add constraint
        //model.addQConstr((2*x1-4)*(2*x1-4)+(sqrt(3)*x2-x3-sqrt(3))*(sqrt(3)*x2-x3-sqrt(3))<=z1*z1, "qc0");
        model.addQConstr(z1*z1+z2*z2<=z3*z3, "qc0");
        model.addConstr(x1-x2>=0, "c0");
        model.addConstr(2*x1-4==z1, "c1");
        model.addConstr(sqrt(3)*x2-x3-sqrt(3)==z2, "c2");
        model.addConstr(x2+sqrt(3)*x3-1==z3, "c3");

        model.optimize();

        std::cout << x1.get(GRB_StringAttr_VarName) << " " << x1.get(GRB_DoubleAttr_X) << std::endl;
        std::cout << x2.get(GRB_StringAttr_VarName) << " " << x2.get(GRB_DoubleAttr_X) << std::endl;
        std::cout << x3.get(GRB_StringAttr_VarName) << " " << x3.get(GRB_DoubleAttr_X) << std::endl;

    }
    catch(GRBException e)
    {
        std::cout << "Error code = " << e.getErrorCode() << std::endl;
        std::cout << e.getMessage() << std::endl;
    } catch(...)
    {
        std::cout << "Exception during optimization" << std::endl;
    }

    return 0;
}