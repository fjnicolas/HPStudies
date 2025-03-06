#!/bin/sh
# Compile QE analysis
cd ${G4WORKDIR}/AnaQE
g++ -o ${G4WORKDIR}/build/CreateMCXSec_QE CreateMCXSec_QE.C `root-config --cflags --glibs` -I${G4WORKDIR}/include  -L${G4WORKDIR}/build -lg4hpDict
g++ -o ${G4WORKDIR}/build/QElEvents QElEvents.C `root-config --cflags --glibs` -I${G4WORKDIR}/include  -L${G4WORKDIR}/build -lg4hpDict
cd ${G4WORKDIR}

# Compile ana analysis
cd ${G4WORKDIR}/ana
g++ -o ${G4WORKDIR}/build/CreateInvXS CreateInvXS.C `root-config --cflags --glibs` -I${G4WORKDIR}/include  -L${G4WORKDIR}/build -lg4hpDict
g++ -o ${G4WORKDIR}/build/CreateMult CreateMult.C `root-config --cflags --glibs` -I${G4WORKDIR}/include  -L${G4WORKDIR}/build -lg4hpDict
g++ -o ${G4WORKDIR}/build/CreateYields CreateYields.C `root-config --cflags --glibs` -I${G4WORKDIR}/include  -L${G4WORKDIR}/build -lg4hpDict
cd ${G4WORKDIR}

# Compile AnaHARP
cd ${G4WORKDIR}/AnaHARP
g++ -o ${G4WORKDIR}/build/CreateMCXSec CreateMCXSec.C `root-config --cflags --glibs` -I${G4WORKDIR}/include  -L${G4WORKDIR}/build -lg4hpDict
g++ -o ${G4WORKDIR}/build/CreateMCFInv CreateMCFInv.C `root-config --cflags --glibs` -I${G4WORKDIR}/include  -L${G4WORKDIR}/build -lg4hpDict
cd ${G4WORKDIR}
