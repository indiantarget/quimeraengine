#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.137                       #
#------------------------------------------------------------------------------#


WORKDIR = `pwd`

CC = gcc
CXX = g++
AR = ar
LD = g++
WINDRES = windres

#DebugLinux32SharedrtStatic
INC_DEBUGLINUX32SHAREDRTSTATIC =  -I$(MAKEPATH)trunk/headers -I$(MAKEPATH)trunk/3rdparty/Boost/include -I$(MAKEPATH)trunk/testing/tests/unit
CFLAGS_DEBUGLINUX32SHAREDRTSTATIC =  -Wshadow -Wredundant-decls -Wcast-align -Winline -Wmissing-include-dirs -Wswitch-default -Wall -g -m32 -D_DEBUG
RESINC_DEBUGLINUX32SHAREDRTSTATIC =  
RCFLAGS_DEBUGLINUX32SHAREDRTSTATIC =  
LIBDIR_DEBUGLINUX32SHAREDRTSTATIC =  -L$(MAKEPATH)trunk/testing/bin/CodeBlocks10/DebugLinux32SharedrtStatic -L$(MAKEPATH)trunk/3rdparty/Boost/bin/Linux32/DebugSharedrtStatic
LIB_DEBUGLINUX32SHAREDRTSTATIC = $(MAKEPATH)trunk/bin/CodeBlocks10/DebugLinux32SharedrtStatic/QuimeraEngineCommon.a libboost_unit_test_framework.a
LDFLAGS_DEBUGLINUX32SHAREDRTSTATIC =  -m32
OBJDIR_DEBUGLINUX32SHAREDRTSTATIC = $(MAKEPATH)trunk/testing/garbage/CodeBlocks10/DebugLinux32SharedrtStatic
DEP_DEBUGLINUX32SHAREDRTSTATIC = 
OUT_DEBUGLINUX32SHAREDRTSTATIC = $(MAKEPATH)trunk/testing/bin/CodeBlocks10/DebugLinux32SharedrtStatic/Unit_TestModule_Common
OBJ_DEBUGLINUX32SHAREDRTSTATIC = $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQFloat_Test.o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQVF32_Test.o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/TestModule_Common.o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/testsystem/EQTestType.o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/testsystem/QCommonTestConfig.o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/testsystem/QSimpleConfigLoader.o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/EQEnumeration_Test.o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQInteger_Test.o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQBoolean_Test.o

#DebugLinux32SharedrtDynamic
INC_DEBUGLINUX32SHAREDRTDYNAMIC =  -I$(MAKEPATH)trunk/headers -I$(MAKEPATH)trunk/3rdparty/Boost/include -I$(MAKEPATH)trunk/testing/tests/unit
CFLAGS_DEBUGLINUX32SHAREDRTDYNAMIC =  -Wshadow -Wredundant-decls -Wcast-align -Winline -Wmissing-include-dirs -Wswitch-default -Wall -g -m32 -D_DEBUG -DQE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE
RESINC_DEBUGLINUX32SHAREDRTDYNAMIC =  
RCFLAGS_DEBUGLINUX32SHAREDRTDYNAMIC =  
LIBDIR_DEBUGLINUX32SHAREDRTDYNAMIC =  -L$(MAKEPATH)trunk/testing/bin/CodeBlocks10/DebugLinux32SharedrtDynamic -L$(MAKEPATH)trunk/3rdparty/Boost/bin/Linux32/DebugSharedrtStatic
LIB_DEBUGLINUX32SHAREDRTDYNAMIC = libQuimeraEngineCommon.so libboost_unit_test_framework.a
LDFLAGS_DEBUGLINUX32SHAREDRTDYNAMIC =  -m32
OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC = $(MAKEPATH)trunk/testing/garbage/CodeBlocks10/DebugLinux32SharedrtDynamic
DEP_DEBUGLINUX32SHAREDRTDYNAMIC = 
OUT_DEBUGLINUX32SHAREDRTDYNAMIC = $(MAKEPATH)trunk/testing/bin/CodeBlocks10/DebugLinux32SharedrtDynamic/Unit_TestModule_Common
OBJ_DEBUGLINUX32SHAREDRTDYNAMIC = $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQFloat_Test.o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQVF32_Test.o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/TestModule_Common.o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/testsystem/EQTestType.o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/testsystem/QCommonTestConfig.o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/testsystem/QSimpleConfigLoader.o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/EQEnumeration_Test.o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQInteger_Test.o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQBoolean_Test.o


all: debuglinux32sharedrtstatic debuglinux32sharedrtdynamic

