#------------------------------------------------------------------------------#
# This makefile was generated by 'cbp2make' tool rev.137                       #
#------------------------------------------------------------------------------#


WORKDIR = %cd%

CC = gcc.exe
CXX = g++.exe
AR = ar.exe
LD = g++.exe
WINDRES = windres.exe

# DebugWin32SharedrtStatic
INC_DEBUGWIN32SHAREDRTSTATIC =  -I$(MAKEPATH)trunk/headers -I$(MAKEPATH)trunk/3rdparty/Boost/include -I$(MAKEPATH)trunk/testing/tests/unit
CFLAGS_DEBUGWIN32SHAREDRTSTATIC =  -Wshadow -Wredundant-decls -Wcast-align -Winline -Wmissing-include-dirs -Wswitch-default -Wall -g -D_DEBUG
RESINC_DEBUGWIN32SHAREDRTSTATIC =  
RCFLAGS_DEBUGWIN32SHAREDRTSTATIC =  
LIBDIR_DEBUGWIN32SHAREDRTSTATIC =  -L$(MAKEPATH)\\trunk\\bin\CodeBlocks10\DebugWin32SharedrtStatic -L$(MAKEPATH)\\trunk\\3rdparty\Boost\bin\Win32\DebugSharedrtStatic
LIB_DEBUGWIN32SHAREDRTSTATIC = $(MAKEPATH)\\trunk\\bin\CodeBlocks10\DebugWin32SharedrtStatic\QuimeraEngineCommon.lib -lboost_unit_test_framework-mt-d
LDFLAGS_DEBUGWIN32SHAREDRTSTATIC =  
OBJDIR_DEBUGWIN32SHAREDRTSTATIC = $(MAKEPATH)trunk\\testing\\garbage\\CodeBlocks10\\DebugWin32SharedrtStatic
DEP_DEBUGWIN32SHAREDRTSTATIC = 
OUT_DEBUGWIN32SHAREDRTSTATIC = $(MAKEPATH)trunk\\testing\\bin\\CodeBlocks10\\DebugWin32SharedrtStatic\\Unit_TestModule_Common.exe
OBJ_DEBUGWIN32SHAREDRTSTATIC = $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQFloat_Test.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQVF32_Test.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\TestModule_Common.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\EQTestType.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\QCommonTestConfig.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\QSimpleConfigLoader.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\EQEnumeration_Test.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQInteger_Test.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQBoolean_Test.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\QAlignment_Test.o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\AllocationOperators_Test.o

# DebugWin32SharedrtDynamic
INC_DEBUGWIN32SHAREDRTDYNAMIC =  -I$(MAKEPATH)trunk/headers -I$(MAKEPATH)trunk/3rdparty/Boost/include -I$(MAKEPATH)trunk/testing/tests/unit
CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC =  -Wshadow -Wredundant-decls -Wcast-align -Winline -Wmissing-include-dirs -Wswitch-default -Wall -g -D_DEBUG -DQE_PREPROCESSOR_IMPORTLIB_QUIMERAENGINE
RESINC_DEBUGWIN32SHAREDRTDYNAMIC =  
RCFLAGS_DEBUGWIN32SHAREDRTDYNAMIC =  
LIBDIR_DEBUGWIN32SHAREDRTDYNAMIC =  -L$(MAKEPATH)\\trunk\\3rdparty\Boost\bin\Win32\DebugSharedrtStatic
LIB_DEBUGWIN32SHAREDRTDYNAMIC = -lboost_unit_test_framework-mt-d $(MAKEPATH)\\trunk\\bin\CodeBlocks10\DebugWin32SharedrtDynamic\QuimeraEngineCommon.dll
LDFLAGS_DEBUGWIN32SHAREDRTDYNAMIC =  
OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC = $(MAKEPATH)trunk\\testing\\garbage\\CodeBlocks10\\DebugWin32SharedrtDynamic
DEP_DEBUGWIN32SHAREDRTDYNAMIC = 
OUT_DEBUGWIN32SHAREDRTDYNAMIC = $(MAKEPATH)trunk\\testing\\bin\\CodeBlocks10\\DebugWin32SharedrtDynamic\\Unit_TestModule_Common.exe
OBJ_DEBUGWIN32SHAREDRTDYNAMIC = $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQFloat_Test.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQVF32_Test.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\TestModule_Common.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\EQTestType.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\QCommonTestConfig.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\QSimpleConfigLoader.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\EQEnumeration_Test.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQInteger_Test.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQBoolean_Test.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\QAlignment_Test.o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\AllocationOperators_Test.o

