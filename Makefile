# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /cvmfs/larsoft.opensciencegrid.org/products/cmake/v3_14_3/Linux64bit+3.10-2.17/bin/cmake

# The command to remove a file.
RM = /cvmfs/larsoft.opensciencegrid.org/products/cmake/v3_14_3/Linux64bit+3.10-2.17/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target install/strip
install/strip: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/cvmfs/larsoft.opensciencegrid.org/products/cmake/v3_14_3/Linux64bit+3.10-2.17/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip

# Special rule for the target install/strip
install/strip/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing the project stripped..."
	/cvmfs/larsoft.opensciencegrid.org/products/cmake/v3_14_3/Linux64bit+3.10-2.17/bin/cmake -DCMAKE_INSTALL_DO_STRIP=1 -P cmake_install.cmake
.PHONY : install/strip/fast

# Special rule for the target install/local
install/local: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/cvmfs/larsoft.opensciencegrid.org/products/cmake/v3_14_3/Linux64bit+3.10-2.17/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local

# Special rule for the target install/local
install/local/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Installing only the local directory..."
	/cvmfs/larsoft.opensciencegrid.org/products/cmake/v3_14_3/Linux64bit+3.10-2.17/bin/cmake -DCMAKE_INSTALL_LOCAL_ONLY=1 -P cmake_install.cmake
.PHONY : install/local/fast

# Special rule for the target install
install: preinstall
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/cvmfs/larsoft.opensciencegrid.org/products/cmake/v3_14_3/Linux64bit+3.10-2.17/bin/cmake -P cmake_install.cmake
.PHONY : install

# Special rule for the target install
install/fast: preinstall/fast
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Install the project..."
	/cvmfs/larsoft.opensciencegrid.org/products/cmake/v3_14_3/Linux64bit+3.10-2.17/bin/cmake -P cmake_install.cmake
.PHONY : install/fast

# Special rule for the target list_install_components
list_install_components:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Available install components are: \"Unspecified\""
.PHONY : list_install_components

# Special rule for the target list_install_components
list_install_components/fast: list_install_components

.PHONY : list_install_components/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/cvmfs/larsoft.opensciencegrid.org/products/cmake/v3_14_3/Linux64bit+3.10-2.17/bin/ccmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/cvmfs/larsoft.opensciencegrid.org/products/cmake/v3_14_3/Linux64bit+3.10-2.17/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies/CMakeFiles /exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /exp/sbnd/app/users/fnicolas/BNBFlux/HPStudies/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named g4hp

# Build rule for target.
g4hp: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 g4hp
.PHONY : g4hp

# fast build rule for target.
g4hp/fast:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/build
.PHONY : g4hp/fast

#=============================================================================
# Target rules for targets named g4hpDict

# Build rule for target.
g4hpDict: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 g4hpDict
.PHONY : g4hpDict

# fast build rule for target.
g4hpDict/fast:
	$(MAKE) -f CMakeFiles/g4hpDict.dir/build.make CMakeFiles/g4hpDict.dir/build
.PHONY : g4hpDict/fast

g4hp.o: g4hp.cc.o

.PHONY : g4hp.o

# target to build an object file
g4hp.cc.o:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/g4hp.cc.o
.PHONY : g4hp.cc.o

g4hp.i: g4hp.cc.i

.PHONY : g4hp.i

# target to preprocess a source file
g4hp.cc.i:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/g4hp.cc.i
.PHONY : g4hp.cc.i

g4hp.s: g4hp.cc.s

.PHONY : g4hp.s

# target to generate assembly for a file
g4hp.cc.s:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/g4hp.cc.s
.PHONY : g4hp.cc.s

g4hpCint.o: g4hpCint.cc.o

.PHONY : g4hpCint.o

# target to build an object file
g4hpCint.cc.o:
	$(MAKE) -f CMakeFiles/g4hpDict.dir/build.make CMakeFiles/g4hpDict.dir/g4hpCint.cc.o
.PHONY : g4hpCint.cc.o

g4hpCint.i: g4hpCint.cc.i

.PHONY : g4hpCint.i

