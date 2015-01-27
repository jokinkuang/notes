##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=testSelect
ConfigurationName      :=Debug
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
WorkspacePath          := "/home/ema/Desktop/test/testSelect"
ProjectPath            := "/home/ema/Desktop/test/testSelect/testSelect"
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=ema
Date                   :=01/07/2014
CodeLitePath           :="/home/ema/.codelite"
LinkerName             :=gcc
ArchiveTool            :=ar rcus
SharedObjectLinkerName :=gcc -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
CompilerName           :=gcc
C_CompilerName         :=gcc
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
MakeDirCommand         :=mkdir -p
CmpOptions             := -g $(Preprocessors)
LinkOptions            :=  
IncludePath            :=  "$(IncludeSwitch)." "$(IncludeSwitch)." 
RcIncludePath          :=
Libs                   :=
LibPath                := "$(LibraryPathSwitch)." 


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
Objects=$(IntermediateDirectory)/testSelect$(ObjectSuffix) 

##
## Main Build Targets 
##
all: $(OutputFile)

$(OutputFile): makeDirStep $(Objects)
	@$(MakeDirCommand) $(@D)
	$(LinkerName) $(OutputSwitch)$(OutputFile) $(Objects) $(LibPath) $(Libs) $(LinkOptions)

makeDirStep:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/testSelect$(ObjectSuffix): testSelect.c $(IntermediateDirectory)/testSelect$(DependSuffix)
	$(C_CompilerName) $(SourceSwitch) "/home/ema/Desktop/test/testSelect/testSelect/testSelect.c" $(CmpOptions) $(ObjectSwitch)$(IntermediateDirectory)/testSelect$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/testSelect$(DependSuffix): testSelect.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) -MT$(IntermediateDirectory)/testSelect$(ObjectSuffix) -MF$(IntermediateDirectory)/testSelect$(DependSuffix) -MM "/home/ema/Desktop/test/testSelect/testSelect/testSelect.c"

$(IntermediateDirectory)/testSelect$(PreprocessSuffix): testSelect.c
	@$(C_CompilerName) $(CmpOptions) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/testSelect$(PreprocessSuffix) "/home/ema/Desktop/test/testSelect/testSelect/testSelect.c"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/testSelect$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/testSelect$(DependSuffix)
	$(RM) $(IntermediateDirectory)/testSelect$(PreprocessSuffix)
	$(RM) $(OutputFile)


