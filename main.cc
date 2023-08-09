#include "PlanInputs.hh"
#include "Plan.hh"

int main() {

  // Read the inputs
  PlanInputs inp("draft0.fcl");
  inp.print();

  // Build the model.
  Plan plan(inp);

  return 0;
}
