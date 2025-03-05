# Hadron Production Studies

## Setup

- Make sure to be in SL7 container
- source setup.sh
- Compile using usual CMake
    - mkdir build; cd build; cmake ..;
    - cd ..; make;


## Running the G4 simulation

- Executable is `g4hp`
- `./g4hp -h`

## Generating grid jobs
- `ProcessG4HP.py`: send grid jobs for a single configuration
- `ProcessG4HP_ENERGYSCAN.py`: send grid jobs for a single configuration, looping over different beam incident energies

## QE analysis
- They live in the `AnaQE/` directory
- To compile the programs in `AnaQE/`, somply run `compile_analysis_QE` (this is just an alias defined in the setup script)
- To make distribution of # events per final state category: run `QElEvents` macro
- To create differential cross section (as a function of four transfer momentum): run `CreateMCXSec_QE` macro
    - Run as `CreateMCXSec_QE [input_files_list] [output_ROOT_file] [incidentMomemtum]`, e.g.
    `CreateMCXSec_QE pBe_20GeV_FTFP.list DiffXSec_pBe_20GeV_FTFP.root 20`

## Plotting directory
- ROOT macros to make various plots in `plotting/` directory