all: debugwin32sharedrtstatic debugwin32sharedrtdynamic

clean: clean_debugwin32sharedrtstatic clean_debugwin32sharedrtdynamic

#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
#	DebugWin32SharedrtStatic   ~~~   DebugWin32SharedrtStatic   ~~~   DebugWin32SharedrtStatic   ~~~   DebugWin32SharedrtStatic   ~~~   DebugWin32SharedrtStatic   ~~~       #  
#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
	
before_debugwin32sharedrtstatic: 
	cmd /c if not exist $(MAKEPATH)trunk\\testing\\bin\\CodeBlocks10\\DebugWin32SharedrtStatic md $(MAKEPATH)trunk\\testing\\bin\\CodeBlocks10\\DebugWin32SharedrtStatic
	cmd /c if not exist $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common md $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common
	cmd /c if not exist $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\testsystem md $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\testsystem

after_debugwin32sharedrtstatic: 
	cmd /c copy "$(MAKEPATH)trunk\testing\bin\TestConfig.txt" "$(MAKEPATH)trunk\testing\bin\CodeBlocks10\DebugWin32SharedrtStatic"

debugwin32sharedrtstatic: before_debugwin32sharedrtstatic out_debugwin32sharedrtstatic after_debugwin32sharedrtstatic

out_debugwin32sharedrtstatic: $(OBJ_DEBUGWIN32SHAREDRTSTATIC) $(DEP_DEBUGWIN32SHAREDRTSTATIC)
	$(LD) $(LDFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(LIBDIR_DEBUGWIN32SHAREDRTSTATIC) $(OBJ_DEBUGWIN32SHAREDRTSTATIC) $(LIB_DEBUGWIN32SHAREDRTSTATIC) -o $(OUT_DEBUGWIN32SHAREDRTSTATIC)

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQFloat_Test.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQFloat_Test.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQFloat_Test.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQFloat_Test.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQVF32_Test.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQVF32_Test.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQVF32_Test.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQVF32_Test.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\TestModule_Common.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\TestModule_Common.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\TestModule_Common.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\TestModule_Common.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\EQTestType.o: $(MAKEPATH)trunk\\testing\\testsystem\\EQTestType.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)trunk\\testing\\testsystem\\EQTestType.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\EQTestType.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\QCommonTestConfig.o: $(MAKEPATH)trunk\\testing\\testsystem\\QCommonTestConfig.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)trunk\\testing\\testsystem\\QCommonTestConfig.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\QCommonTestConfig.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\QSimpleConfigLoader.o: $(MAKEPATH)trunk\\testing\\testsystem\\QSimpleConfigLoader.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)trunk\\testing\\testsystem\\QSimpleConfigLoader.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\QSimpleConfigLoader.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\EQEnumeration_Test.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\EQEnumeration_Test.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\EQEnumeration_Test.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\EQEnumeration_Test.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQInteger_Test.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQInteger_Test.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQInteger_Test.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQInteger_Test.o
	
$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQBoolean_Test.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQBoolean_Test.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQBoolean_Test.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQBoolean_Test.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\QAlignment_Test.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\QAlignment_Test.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\QAlignment_Test.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\QAlignment_Test.o

