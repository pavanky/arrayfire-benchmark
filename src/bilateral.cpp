/*
 * bilateral.cpp
 *
 *  Created on: Nov 7, 2014
 *      Author: bkloppenborg
 */

#include <celero/Celero.h>
#include <arrayfire.h>
#include "fixtures.h"
using namespace af;

extern unsigned int samples;
extern unsigned int operations;

BASELINE_F(BilateralFilter, Baseline, Fixture_2D_f32, samples, operations){}

BENCHMARK_F(BilateralFilter, BilateralFilter_f32, Fixture_2D_f32, samples, operations)
{
    array B = bilateral(this->A, 2.5f, 50.0f);
    B.eval();
}

BENCHMARK_F(BilateralFilter, BilateralFilter_f64, Fixture_2D_f64, samples, operations)
{
    array B = bilateral(this->A, 2.5f, 50.0f);
    B.eval();
}
