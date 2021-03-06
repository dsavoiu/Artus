cmake_minimum_required (VERSION 2.6)
project (Artus)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -std=c++0x -fpic -Wfatal-errors -Wall -O2 -g -DSTANDALONE -Wextra -Wno-unused-parameter -DSTANDALONE -Wswitch-default -Wswitch-enum -Wsync-nand -Wunused-local-typedefs -Wtrampolines -Wno-aggressive-loop-optimizations -Wpacked -Wwrite-strings -Wstrict-overflow=3 -Wredundant-decls -Wuseless-cast -Wdisabled-optimization -Wmissing-declarations -Wnormalized=nfkc -Wlogical-op -Wmissing-include-dirs -Wvector-operation-performance -Wmissing-format-attribute -Wundef -Wcast-qual -Wcast-align -Wreturn-type")
# warnings to be added in future when issues are fixed:
# -Wunsafe-loop -Wzero-as-null-pointer-constant -Wfloat-equal -Wconversion -Wdouble-promotion -Wstack-protector
# to compile with clang, use: cmake . -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_C_COMPILER=/usr/bin/clang

# Load some basic macros which are needed later on
include(FindROOT.cmake)

if (DEFINED ENV{CMSSW_RELEASE_BASE} )
	set(USE_BOOST_CMSSW TRUE)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSTANDALONE")
	execute_process(WORKING_DIRECTORY $ENV{CMSSW_BASE} COMMAND scram tool info boost COMMAND grep "Version" COMMAND grep -E -o "[0-9.]*(-.*)?" COMMAND tr -d '\n' OUTPUT_VARIABLE BOOSTVER)
	set(BOOST_INCLUDE_DIR "/afs/cern.ch/cms/$ENV{SCRAM_ARCH}/external/boost/${BOOSTVER}/include/")
	set(BOOST_LIB_DIR "/afs/cern.ch/cms/$ENV{SCRAM_ARCH}/external/boost/${BOOSTVER}/lib/")
	set(CORRECTION_DIR "..")
	message(STATUS "Looking for boost ${BOOSTVER} inc in CMSSW: found ${BOOST_INCLUDE_DIR}")
	message(STATUS "Looking for boost ${BOOSTVER} lib in CMSSW: found ${BOOST_LIB_DIR}")
else()
	set(USE_BOOST_CMSSW FALSE)
	set(BOOST_INCLUDE_DIR "")
	set(BOOST_LIB_DIR "")
	set(CORRECTION_DIR "")
	message("Expecting boost to be provided by system")
endif()

set(INCLUDE_DIRECTORIES
	${ROOT_INCLUDE_DIR}
	${BOOST_INCLUDE_DIR}
	${CORRECTION_DIR}
)

include_directories(SYSTEM ${INCLUDE_DIRECTORIES})
include_directories( ${closure_SOURCE_DIR}../ )

add_library(artus_core SHARED
	Core/src/CutFlow.cc
	Core/src/FilterResult.cc
	Core/src/Mutation.cc
	Core/src/ProgressReport.cc
	Core/src/OsSignalHandler.cc
)

target_link_libraries(artus_core
	${ROOT_LIBRARIES}
	)

add_library(artus_configuration SHARED
	Configuration/src/ArtusConfig.cc
	Configuration/src/PropertyTreeSupport.cc
	Configuration/src/RootEnvironment.cc
	Configuration/src/SettingsBase.cc
)

if ( USE_BOOST_CMSSW )
	target_link_libraries( artus_configuration
			-L${BOOST_LIB_DIR}
	        boost_program_options
			${ROOT_LIBRARIES}
			)
else()
	target_link_libraries(artus_configuration
	boost_program_options
	${ROOT_LIBRARIES}
	)
endif()

add_library(artus_consumer SHARED
	Consumer/src/Hist1D.cc
	Consumer/src/Profile2D.cc
	Consumer/src/ValueModifier.cc
	Consumer/src/LambdaNtupleConsumer.cc
)

add_library(artus_filter SHARED
	Filter/src/ArtusFilter.cc
)

add_library(artus_provider SHARED
	Provider/src/ArtusProvider.cc
)

add_library(artus_utility SHARED
	Utility/src/RootFileHelper.cc
	Utility/src/Utility.cc
	Utility/src/ArtusEasyLoggingDecl.cc
	Utility/src/DefaultValues.cc
	Utility/src/CutRange.cc
)

target_link_libraries(artus_utility
	${ROOT_LIBRARIES}
	)



if(EXISTS "../CondFormats")
	message(STATUS "Looking for offline jet corrections: found ../CondFormats")
set_source_files_properties(
	../CondFormats/JetMETObjects/src/FactorizedJetCorrector.cc
	../CondFormats/JetMETObjects/src/JetCorrectionUncertainty.cc
	../CondFormats/JetMETObjects/src/JetCorrectorParameters.cc
	../CondFormats/JetMETObjects/src/JetResolution.cc
	../CondFormats/JetMETObjects/src/SimpleJetCorrectionUncertainty.cc
	../CondFormats/JetMETObjects/src/SimpleJetCorrector.cc
	PROPERTIES COMPILE_FLAGS "-Wno-conversion -Wno-float-equal -Wno-zero-as-null-pointer-constant -Wno-unsafe-loop-optimizations -Wno-double-promotion -Wno-useless-cast -Wno-shadow"
)
add_library(artus_externalcorr SHARED
	../CondFormats/JetMETObjects/src/FactorizedJetCorrector.cc
	../CondFormats/JetMETObjects/src/JetCorrectionUncertainty.cc
	../CondFormats/JetMETObjects/src/JetCorrectorParameters.cc
	../CondFormats/JetMETObjects/src/JetResolution.cc
	../CondFormats/JetMETObjects/src/SimpleJetCorrectionUncertainty.cc
	../CondFormats/JetMETObjects/src/SimpleJetCorrector.cc
)
else()
	message(STATUS "Looking for offline corrections: not found and not compiled.")
endif()

if(EXISTS "../Kappa")
	message(STATUS "Looking for Kappa: found ../Kappa")
	FILE(GLOB KappaAnalysisFiles KappaAnalysis/src/KappaFactory.cc KappaAnalysis/src/*/*.cc)
	add_library(artus_kappaanalysis SHARED ${KappaAnalysisFiles})
else()
	message(STATUS "Looking for Kappa: not found and not compiled")
endif()

add_executable(artus_core_test
	Test/test/Artus_t.cc
)

target_link_libraries( artus_core_test
	artus_core
	artus_configuration
	artus_utility
	${ROOT_LIBRARIES}
)

# use a capital *E*xample here and no underscore
# to be compatible of how the binary is named in the CMSSW build
add_executable(artusExample
	Example/bin/ArtusExample.cc
	Example/src/MeanPtConsumer.cc
)

target_link_libraries(artusExample
	artus_core
	artus_configuration
	artus_provider
	artus_consumer
	artus_utility
	${ROOT_LIBRARIES}
)