$(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\AllocationOperators_Test.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\AllocationOperators_Test.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTSTATIC) $(INC_DEBUGWIN32SHAREDRTSTATIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\AllocationOperators_Test.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTSTATIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\AllocationOperators_Test.o

clean_debugwin32sharedrtstatic: 


#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
#	DebugWin32SharedrtDynamic   ~~~   DebugWin32SharedrtDynamic   ~~~   DebugWin32SharedrtDynamic   ~~~   DebugWin32SharedrtDynamic   ~~~   DebugWin32SharedrtDynamic   ~~~  #  
#----------------------------------------------------------------------------------------------------------------------------------------------------------------------------#
	
before_debugwin32sharedrtdynamic: 
	cmd /c if not exist $(MAKEPATH)trunk\\testing\\bin\\CodeBlocks10\\DebugWin32SharedrtDynamic md $(MAKEPATH)trunk\\testing\\bin\\CodeBlocks10\\DebugWin32SharedrtDynamic
	cmd /c if not exist $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common md $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common
	cmd /c if not exist $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\testsystem md $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\testsystem

after_debugwin32sharedrtdynamic: 
	cmd /c copy "$(MAKEPATH)trunk\testing\bin\TestConfig.txt" "$(MAKEPATH)trunk\testing\bin\CodeBlocks10\DebugWin32SharedrtDynamic"
	cmd /c copy "$(MAKEPATH)trunk\bin\CodeBlocks10\DebugWin32SharedrtDynamic\QuimeraEngineCommon.dll" "$(MAKEPATH)trunk\testing\bin\CodeBlocks10\DebugWin32SharedrtDynamic" /Y

debugwin32sharedrtdynamic: before_debugwin32sharedrtdynamic out_debugwin32sharedrtdynamic after_debugwin32sharedrtdynamic

out_debugwin32sharedrtdynamic: $(OBJ_DEBUGWIN32SHAREDRTDYNAMIC) $(DEP_DEBUGWIN32SHAREDRTDYNAMIC)
	$(LD) $(LDFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(LIBDIR_DEBUGWIN32SHAREDRTDYNAMIC) $(OBJ_DEBUGWIN32SHAREDRTDYNAMIC) $(LIB_DEBUGWIN32SHAREDRTDYNAMIC) -o $(OUT_DEBUGWIN32SHAREDRTDYNAMIC)

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQFloat_Test.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQFloat_Test.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQFloat_Test.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQFloat_Test.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQVF32_Test.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQVF32_Test.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQVF32_Test.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQVF32_Test.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\TestModule_Common.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\TestModule_Common.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\TestModule_Common.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\TestModule_Common.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\EQTestType.o: $(MAKEPATH)trunk\\testing\\testsystem\\EQTestType.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk\\testing\\testsystem\\EQTestType.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\EQTestType.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\QCommonTestConfig.o: $(MAKEPATH)trunk\\testing\\testsystem\\QCommonTestConfig.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk\\testing\\testsystem\\QCommonTestConfig.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\QCommonTestConfig.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\QSimpleConfigLoader.o: $(MAKEPATH)trunk\\testing\\testsystem\\QSimpleConfigLoader.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk\\testing\\testsystem\\QSimpleConfigLoader.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\testsystem\\QSimpleConfigLoader.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\EQEnumeration_Test.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\EQEnumeration_Test.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\EQEnumeration_Test.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\EQEnumeration_Test.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQInteger_Test.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQInteger_Test.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQInteger_Test.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQInteger_Test.o
	
$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQBoolean_Test.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQBoolean_Test.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\SQBoolean_Test.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\SQBoolean_Test.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\QAlignment_Test.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\QAlignment_Test.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\QAlignment_Test.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\QAlignment_Test.o

$(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\AllocationOperators_Test.o: $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\AllocationOperators_Test.cpp
	$(CXX) $(CFLAGS_DEBUGWIN32SHAREDRTDYNAMIC) $(INC_DEBUGWIN32SHAREDRTDYNAMIC) -c $(MAKEPATH)trunk\\testing\\tests\\unit\\testmodule_common\\AllocationOperators_Test.cpp -o $(OBJDIR_DEBUGWIN32SHAREDRTDYNAMIC)$(MAKEPATH__)\\trunk\\testing\\tests\\unit\\testmodule_common\\AllocationOperators_Test.o

	
clean_debugwin32sharedrtdynamic: 


	
.PHONY: before_debugwin32sharedrtstatic after_debugwin32sharedrtstatic clean_debugwin32sharedrtstatic before_debugwin32sharedrtdynamic after_debugwin32sharedrtdynamic clean_debugwin32sharedrtdynamic

