/*
 * jit.cpp
 *
 *  Created on: March 4, 2015
 *      Author: bkloppenborg
 */

#include <celero/Celero.h>
#include <arrayfire.h>
using namespace af;

extern unsigned int samples;
extern unsigned int operations;

class AF_GFOR_Fixture : public celero::TestFixture
{
public:
    af_dtype data_type;
    array input_cube;
    array output;

    AF_GFOR_Fixture() { this->data_type = af_dtype::f32; }

    virtual std::vector<int64_t> getExperimentValues() const
    {
        std::vector<int64_t> problemSpace;
        // 32 - 256 elements (2^5 - 2^8)
        for(int i = 5; i <= 8; i++)
            problemSpace.push_back(pow(2, i));

        return problemSpace;

    }

    /// Before each run, build a vector of random integers.
    virtual void setUp(int64_t experimentSize)
    {
        try
        {
            int depth = 1000;
            input_cube = constant(1.0, experimentSize, experimentSize, depth, this->data_type);
            input_cube.eval();
            output = array(depth, this->data_type);
            output.eval();
            af::sync();
        }
        catch (af::exception & e)
        {
            // print out the error, rethrow the error to cause the test to fail.
            std::cout << e << std::endl;
            throw e;
        }
    }

};

// do-nothing baseline measurement
BASELINE_F( GFOR, Baseline, AF_GFOR_Fixture, samples,  operations) {}


// Benchmark without using gfor:
BENCHMARK_F( GFOR , GFOR_NO_LOOP_SUM , AF_GFOR_Fixture , 1, 1) //samples, operations)
{
    output = sum(sum(input_cube));

    output.eval();
    af::sync();
}

// Benchmark without using gfor:
BENCHMARK_F( GFOR , GFOR_FOR_LOOP_SUM , AF_GFOR_Fixture , 1, 1) //samples, operations)
{
    for(int i = 0; i < input_cube.dims(2); i++)
    {
        output(i) = sum(sum(input_cube(span, span, i)));
    }

    output.eval();
    af::sync();
}


// Benchmark using gfor:
BENCHMARK_F( GFOR , GFOR_SUM , AF_GFOR_Fixture , 1, 1) //samples, operations)
{
    gfor(seq ii, input_cube.dims(2))
    {
        output(ii) = sum(sum(input_cube(span, span, ii)));
    }

    output.eval();
    af::sync();
}
