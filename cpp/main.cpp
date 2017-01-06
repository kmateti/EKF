#include <iostream>

/*
Copyright (c) 2013 Daniel Stahlke

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <fstream>
#include <vector>
#include <map>
#include <limits>
#include <cmath>
#include <cstdio>
//#include <boost/tuple/tuple.hpp>
//#include <boost/foreach.hpp>

// Warn about use of deprecated functions.
#define GNUPLOT_DEPRECATE_WARN
#include "gnuplot-iostream.h"

#ifndef M_PI
#       define M_PI 3.14159265358979323846
#endif

// http://stackoverflow.com/a/1658429
#ifdef _WIN32
        #include <windows.h>
        inline void mysleep(unsigned millis) {
                ::Sleep(millis);
        }
#else
        #include <unistd.h>
        inline void mysleep(unsigned millis) {
                ::usleep(millis * 1000);
        }
#endif


void pause_if_needed() {
#ifdef _WIN32
        // For Windows, prompt for a keystroke before the Gnuplot object goes out of scope so that
        // the gnuplot window doesn't get closed.
        std::cout << "Press enter to exit." << std::endl;
        std::cin.get();
#endif
}


void demo_basic() {
        Gnuplot gp;
        // For debugging or manual editing of commands:
        //Gnuplot gp(std::fopen("plot.gnu"));
        // or
        //Gnuplot gp("tee plot.gnu | gnuplot -persist");

        std::vector<std::pair<double, double> > xy_pts_A;
        for(double x=-2; x<2; x+=0.01) {
                double y = x*x*x;
                xy_pts_A.push_back(std::make_pair(x, y));
        }

        std::vector<std::pair<double, double> > xy_pts_B;
        for(double alpha=0; alpha<1; alpha+=1.0/24.0) {
                double theta = alpha*2.0*3.14159;
                xy_pts_B.push_back(std::make_pair(cos(theta), sin(theta)));
        }

        gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
        gp << "plot '-' with lines title 'cubic', '-' with points title 'circle'\n";
        gp.send1d(xy_pts_A);
        gp.send1d(xy_pts_B);

        pause_if_needed();
}


int main (int argc, char** argv)
{

  std::cout << "Hello World!\n";

  demo_basic();
  return 0;
  
}
