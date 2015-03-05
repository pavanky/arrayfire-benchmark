/*
 * matrix_multiply.cpp
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

BASELINE_F(MedianFilter, Baseline, Fixture_2D_f32, samples, operations) { }


BENCHMARK_F(MedianFilter, MedianFilter_f32_4x4_PAD_ZERO, Fixture_2D_f32, samples, operations)
{
	array B = medfilt(A, 4, 4, af_pad_type::AF_ZERO);
	B.eval();
	af::sync();
}

BENCHMARK_F(MedianFilter, MedianFilter_f32_4x4_PAD_SYMMETRIC, Fixture_2D_f32, samples, operations)
{
	array B = medfilt(A, 4, 4, af_pad_type::AF_SYMMETRIC);
	B.eval();
	af::sync();
}

BENCHMARK_F(MedianFilter, MedianFilter_f64_4x4_PAD_ZERO, Fixture_2D_f64, samples, operations)
{
	array B = medfilt(A, 4, 4, af_pad_type::AF_ZERO);
	B.eval();
	af::sync();
}

BENCHMARK_F(MedianFilter, MedianFilter_f64_4x4_PAD_SYMMETRIC, Fixture_2D_f64, samples, operations)
{
	array B = medfilt(A, 4, 4, af_pad_type::AF_SYMMETRIC);
	B.eval();
	af::sync();
}