# target to preprocess a source file
g4hpCint.cc.i:
	$(MAKE) -f CMakeFiles/g4hpDict.dir/build.make CMakeFiles/g4hpDict.dir/g4hpCint.cc.i
.PHONY : g4hpCint.cc.i

g4hpCint.s: g4hpCint.cc.s

.PHONY : g4hpCint.s

# target to generate assembly for a file
g4hpCint.cc.s:
	$(MAKE) -f CMakeFiles/g4hpDict.dir/build.make CMakeFiles/g4hpDict.dir/g4hpCint.cc.s
.PHONY : g4hpCint.cc.s

src/HPAnalysis.o: src/HPAnalysis.cc.o

.PHONY : src/HPAnalysis.o

# target to build an object file
src/HPAnalysis.cc.o:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPAnalysis.cc.o
.PHONY : src/HPAnalysis.cc.o

src/HPAnalysis.i: src/HPAnalysis.cc.i

.PHONY : src/HPAnalysis.i

# target to preprocess a source file
src/HPAnalysis.cc.i:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPAnalysis.cc.i
.PHONY : src/HPAnalysis.cc.i

src/HPAnalysis.s: src/HPAnalysis.cc.s

.PHONY : src/HPAnalysis.s

# target to generate assembly for a file
src/HPAnalysis.cc.s:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPAnalysis.cc.s
.PHONY : src/HPAnalysis.cc.s

src/HPConfig.o: src/HPConfig.cc.o

.PHONY : src/HPConfig.o

# target to build an object file
src/HPConfig.cc.o:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPConfig.cc.o
.PHONY : src/HPConfig.cc.o

src/HPConfig.i: src/HPConfig.cc.i

.PHONY : src/HPConfig.i

# target to preprocess a source file
src/HPConfig.cc.i:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPConfig.cc.i
.PHONY : src/HPConfig.cc.i

src/HPConfig.s: src/HPConfig.cc.s

.PHONY : src/HPConfig.s

# target to generate assembly for a file
src/HPConfig.cc.s:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPConfig.cc.s
.PHONY : src/HPConfig.cc.s

src/HPDetectorConstruction.o: src/HPDetectorConstruction.cc.o

.PHONY : src/HPDetectorConstruction.o

# target to build an object file
src/HPDetectorConstruction.cc.o:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPDetectorConstruction.cc.o
.PHONY : src/HPDetectorConstruction.cc.o

src/HPDetectorConstruction.i: src/HPDetectorConstruction.cc.i

.PHONY : src/HPDetectorConstruction.i

# target to preprocess a source file
src/HPDetectorConstruction.cc.i:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPDetectorConstruction.cc.i
.PHONY : src/HPDetectorConstruction.cc.i

src/HPDetectorConstruction.s: src/HPDetectorConstruction.cc.s

.PHONY : src/HPDetectorConstruction.s

# target to generate assembly for a file
src/HPDetectorConstruction.cc.s:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPDetectorConstruction.cc.s
.PHONY : src/HPDetectorConstruction.cc.s

src/HPEventAction.o: src/HPEventAction.cc.o

.PHONY : src/HPEventAction.o

# target to build an object file
src/HPEventAction.cc.o:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPEventAction.cc.o
.PHONY : src/HPEventAction.cc.o

src/HPEventAction.i: src/HPEventAction.cc.i

.PHONY : src/HPEventAction.i

# target to preprocess a source file
src/HPEventAction.cc.i:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPEventAction.cc.i
.PHONY : src/HPEventAction.cc.i

src/HPEventAction.s: src/HPEventAction.cc.s

.PHONY : src/HPEventAction.s

# target to generate assembly for a file
src/HPEventAction.cc.s:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPEventAction.cc.s
.PHONY : src/HPEventAction.cc.s

src/HPPrimaryGeneratorAction.o: src/HPPrimaryGeneratorAction.cc.o

.PHONY : src/HPPrimaryGeneratorAction.o

# target to build an object file
src/HPPrimaryGeneratorAction.cc.o:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPPrimaryGeneratorAction.cc.o
.PHONY : src/HPPrimaryGeneratorAction.cc.o

src/HPPrimaryGeneratorAction.i: src/HPPrimaryGeneratorAction.cc.i

.PHONY : src/HPPrimaryGeneratorAction.i

