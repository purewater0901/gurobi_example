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

        GRBLinExpr J = 0.0;
        J = -x1 + 3*x2 + 2*x3;
        model.setObjective(J, GRB_MINIMIZE);

        // add constraint
        model.addConstr(x1-x2>=0, "c1");
        GRBQuadExpr qc2 = 4*x1*x1 + 3*x2*x2 + x3*x3 - 2*sqrt(3)*x2*x3 - 16*x1 - 6*x2 + 2*sqrt(3)*x3 + 19;
        GRBLinExpr lc2 = x2+sqrt(3)*x3-1;
        model.addQConstr(qc2<=lc2*lc2, "c2");

        model.optimize();

        std::cout << x1.get(GRB_StringAttr_VarName) << " " << std::sqrt(x1.get(GRB_DoubleAttr_X)) << std::endl;
        std::cout << x2.get(GRB_StringAttr_VarName) << " " << std::sqrt(x2.get(GRB_DoubleAttr_X)) << std::endl;
        std::cout << x3.get(GRB_StringAttr_VarName) << " " << std::sqrt(x3.get(GRB_DoubleAttr_X)) << std::endl;

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