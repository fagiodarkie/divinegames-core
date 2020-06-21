CPP = g++ -m64 -std=${CSTD}

includes = -I thirdparty \
	-I headers \
	-I headers/serialisation \
	-I headers/errors \
	-I headers/model \
	-I headers/model/character \
	-I headers/calculator

%.o: %.cpp
	echo $(CPP) $(includes) $(CPPFLAGS) -o $@ -c $<
	$(CPP) $(includes) $(CPPFLAGS) -o $@ -c $<

coresrc = $(wildcard src/calculator/*.cpp) \
	$(wildcard src/calculator/cost_worker/*.cpp) \
	$(wildcard src/calculator/dice_roller/*.cpp) \
	$(wildcard src/calculator/worker/*.cpp) \
	$(wildcard src/combat/*.cpp) \
	$(wildcard src/equipment/*.cpp) \
	$(wildcard src/equipment/craft/*.cpp) \
	$(wildcard src/errors/*.cpp) \
	$(wildcard src/model/*.cpp) \
	$(wildcard src/model/abilities/*.cpp) \
	$(wildcard src/model/attributes/*.cpp) \
	$(wildcard src/model/character/*.cpp) \
	$(wildcard src/model/character/creation/*.cpp) \
	$(wildcard src/model/character/exalt/*.cpp) \
	$(wildcard src/model/managers/*.cpp) \
	$(wildcard src/model/narrative/*.cpp) \
	$(wildcard src/model/power/*.cpp) \
	$(wildcard src/model/social/*.cpp) \
	$(wildcard src/model/virtues/*.cpp) \
	$(wildcard src/serialisation/*.cpp)

testsrc = $(coresrc) \
	$(wildcard src/test/*.cpp) \
	$(wildcard src/test-case/calculator/*.cpp) \
	$(wildcard src/test-case/calculator/cost_worker/*.cpp) \
	$(wildcard src/test-case/calculator/worker/*.cpp) \
	$(wildcard src/test-case/errors/*.cpp) \
	$(wildcard src/test-case/model/*.cpp) \
	$(wildcard src/test-case/model/abilities/*.cpp) \
	$(wildcard src/test-case/model/attributes/*.cpp) \
	$(wildcard src/test-case/model/character/*.cpp) \
	$(wildcard src/test-case/model/managers/*.cpp) \
	$(wildcard src/test-case/model/narrative/*.cpp) \
	$(wildcard src/test-case/model/power/*.cpp) \
	$(wildcard src/test-case/model/social/*.cpp) \
	$(wildcard src/test-case/model/virtues/*.cpp) \
	$(wildcard src/test-case/serialisation/*.cpp) \
	$(wildcard src/test-case/*.cpp)

coreobj = $(coresrc:.cpp=.o)

testobj = $(testsrc:.cpp=.o)

test: $(testobj)
	echo $(testobj)
	$(CPP) $(includes) -o $@ $(testobj)

# declare OUTDLL to be equal to "-o divinegames-core.dll" to compile DLL as well

divinegames: $(coreobj)
	$(CPP) -shared $(includes) ${OUTDLL} $^ -Wl,--export-all-symbols,--out-implib,libdivinegames-core.a

.PHONY: clean
clean:
	del /S *.o