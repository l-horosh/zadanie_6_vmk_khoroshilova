#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

const double EPS = 0.001;
static int counter = 0;
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
        counter += 1;
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

// double integral1 (double a, double b, double (* f) (double x)) {
//     if (a == b) {
//         return 0;
//     }
//     double delta_x = fabs(b-a)/(b-a)*EPS/1000;
//     double I = 0;
//     int count = (int) ((b-a)/delta_x) + 1;
//     for (int i = 0; i <= count+1; i++) {
//         I += delta_x * f(a);
//         a += delta_x;
//     }
//     return I;
// }

double integral (double (* f)(double x), double a, double b, double eps2) {
    if (a > b) {
        a += b;
        b = a - b;
        a -= b;
    }
    double integral_sum_n;
    double integral_sum_2n = 0;
    double step = b - a;

    do {
        integral_sum_n = integral_sum_2n;
        integral_sum_2n = 0;
        for (double i = a; i < b; i += step) {
            integral_sum_2n = integral_sum_2n + f(i + step / 2) * step;
        }
        step = step / 2;
    } while (integral_sum_2n - integral_sum_n > eps2);
    return integral_sum_2n;
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

int test_integral (double (*integral) (double (* f) (double x), double a, double b, double eps2)) {
    printf ("-------Testing integral------\n");
    int test_errors = 0;
    //--------------------------------------TESTS---------------------------------------------
    if (abs(integral (f2, 0, 1, EPS) - 0.25) < EPS) {
        printf("Test_1 passed OK\n");
    }
    else {
        printf("Test_1 ERROR. returned = %f, answer = %f\n", integral (f2, 0, 1, EPS), 0.25);
        test_errors += 1;
    }
    //-----------------------------------------------------------------------------------
    if (abs(integral (f3, -2, 5, EPS) - 5.7257) < EPS) {
        printf("Test_2 passed OK\n");
    }
    else {
        printf("Test_2 ERROR. returned = %f, answer = %f\n", integral (f3, -2, 5, EPS), 5.7257);
        test_errors += 1;
    }
    //-----------------------------------------------------------------------------------
    if (abs(integral(f1, 3, 10, EPS) - 7.88833) < EPS) {
        printf("Test_3 passed OK\n");
    }
    else {
        printf("Test_3 ERROR. returned = %f, answer = %f\n", integral (f1, 3, 10, EPS), 7.88833);
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
    S += integral (f1, x1, x2, EPS);
    S += integral (f3, x2, x3, EPS);
    S += integral (f2, x3, x1, EPS);

    // double S1 = 0;
    // S1 += integral1 (x1, x2, f1);
    // S1 += integral1 (x1, x2, f3);
    // S1 += integral1 (x1, x2, f2);

    return fabs(S);
}

void testik (int n) {
    if (n == 1) {
        //----------------------------------TESTS-------------------------------------------------
        if (abs(root(f2, f3, -100, 100, EPS) - 0.826218) < EPS) {
            printf("Test_1 root passed OK\n");
        }
        else {
            printf("Test_1 root ERROR. returned = %f, answer = %f\n", root (f2, f3, -100, 100, EPS), 0.826218);
        }
        //----------------------------------------------------------------------------------- 
    }
    if (n == 2) {
        //-----------------------------------------------------------------------------------   
        if (abs(root(f3, f1, -100, 100, EPS) + 1.3079) < EPS) {
            printf("Test_2 root passed OK\n");
        }
        else {
            printf("Test_2 root ERROR. returned = %f, answer = %f\n", root (f3, f1, -100, 100, EPS), -1.3079);
        }
        //-----------------------------------------------------------------------------------
    }
    if (n == 3) {
        //-----------------------------------------------------------------------------------
        if (abs(root(f2, f1, -100, 100, EPS) - 1.344) < EPS) {
            printf("Test_3 root passed OK\n");
        }
        else {
            printf("Test_3 root ERROR. returned = %f, answer = %f\n", root (f2, f1, -100, 100, EPS), 1.344);
        }
        //--------------------------------END_TESTS---------------------------------------------------
    }
    if (n == 4) {
        //--------------------------------------TESTS---------------------------------------------
        if (abs(integral (f2, 0, 1, EPS) - 0.25) < EPS) {
            printf("Test_4 passed OK\n");
        }
        else {
            printf("Test_4 ERROR. returned = %f, answer = %f\n", integral (f2, 0, 1, EPS), 0.25);
        }
        //-----------------------------------------------------------------------------------
    }
    if (n == 5) {
        //-----------------------------------------------------------------------------------
        if (abs(integral (f3, -2, 5, EPS) - 5.7257) < EPS) {
            printf("Test_5 passed OK\n");
        }
        else {
            printf("Test_5 ERROR. returned = %f, answer = %f\n", integral (f3, -2, 5, EPS), 5.7257);
        }
        //-----------------------------------------------------------------------------------
    }
    if (n == 6) {
        //-----------------------------------------------------------------------------------
        if (abs(integral(f1, 3, 10, EPS) - 7.88833) < EPS) {
            printf("Test_6 passed OK\n");
        }
        else {
            printf("Test_6 ERROR. returned = %f, answer = %f\n", integral (f1, 3, 10, EPS), 7.88833);
        }
        //-----------------------------------END_TESTS------------------------------------------------
    }
}

int main(int argc, char *argv[])
{
    int help = 0;
    int tochki = 0;
    int iteratsii = 0;
    int flagTest = 0;
    int n = 0;
    unsigned int numberOfTests = 6;
    if (argc >= 2) {
        for (int i = 1; i < argc; i++) {
            if (strcmp(argv[i], "-help") == 0) {
                help = 1;
            }
            else if (strcmp(argv[i], "-iteratsii") == 0) {
                iteratsii = 1;
            }
            else if (strcmp(argv[i], "-tochki") == 0) {
                tochki = 1;
            }
            else if (strcmp(argv[i], "-test") == 0) {
                flagTest = 1;
                if (i + 1 >= argc) {
                    printf("Incorrect flag\n");
                    return 1;
                }
                for (int j = 0; j < strlen(argv[i + 1]); j++) {
                    if ('0' > argv[i + 1][j] || argv[i + 1][j] > '9') {
                        printf("Incorrect number\n");
                        return 1;
                    }
                }
                n = atoi(argv[i + 1]); // номер теста
                if (n > numberOfTests || n <= 0) {
                    printf("Incorrect number\n");
                    return 1;
                }
                i++;
            }
            else {
                printf("Error: Undefined flag\n");
                return 1;
            }
        }
    }
    
    // подсчёт итераций
    static int counter = 0;
    unsigned int counter12 = 0, counter13 = 0, counter23 = 0;
    double f1f2 = root(f1, f2, -100, 100, EPS);
    counter12= counter;
    counter = 0;
    double f1f3 = root(f1, f3, -100, 100, EPS);
    counter13 = counter;
    counter = 0;
    double f2f3 = root(f2, f3, -100, 100, EPS);
    counter23 = counter;
    counter = 0;
    if (iteratsii) {
        printf("%d - iteratsii ot f1(x) = f2(x)", counter12);
        printf("%d - iteratsii ot f2(x) = f3(x)", counter23);
        printf("%d - iteratsii ot f1(x) = f3(x)", counter13);
    }
    if (tochki) {
        printf("f1(x) = f2(x) <=> x = %lf, znachenie funktsii = %lf\n", f1f2, f1(f1f2));
        printf("f1(x) = f3(x) <=> x = %lf, znachenie funktsii = %lf\n", f1f3, f1(f1f3));
        printf("f2(x) = f3(x) <=> x = %lf, znachenie funktsii = %lf\n", f2f3, f2(f2f3));
    }
    if (help) {
        printf("-help             - print this message\n");
        printf("-iteratsii        - print info about iterations\n");
        printf("-tochki           - print info about point\n");
        printf("-test Number      - test function\n");
    }
    if (flagTest) {
        testik(n);
    }
    if (help + tochki + iteratsii + flagTest == 0) {
        double x = 100;
        // printf ("f = %lg\n", f1 (100.0));
        printf ("f = %lg\n", f3 (5.0));
        // printf ("f = %lg\n", f1 (100.0));
        //printf("%f %f %f", f1(x), f2(x), f3(x));
        // printf("root 1 = %f \n", root(f1, f2));
        // printf("integral = %f \n", integral (0, 1, f1));
        // printf ("Square = %f\n", square_of_figure(f1, f2, f3));
        //test_root (root);
        //test_integral(integral);
        printf ("Square = %lg\n", square_of_figure (f1, f2, f3));
    }
    return 0;
}