# START USER DEFINE AREA
# You can edit this area.

# [User modify Data]

# Library Path Define
#
# BOOST_INCLUDE / BOOST_LIB
#
# Set variables in /etc/profile or .bash_profile.
#

INCLUDE =	-I$(BOOST_INCLUDE) \
			-I$(MYSQL_INCLUDE) \
			-I$(MYSQL_DRIVER_INCLUDE)

LIB = 		-lboost_thread \
		-lboost_system \
		-lboost_chrono \
		-lboost_filesystem \
		-lboost_regex \
		-lboost_date_time \
		-lboost_locale \
		-ldl \
		-lpthread \
		-lodbc\
		-lz \
		-L$(BOOST_LIB)

# [User modify Data] End

CFLAGS = -O2 -Wno-write-strings -Wno-deprecated -Wno-attributes -Wno-int-to-pointer-cast -std=c++11
LFLAGS = -g -Wall -ggdb
#-g -Wall -ggdb

OBJ_FILES = `ls *.o`

TARGET_FILE = DServer

MAKE_PATH = `pwd`
COMPILELISTPATH = $(MAKE_PATH)/py/CompileList
LASTCOMPILELISTPATH = $(MAKE_PATH)/py/LastCompileList

OBJ_DIR = x64
MAKE_DIR = ../make_gcc

JOB_COUNT=8

SINGLE_FILE = ../src/main.cpp
PROJECT_PATH=$(MAKE_PATH)/..

PY_COMPILELIST=python py/Compile.py $(PROJECT_PATH) $(MAKE_PATH)/$(TARGET_FILE) $(COMPILELISTPATH)
PY_LASTCOMPILELIST=python py/CompileLast.py $(PROJECT_PATH) $(MAKE_PATH)/$(TARGET_FILE) $(LASTCOMPILELISTPATH)

# complie shell script repeat define


CHECK=echo -n stand by; \
		while true; do\
		path=$$(pwd); \
		cd ../; \
		pspath=$$(pwd); \
		cd $$path; \
		\
		if [ `ps -ef | grep $$pspath | grep cc1plus | grep -v grep | wc -l` -le 0 ];\
		then\
			sleep 1;\
			echo .; \
			break; \
		fi;\
		sleep 1; \
		echo -n .;\
	done; 

# complie shell script repeat define
OBJ_DIR_MAKE=if [ -d $(OBJ_DIR) ]; \
	then \
		echo $(OBJ_DIR) exist!;\
	else \
		mkdir $(OBJ_DIR);\
	fi; 

# complie shell script repeat define
COMPILE=Count=0;\
	while read filename;do\
		echo -e "\033[34m [$$((Count+1))]compiling... $$filename.cpp\033[0m";\
		if [ $$((Count % $(JOB_COUNT))) -lt $$(($(JOB_COUNT) - 1)) ]; then\
			g++ -c $$filename.cpp $(INCLUDE) $(CFLAGS) -o $$filename.o &  \
		else \
			g++ -c $$filename.cpp $(INCLUDE) $(CFLAGS) -o $$filename.o;  \
		fi;\
		Count=$$((Count+1));

# complie shell script repeat define
OBJ_MOVE=while read filename;do\
		mv $$filename.o $(MAKE_DIR)/$(OBJ_DIR); 



default:
	@$(PY_LASTCOMPILELIST);\
	echo -e "\033[33mCompile List Python Exe :";\
	echo -e "$(PY_LASTCOMPILELIST) \033[0m";\
	echo -e "\033[35mJOB_COUNT = $(JOB_COUNT) \033[0m"; \
	$(MAKE) lastcompile; 
	$(MAKE) link;
all:
	@$(PY_COMPILELIST);\
	echo -e "\033[33mCompile List Python Exe :";\
	echo -e "$(PY_COMPILELIST) \033[0m";\
	echo -e "\033[35mJOB_COUNT = $(JOB_COUNT) \033[0m"; \
	$(MAKE) clean;
	$(MAKE) compile;
	$(MAKE) link;
compile:
	@ \
	$(OBJ_DIR_MAKE) \
	$(COMPILE)\
	done < $(COMPILELISTPATH); \
	\
	$(CHECK)\
	\
	$(OBJ_MOVE)\
	done < $(COMPILELISTPATH); \
	echo compile : $$(date +%Y-%m-%d_%H:%M:%S) >> compiletime; 
lastcompile:
	@ \
	$(OBJ_DIR_MAKE) \
	$(COMPILE)\
	done < $(LASTCOMPILELISTPATH); \
	\
	$(CHECK)\
	\
	$(OBJ_MOVE)\
	done < $(LASTCOMPILELISTPATH);
	echo lastcompile : $$(date +%Y-%m-%d_%H:%M:%S) >> compiletime; 
link:
	@cd $(OBJ_DIR); \
	echo linking... $(TARGETFILE); \
	g++ $(OBJ_FILES) $(LFLAGS) $(LIB) -o ../$(TARGET_FILE); \

clean:
	@echo cleaning...; 
	rm -f $(TARGET_FILE); 
	rm $(OBJ_DIR) -rf; 

single:
	@echo compiling... $(SINGLE_FILE).cpp; \
  g++ -c $(SINGLE_FILE).cpp $(INCLUDE) $(CFLAGS) -o $(SINGLE_FILE).o; \
  mv $(SINGLE_FILE).o $(MAKE_DIR)/$(OBJ_DIR); \


