#include "pch.h"

/*
eg1
Max
  z = 10x1 + 6x2;
Sub
  x1+x2<=200
  x1+2x2>=10
  3x1+x2<=275.5
  x1>=0
  x2>=0
*/

int main(int argc, char** argv)
{
    std::cout << glp_version() << std::endl;

    glp_prob *lp = nullptr;
    lp = glp_create_prob();

    if(lp!=nullptr)
    {
        glp_set_obj_dir(lp, GLP_MAX);

        glp_add_rows(lp, 3);
        glp_set_row_name(lp, 1, "p");
        glp_set_row_bnds(lp, 1, GLP_DB, 0.0, 200.0);
        glp_set_row_name(lp, 2, "q");
        glp_set_row_bnds(lp, 2, GLP_LO, 10.0, 0.0);
        glp_set_row_name(lp, 3, "r");
        glp_set_row_bnds(lp, 3, GLP_DB, 0.0, 275.0);

        glp_add_cols(lp, 2);
        glp_set_col_name(lp, 1, "x1");
        glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0);
        glp_set_col_name(lp, 2, "x2");
        glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0);

        glp_set_obj_coef(lp, 1, 10.0);
        glp_set_obj_coef(lp, 2, 6.0);

        int ia[7], ja[7];
        double ar[7];
        ia[1] = 1, ja[1] = 1, ar[1] = 1;
        ia[2] = 1, ja[2] = 2, ar[2] = 1;
        ia[3] = 2, ja[3] = 1, ar[3] = 1;
        ia[4] = 2, ja[4] = 2, ar[4] = 2;
        ia[5] = 3, ja[5] = 1, ar[5] = 3;
        ia[6] = 3, ja[6] = 2, ar[6] = 1;
        glp_load_matrix(lp, 6, ia, ja, ar);

        glp_simplex(lp, NULL);

        double z, x1, x2;
        z = glp_get_obj_val(lp);
        x1 = glp_get_col_prim(lp, 1);
        x2 = glp_get_col_prim(lp, 2);
        printf("z = %lf, x1 = %lf, x2 = %lf\n", z, x1, x2);

        glp_delete_prob(lp);
    }
    
    return 0;
}