clean: clean_debuglinux32sharedrtstatic clean_debuglinux32sharedrtdynamic


#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
#  DebugLinux32SharedrtStatic ~~~  DebugLinux32SharedrtStatic  ~~~  DebugLinux32SharedrtStatic  ~~~  DebugLinux32SharedrtStatic  ~~~  DebugLinux32SharedrtStatic  ~~~        #  
#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#

before_debuglinux32sharedrtstatic: 
	test -d $(MAKEPATH)trunk/testing/bin/CodeBlocks10/DebugLinux32SharedrtStatic || mkdir -p $(MAKEPATH)trunk/testing/bin/CodeBlocks10/DebugLinux32SharedrtStatic
	test -d $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common || mkdir -p $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common
	test -d $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/testsystem || mkdir -p $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/testsystem

after_debuglinux32sharedrtstatic: 
	cp "$(MAKEPATH)trunk/testing/bin/TestConfig.txt" "$(MAKEPATH)trunk/testing/bin/CodeBlocks10/DebugLinux32SharedrtStatic"

debuglinux32sharedrtstatic: before_debuglinux32sharedrtstatic out_debuglinux32sharedrtstatic after_debuglinux32sharedrtstatic

out_debuglinux32sharedrtstatic: $(OBJ_DEBUGLINUX32SHAREDRTSTATIC) $(DEP_DEBUGLINUX32SHAREDRTSTATIC)
	$(LD) $(LDFLAGS_DEBUGLINUX32SHAREDRTSTATIC) $(LIBDIR_DEBUGLINUX32SHAREDRTSTATIC) $(OBJ_DEBUGLINUX32SHAREDRTSTATIC) $(LIB_DEBUGLINUX32SHAREDRTSTATIC) -o $(OUT_DEBUGLINUX32SHAREDRTSTATIC)

$(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQFloat_Test.o: $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQFloat_Test.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTSTATIC) $(INC_DEBUGLINUX32SHAREDRTSTATIC) -c $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQFloat_Test.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQFloat_Test.o

$(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQVF32_Test.o: $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQVF32_Test.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTSTATIC) $(INC_DEBUGLINUX32SHAREDRTSTATIC) -c $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQVF32_Test.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQVF32_Test.o

$(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/TestModule_Common.o: $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/TestModule_Common.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTSTATIC) $(INC_DEBUGLINUX32SHAREDRTSTATIC) -c $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/TestModule_Common.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/TestModule_Common.o

$(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/testsystem/EQTestType.o: $(MAKEPATH)trunk/testing/testsystem/EQTestType.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTSTATIC) $(INC_DEBUGLINUX32SHAREDRTSTATIC) -c $(MAKEPATH)trunk/testing/testsystem/EQTestType.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/testsystem/EQTestType.o

$(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/testsystem/QCommonTestConfig.o: $(MAKEPATH)trunk/testing/testsystem/QCommonTestConfig.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTSTATIC) $(INC_DEBUGLINUX32SHAREDRTSTATIC) -c $(MAKEPATH)trunk/testing/testsystem/QCommonTestConfig.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/testsystem/QCommonTestConfig.o

$(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/testsystem/QSimpleConfigLoader.o: $(MAKEPATH)trunk/testing/testsystem/QSimpleConfigLoader.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTSTATIC) $(INC_DEBUGLINUX32SHAREDRTSTATIC) -c $(MAKEPATH)trunk/testing/testsystem/QSimpleConfigLoader.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/testsystem/QSimpleConfigLoader.o

$(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/EQEnumeration_Test.o: $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/EQEnumeration_Test.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTSTATIC) $(INC_DEBUGLINUX32SHAREDRTSTATIC) -c $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/EQEnumeration_Test.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/EQEnumeration_Test.o
	
$(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQInteger_Test.o: $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQInteger_Test.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTSTATIC) $(INC_DEBUGLINUX32SHAREDRTSTATIC) -c $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQInteger_Test.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQInteger_Test.o	

$(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQBoolean_Test.o: $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQBoolean_Test.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTSTATIC) $(INC_DEBUGLINUX32SHAREDRTSTATIC) -c $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQBoolean_Test.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTSTATIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQBoolean_Test.o	

clean_debuglinux32sharedrtstatic: 
	rm -f $(OBJ_DEBUGLINUX32SHAREDRTSTATIC) $(OUT_DEBUGLINUX32SHAREDRTSTATIC)


