#!/bin/sh
cd ${G4WORKDIR}/AnaQE
g++ -o CreateMCXSec_QE CreateMCXSec_QE.C `root-config --cflags --glibs` -I${G4WORKDIR}/include  -L${G4WORKDIR}/build -lg4hpDict
g++ -o QElEvents QElEvents.C `root-config --cflags --glibs` -I${G4WORKDIR}/include  -L${G4WORKDIR}/build -lg4hpDict