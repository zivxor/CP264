/**
 * -------------------------------------
 * @file  mymortgage_ptest.c
 * @brief  Public test driver
 * -------------------------------------
 * @author HBF
 * @version 2026-01-09
 * -------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "mymortgage.h"

#define EPSILON 1e-6 //#define EPSILON 0.000001

static const float bases[] = {1e-1f, 1.5f, 2.0f, 5.0f};
static const int exps[] = {1, 2, 10, 100};
static const float principal_tests[] = {1000.0, 10000.0, 200000.0};
static const float rate_tests[] = {1.0, 3.0, 5.0};
static const int years_tests[] = {1, 10, 20};


void test_mypowf(void) {
    printf("------------------\n");
    printf("Test: mypowf\n\n");
    int bcount = sizeof bases / sizeof *bases;
    int ecount = sizeof exps / sizeof *exps;
    for (int i = 0; i < bcount; i++) {
        for (int j = 0; j < ecount; j++) {
            float b = bases[i];
            int n = exps[j];
            printf("mypowf(%.2f,%d) = %.6g\n", b, n, mypowf(b, n));
        }
        printf("\n");
    }
}

void test_monthly_payment(void) {
    printf("------------------\n");
    printf("Test: monthly_payment(principle,rate,years)\n\n");

    int count = sizeof principal_tests / sizeof *principal_tests;
    for(int i = 0; i < count; i++) {
        float principal = principal_tests[i] ;
        float rate = rate_tests[i];
        int years = years_tests[i];
        printf("monthly_payment(%.2f,%.2f,%d): %.2f\n", principal, rate, years, monthly_payment(principal, rate, years));
    }
    printf("\n");
}

void test_total_payment(void) {
    printf("------------------\n");
    printf("Test: total_payment(principle,rate,years)\n\n");
    int count = sizeof principal_tests / sizeof *principal_tests;

    for(int i = 0; i < count; i++) {
        float principal = principal_tests[i] ;
        float rate = rate_tests[i];
        int years = years_tests[i];
        printf("total_payment(%.2f,%.2f,%d): %.2f\n", principal, rate, years, total_payment(principal, rate, years));
    }
    printf("\n");
}  

void test_total_interest(void) {
    printf("------------------\n");
    printf("Test: total_interest(principle,rate,years)\n\n");

        int count = sizeof principal_tests / sizeof *principal_tests;

    for(int i = 0; i < count; i++) {
        float principal = principal_tests[i] ;
        float rate = rate_tests[i];
        int years = years_tests[i];
        printf("total_interest(%.2f,%.2f,%d): %.2f\n", principal, rate, years, total_interest(principal, rate, years));
    }
    printf("\n");
}


void test(float a, float b, int c) {
   printf("principle:%.2f\nannual interest rate:%.2f%%\nyears:%d\n", a, b, c);
   printf("monthly payment:%.2f\n",   monthly_payment(a,b,c));
   printf("total payment:%.2f\n",   total_payment(a,b,c));
   printf("total interest:%.2f\n",   total_interest(a,b,c));
}

int main(int argc, char* argv[])
{
	if (argc <= 1) {
        test_mypowf();        	
        test_monthly_payment();
        test_total_payment();
        test_total_interest();
	} else {
		float a, b;
		int c;
		int n = sscanf(argv[1], "%f,%f,%d", &a, &b, &c); 
		if (n == 3 && a > EPSILON && b > EPSILON && c > 0) { 
		   test(a, b, c);
		}
		else {
			printf("invalid command argument format\n");	
			printf("argument format:principle,rate(%%),years, e.g., 1000.0,5.0,1\n");	 
		}
	}
	printf("\n");
	return 0;
}