#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
#  DebugLinux32SharedrtDynamic  ~~~  DebugLinux32SharedrtDynamic  ~~~  DebugLinux32SharedrtDynamic  ~~~  DebugLinux32SharedrtDynamic  ~~~  DebugLinux32SharedrtDynamic  ~~~  #  
#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#

before_debuglinux32sharedrtdynamic: 
	test -d $(MAKEPATH)trunk/testing/bin/CodeBlocks10/DebugLinux32SharedrtDynamic || mkdir -p $(MAKEPATH)trunk/testing/bin/CodeBlocks10/DebugLinux32SharedrtDynamic
	test -d $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common || mkdir -p $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common
	test -d $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/testsystem || mkdir -p $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/testsystem
	cp "$(MAKEPATH)trunk/bin/CodeBlocks10/DebugLinux32SharedrtDynamic/libQuimeraEngineCommon.so" "."
	cp "$(MAKEPATH)trunk/bin/CodeBlocks10/DebugLinux32SharedrtDynamic/libQuimeraEngineCommon.so" "$(MAKEPATH)trunk/testing/bin/CodeBlocks10/DebugLinux32SharedrtDynamic/"

after_debuglinux32sharedrtdynamic: 
	cp "$(MAKEPATH)trunk/testing/bin/TestConfig.txt" "$(MAKEPATH)trunk/testing/bin/CodeBlocks10/DebugLinux32SharedrtDynamic"
	rm *.so

debuglinux32sharedrtdynamic: before_debuglinux32sharedrtdynamic out_debuglinux32sharedrtdynamic after_debuglinux32sharedrtdynamic

out_debuglinux32sharedrtdynamic: $(OBJ_DEBUGLINUX32SHAREDRTDYNAMIC) $(DEP_DEBUGLINUX32SHAREDRTDYNAMIC)
	$(LD) $(LDFLAGS_DEBUGLINUX32SHAREDRTDYNAMIC) $(LIBDIR_DEBUGLINUX32SHAREDRTDYNAMIC) $(OBJ_DEBUGLINUX32SHAREDRTDYNAMIC) $(LIB_DEBUGLINUX32SHAREDRTDYNAMIC) -o $(OUT_DEBUGLINUX32SHAREDRTDYNAMIC)

$(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQFloat_Test.o: $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQFloat_Test.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INC_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQFloat_Test.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQFloat_Test.o

$(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQVF32_Test.o: $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQVF32_Test.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INC_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQVF32_Test.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQVF32_Test.o

$(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/TestModule_Common.o: $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/TestModule_Common.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INC_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/TestModule_Common.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/TestModule_Common.o

$(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/testsystem/EQTestType.o: $(MAKEPATH)trunk/testing/testsystem/EQTestType.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INC_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk/testing/testsystem/EQTestType.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/testsystem/EQTestType.o

$(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/testsystem/QCommonTestConfig.o: $(MAKEPATH)trunk/testing/testsystem/QCommonTestConfig.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INC_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk/testing/testsystem/QCommonTestConfig.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/testsystem/QCommonTestConfig.o

$(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/testsystem/QSimpleConfigLoader.o: $(MAKEPATH)trunk/testing/testsystem/QSimpleConfigLoader.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INC_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk/testing/testsystem/QSimpleConfigLoader.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/testsystem/QSimpleConfigLoader.o

$(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/EQEnumeration_Test.o: $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/EQEnumeration_Test.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INC_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/EQEnumeration_Test.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/EQEnumeration_Test.o
	
$(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQInteger_Test.o: $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQInteger_Test.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INC_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQInteger_Test.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQInteger_Test.o	

$(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQBoolean_Test.o: $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQBoolean_Test.cpp
	$(CXX) $(CFLAGS_DEBUGLINUX32SHAREDRTDYNAMIC) $(INC_DEBUGLINUX32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk/testing/tests/unit/testmodule_common/SQBoolean_Test.cpp -o $(OBJDIR_DEBUGLINUX32SHAREDRTDYNAMIC)$(MAKEPATH__)trunk/testing/tests/unit/testmodule_common/SQBoolean_Test.o	

clean_debuglinux32sharedrtdynamic: 
	rm -f $(OBJ_DEBUGLINUX32SHAREDRTDYNAMIC) $(OUT_DEBUGLINUX32SHAREDRTDYNAMIC)


.PHONY: before_debuglinux32sharedrtstatic after_debuglinux32sharedrtstatic clean_debuglinux32sharedrtstatic before_debuglinux32sharedrtdynamic after_debuglinux32sharedrtdynamic clean_debuglinux32sharedrtdynamic

