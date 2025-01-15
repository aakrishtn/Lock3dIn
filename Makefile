#bundling all the diff programs and making a single executable so that everything runs smoothly

CXX = g++
CXXFLAGS = -std=c++17 -g -Wall -I. -Isrc/app/encryptDecrypt -Isrc/app/file_handling -Isrc/app/processes
#G flag for debugging w/ wall for warnings; I is for linking all files

MAIN_TARGET = encrypt_decrypt
CRYPTION_TARGET = cryption

MAIN_SRC = main.cpp \
           src/app/processes/ProcessManagement.cpp \
           src/app/file_handling/IO.cpp \
           src/app/file_handling/ReadEnv.cpp \
           src/app/encryptDecrypt/Cryption.cpp

CRYPTION_SRC = src/app/encryptDecrypt/CryptionMain.cpp \
               src/app/encryptDecrypt/Cryption.cpp \
               src/app/file_handling/IO.cpp \
               src/app/file_handling/ReadEnv.cpp

MAIN_OBJ = $(MAIN_SRC:.cpp=.o) #making object files of all cpp files in MAIN_SRC
CRYPTION_OBJ = $(CRYPTION_SRC:.cpp=.o)

all: $(MAIN_TARGET) $(CRYPTION_TARGET)

$(MAIN_TARGET): $(MAIN_OBJ) # the main file will be made using all object files; $^ implies taking all cpp files to make an object and use objs to make main file/target output depicted by $@
	$(CXX) $(CXXFLAGS) $^ -o $@ 

$(CRYPTION_TARGET): $(CRYPTION_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp # convert all cpp files to .o files; in the line below cpp/c file will be ip and o file is the target
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean: #cleaning object files
	rm -f $(MAIN_OBJ) $(CRYPTION_OBJ) $(MAIN_TARGET) $(CRYPTION_TARGET)

.PHONY: clean all