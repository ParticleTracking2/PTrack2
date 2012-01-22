################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/Utils/subdir.mk
-include src/Output/OutImpl/subdir.mk
-include src/Output/subdir.mk
-include src/Image/ImageReader/subdir.mk
-include src/Image/subdir.mk
-include src/Container/subdir.mk
-include src/Arguments/subdir.mk
-include src/Algorithm/Implementations/subdir.mk
-include src/Algorithm/Chi2LibCuda/subdir.mk
-include src/Algorithm/Chi2Lib/subdir.mk
-include src/Algorithm/subdir.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: PTrack2

# Tool invocations
PTrack2: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ -L/usr/local/cuda/lib64 -L/usr/local/lib -L/usr/lib -o "PTrack2" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(OBJS)$(C++_DEPS)$(C_DEPS)$(CC_DEPS)$(CPP_DEPS)$(EXECUTABLES)$(CXX_DEPS)$(C_UPPER_DEPS) PTrack2
	-@echo ' '

install:
	sudo cp PTrack2 /usr/bin
	sudo cp ../src/Distribute\ Computing/PTrack2Bash /usr/bin
	sudo cp ../src/Distribute\ Computing/PTrack2Folder /usr/bin
	sudo cp ../src/Distribute\ Computing/PTrack2FolderCuda /usr/bin
	sudo cp ../src/Distribute\ Computing/PTrack2BashFolders /usr/bin
	cp ../src/Distribute\ Computing/PTrack2BashFolders.conf ~/PTrack2BashFolders.conf.example
	cp ../src/Distribute\ Computing/.PTrack2Bash.conf ~/
	sudo chmod +x /usr/bin/PTrack2
	sudo chmod +x /usr/bin/PTrack2Bash
	sudo chmod +x /usr/bin/PTrack2Folder
	sudo chmod +x /usr/bin/PTrack2FolderCuda
	sudo chmod +x /usr/bin/PTrack2BashFolders
	# Autocompletacion y Manual
	sudo cp ../src/PTrack2_autocomplete.sh /etc/bash_completion.d/PTrack2
	gzip -c ../src/PTrack2.1 > ../src/PTrack2.1.gz
	sudo mv ../src/PTrack2.1.gz /usr/share/man/man1/PTrack2.1.gz
	
uninstall:
	rm ~/.PTrack2Bash.conf
	sudo rm /usr/bin/PTrack2
	sudo rm /usr/bin/PTrack2Bash
	sudo rm /usr/bin/PTrack2Folder
	sudo rm /usr/bin/PTrack2FolderCuda
	sudo rm /usr/bin/PTrack2BashFolders
	# Autocompletacion y Manual
	sudo rm /etc/bash_completion.d/PTrack2
	sudo rm /usr/share/man/man1/PTrack2.1.gz

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
