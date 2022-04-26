#include <stdio.h>
#include <stdlib.h>
#include <math.h>

const double EPS = 0.001;

extern double f1 (double x);
extern double f2 (double x);
extern double f3 (double x);

// double f2 (double x) {
//     return x*x*x;
// }

// double f3 (double x) {
//     return pow(2, -x);
// }

// double f1 (double x) {
//     return 1 + 4/(x*x + 1);
// }



double root (double (* f1) (double x), double (* f2) (double x), double x_left, double x_right, double eps) {
    while (x_right - x_left >= eps/2) {
        // printf ("Debug left = %lg, right = %lg, ", x_left, x_right);
        // printf ("\n f2(x_left = %lg\n", f2 (2));
        double val_left = f2(x_left) - f1(x_left);
        double val_right = f2(x_right) - f1(x_right);
        double x_center = (x_left + x_right)/2;
        double val_center = f2(x_center) - f1(x_center);
        // printf ("val_l = %lf, val_c = %lf, val_r = %lf\n", val_left, val_center, val_right);
        if (val_center * val_right > 0) {
            x_right = x_center;
        }
        else {
            x_left = x_center;
        }
    }
    return x_right;
}

double integral (double a, double b, double (* f) (double x)) {
    if (a == b) {
        return 0;
    }
    double delta_x = fabs(b-a)/(b-a)*EPS/1000;
    double I = 0;
    int count = (int) ((b-a)/delta_x) + 1;
    for (int i = 0; i <= count+1; i++) {
        I += delta_x * f(a);
        a += delta_x;
    }
    return I;
}
//addkbabs

int test_root (double (* root) (double (* f1) (double x), double (* f2) (double x), double x_left, double x_right, double eps)) {
    int test_errors = 0;
    printf ("-------Testing root------\n");
    //----------------------------------TESTS-------------------------------------------------
    if (abs(root(f2, f3, -100, 100, EPS) - 0.826218) < EPS) {
        printf("Test_1 root passed OK\n");
    }
    else {
        printf("Test_1 root ERROR. returned = %f, answer = %f\n", root (f2, f3, -100, 100, EPS), 0.826218);
        test_errors += 1;
    }
    //-----------------------------------------------------------------------------------   
    if (abs(root(f3, f1, -100, 100, EPS) + 1.3079) < EPS) {
        printf("Test_2 root passed OK\n");
    }
    else {
        printf("Test_2 root ERROR. returned = %f, answer = %f\n", root (f3, f1, -100, 100, EPS), -1.3079);
        test_errors += 1;
    }
    //-----------------------------------------------------------------------------------
    if (abs(root(f2, f1, -100, 100, EPS) - 1.344) < EPS) {
        printf("Test_3 root passed OK\n");
    }
    else {
        printf("Test_3 root ERROR. returned = %f, answer = %f\n", root (f2, f1, -100, 100, EPS), 1.344);
        test_errors += 1;
    }
    //--------------------------------END_TESTS---------------------------------------------------
    printf ("Total errors count in function root = %d\n", test_errors);
}

int test_integral (double (*integral) (double a, double b, double (* f) (double x))) {
    printf ("-------Testing integral------\n");
    int test_errors = 0;
    //--------------------------------------TESTS---------------------------------------------
    if (abs(integral(0, 1, f2) - 0.25) < EPS) {
        printf("Test_1 passed OK\n");
    }
    else {
        printf("Test_1 ERROR. returned = %f, answer = %f\n", integral(0, 1, f2), 0.25);
        test_errors += 1;
    }
    //-----------------------------------------------------------------------------------
    if (abs(integral(-2, 5, f3) - 5.7257) < EPS) {
        printf("Test_2 passed OK\n");
    }
    else {
        printf("Test_2 ERROR. returned = %f, answer = %f\n", integral(-2, 5, f3), 5.7257);
        test_errors += 1;
    }
    //-----------------------------------------------------------------------------------
    if (abs(integral(3, 10, f1) - 7.88833) < EPS) {
        printf("Test_3 passed OK\n");
    }
    else {
        printf("Test_3 ERROR. returned = %f, answer = %f\n", integral(3, 10, f1), 7.88833);
        test_errors += 1;
    }
    //-----------------------------------END_TESTS------------------------------------------------
    printf ("Total errors count in function integral = %d\n", test_errors);
    
}

double square_of_figure (double (* f1) (double x), double (* f2) (double x), double (* f3) (double x)) {
    double S = 0;
    double x1 = root (f1, f2, -100, 100, EPS);
    double x2 = root (f1, f3, -100, 100, EPS);
    double x3 = root (f2, f3, -100, 100, EPS);
    S += integral (x1, x2, f1);
    S += integral (x2, x3, f3);
    S += integral (x3, x1, f2);
    return fabs(S);
}


int main()
{
    double x = 100;
    // printf ("f = %lg\n", f1 (100.0));
    printf ("f = %lg\n", f3 (5.0));
    // printf ("f = %lg\n", f1 (100.0));
    //printf("%f %f %f", f1(x), f2(x), f3(x));
    // printf("root 1 = %f \n", root(f1, f2));
    // printf("integral = %f \n", integral (0, 1, f1));
    // printf ("Square = %f\n", square_of_figure(f1, f2, f3));
    test_root (root);
    test_integral(integral);
    printf ("Square = %lg\n", square_of_figure (f1, f2, f3));
    return 0;
}