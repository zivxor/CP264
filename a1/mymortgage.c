#include <stdio.h>
#include "mymortgage.h"

static const float FLT_MAX_VALUE = 3.402823466e38f;
static const float FLT_MIN_POS   = 1.175494351e-38f;

static float myfabs(float x) {
    return (x < 0.0f) ? -x : x;
}

float mypowf(float b, int n) {
    if (n == 0) return 1.0f;
    if (b == 0.0f) return 0.0f;

    float result = 1.0f;
    for (int i = 0; i < n; i++) {
        float ab = myfabs(b);
        float ar = myfabs(result);

        if (ab != 0.0f && ar > FLT_MAX_VALUE / ab) {
            return 0.0f;
        }

        result *= b;

        // Underflow check: non-zero but smaller than min positive normal
        if (result != 0.0f && myfabs(result) < FLT_MIN_POS) {
            return 0.0f;
        }
    }
    return result;
}

float monthly_payment(float principal_amount, float annual_interest_rate, int years) {
    int months = years * 12;
    float r = (annual_interest_rate / 100.0f) / 12.0f;

    if (myfabs(r) < 1.0e-8f) {
        return principal_amount / (float)months;
    }

    float one_plus_r = 1.0f + r;
    float pow_val = mypowf(one_plus_r, months);
    if (pow_val == 0.0f) {
        return 0.0f;
    }

    float denom = pow_val - 1.0f;
    if (myfabs(denom) < 1.0e-12f) {
        return 0.0f;
    }

    float payment = principal_amount * (r * pow_val) / denom;
    return payment;
}

float total_payment(float principal_amount, float annual_interest_rate, int years) {
    int months = years * 12;
    float m = monthly_payment(principal_amount, annual_interest_rate, years);
    return m * (float)months;
}

float total_interest(float principal_amount, float annual_interest_rate, int years) {
    float total = total_payment(principal_amount, annual_interest_rate, years);
    return total - principal_amount;
}