# target to preprocess a source file
src/HPPrimaryGeneratorAction.cc.i:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPPrimaryGeneratorAction.cc.i
.PHONY : src/HPPrimaryGeneratorAction.cc.i

src/HPPrimaryGeneratorAction.s: src/HPPrimaryGeneratorAction.cc.s

.PHONY : src/HPPrimaryGeneratorAction.s

# target to generate assembly for a file
src/HPPrimaryGeneratorAction.cc.s:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPPrimaryGeneratorAction.cc.s
.PHONY : src/HPPrimaryGeneratorAction.cc.s

src/HPRunAction.o: src/HPRunAction.cc.o

.PHONY : src/HPRunAction.o

# target to build an object file
src/HPRunAction.cc.o:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPRunAction.cc.o
.PHONY : src/HPRunAction.cc.o

src/HPRunAction.i: src/HPRunAction.cc.i

.PHONY : src/HPRunAction.i

# target to preprocess a source file
src/HPRunAction.cc.i:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPRunAction.cc.i
.PHONY : src/HPRunAction.cc.i

src/HPRunAction.s: src/HPRunAction.cc.s

.PHONY : src/HPRunAction.s

# target to generate assembly for a file
src/HPRunAction.cc.s:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPRunAction.cc.s
.PHONY : src/HPRunAction.cc.s

src/HPStackingAction.o: src/HPStackingAction.cc.o

.PHONY : src/HPStackingAction.o

# target to build an object file
src/HPStackingAction.cc.o:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPStackingAction.cc.o
.PHONY : src/HPStackingAction.cc.o

src/HPStackingAction.i: src/HPStackingAction.cc.i

.PHONY : src/HPStackingAction.i

# target to preprocess a source file
src/HPStackingAction.cc.i:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPStackingAction.cc.i
.PHONY : src/HPStackingAction.cc.i

src/HPStackingAction.s: src/HPStackingAction.cc.s

.PHONY : src/HPStackingAction.s

# target to generate assembly for a file
src/HPStackingAction.cc.s:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPStackingAction.cc.s
.PHONY : src/HPStackingAction.cc.s

src/HPTrackInfo.o: src/HPTrackInfo.cc.o

.PHONY : src/HPTrackInfo.o

# target to build an object file
src/HPTrackInfo.cc.o:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPTrackInfo.cc.o
.PHONY : src/HPTrackInfo.cc.o

src/HPTrackInfo.i: src/HPTrackInfo.cc.i

.PHONY : src/HPTrackInfo.i

# target to preprocess a source file
src/HPTrackInfo.cc.i:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPTrackInfo.cc.i
.PHONY : src/HPTrackInfo.cc.i

src/HPTrackInfo.s: src/HPTrackInfo.cc.s

.PHONY : src/HPTrackInfo.s

# target to generate assembly for a file
src/HPTrackInfo.cc.s:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPTrackInfo.cc.s
.PHONY : src/HPTrackInfo.cc.s

src/HPTrackingAction.o: src/HPTrackingAction.cc.o

.PHONY : src/HPTrackingAction.o

# target to build an object file
src/HPTrackingAction.cc.o:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPTrackingAction.cc.o
.PHONY : src/HPTrackingAction.cc.o

src/HPTrackingAction.i: src/HPTrackingAction.cc.i

.PHONY : src/HPTrackingAction.i

# target to preprocess a source file
src/HPTrackingAction.cc.i:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPTrackingAction.cc.i
.PHONY : src/HPTrackingAction.cc.i

src/HPTrackingAction.s: src/HPTrackingAction.cc.s

.PHONY : src/HPTrackingAction.s

# target to generate assembly for a file
src/HPTrackingAction.cc.s:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/HPTrackingAction.cc.s
.PHONY : src/HPTrackingAction.cc.s

src/TrackInfo_t.o: src/TrackInfo_t.cc.o

.PHONY : src/TrackInfo_t.o

# target to build an object file
src/TrackInfo_t.cc.o:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/TrackInfo_t.cc.o
	$(MAKE) -f CMakeFiles/g4hpDict.dir/build.make CMakeFiles/g4hpDict.dir/src/TrackInfo_t.cc.o
