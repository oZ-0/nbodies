#include <fstream>
#include <stack>
#include "simulation.hpp"
using namespace std;
double m = 1.0;


int main(int argc, const char **argv) {
  Simulation sim(0.01);
  sim.run(5000);
  return 0;
}