.PHONY : src/TrackInfo_t.cc.o

src/TrackInfo_t.i: src/TrackInfo_t.cc.i

.PHONY : src/TrackInfo_t.i

# target to preprocess a source file
src/TrackInfo_t.cc.i:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/TrackInfo_t.cc.i
	$(MAKE) -f CMakeFiles/g4hpDict.dir/build.make CMakeFiles/g4hpDict.dir/src/TrackInfo_t.cc.i
.PHONY : src/TrackInfo_t.cc.i

src/TrackInfo_t.s: src/TrackInfo_t.cc.s

.PHONY : src/TrackInfo_t.s

# target to generate assembly for a file
src/TrackInfo_t.cc.s:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/TrackInfo_t.cc.s
	$(MAKE) -f CMakeFiles/g4hpDict.dir/build.make CMakeFiles/g4hpDict.dir/src/TrackInfo_t.cc.s
.PHONY : src/TrackInfo_t.cc.s

src/hptuple.o: src/hptuple.cc.o

.PHONY : src/hptuple.o

# target to build an object file
src/hptuple.cc.o:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/hptuple.cc.o
	$(MAKE) -f CMakeFiles/g4hpDict.dir/build.make CMakeFiles/g4hpDict.dir/src/hptuple.cc.o
.PHONY : src/hptuple.cc.o

src/hptuple.i: src/hptuple.cc.i

.PHONY : src/hptuple.i

# target to preprocess a source file
src/hptuple.cc.i:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/hptuple.cc.i
	$(MAKE) -f CMakeFiles/g4hpDict.dir/build.make CMakeFiles/g4hpDict.dir/src/hptuple.cc.i
.PHONY : src/hptuple.cc.i

src/hptuple.s: src/hptuple.cc.s

.PHONY : src/hptuple.s

# target to generate assembly for a file
src/hptuple.cc.s:
	$(MAKE) -f CMakeFiles/g4hp.dir/build.make CMakeFiles/g4hp.dir/src/hptuple.cc.s
	$(MAKE) -f CMakeFiles/g4hpDict.dir/build.make CMakeFiles/g4hpDict.dir/src/hptuple.cc.s
.PHONY : src/hptuple.cc.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... install/strip"
	@echo "... install/local"
	@echo "... install"
	@echo "... list_install_components"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... g4hp"
	@echo "... g4hpDict"
	@echo "... g4hp.o"
	@echo "... g4hp.i"
	@echo "... g4hp.s"
	@echo "... g4hpCint.o"
	@echo "... g4hpCint.i"
	@echo "... g4hpCint.s"
	@echo "... src/HPAnalysis.o"
	@echo "... src/HPAnalysis.i"
	@echo "... src/HPAnalysis.s"
	@echo "... src/HPConfig.o"
	@echo "... src/HPConfig.i"
	@echo "... src/HPConfig.s"
	@echo "... src/HPDetectorConstruction.o"
	@echo "... src/HPDetectorConstruction.i"
	@echo "... src/HPDetectorConstruction.s"
	@echo "... src/HPEventAction.o"
	@echo "... src/HPEventAction.i"
	@echo "... src/HPEventAction.s"
	@echo "... src/HPPrimaryGeneratorAction.o"
	@echo "... src/HPPrimaryGeneratorAction.i"
	@echo "... src/HPPrimaryGeneratorAction.s"
	@echo "... src/HPRunAction.o"
	@echo "... src/HPRunAction.i"
	@echo "... src/HPRunAction.s"
	@echo "... src/HPStackingAction.o"
	@echo "... src/HPStackingAction.i"
	@echo "... src/HPStackingAction.s"
	@echo "... src/HPTrackInfo.o"
	@echo "... src/HPTrackInfo.i"
	@echo "... src/HPTrackInfo.s"
	@echo "... src/HPTrackingAction.o"
	@echo "... src/HPTrackingAction.i"
	@echo "... src/HPTrackingAction.s"
	@echo "... src/TrackInfo_t.o"
	@echo "... src/TrackInfo_t.i"
	@echo "... src/TrackInfo_t.s"
	@echo "... src/hptuple.o"
	@echo "... src/hptuple.i"
	@echo "... src/hptuple.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

