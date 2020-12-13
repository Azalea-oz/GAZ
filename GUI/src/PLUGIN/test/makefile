CXX= g++
CFLAGS = -O2
LIBS =

EXECUTE = main.exe
PLUGINS= Test.dll 
PLUGIN_INTERFACE = Test.hpp


all: $(PLUGINS) $(EXECUTE)
	
clean:
	del /Q *.dll *.a *.exe *.o *.tmp *.exp

$(EXECUTE):
	${CXX} ${CFLAGS} -o $@ $(@:%.exe=%.cpp)
	
$(PLUGINS): 
	${CXX} ${CFLAGS} -c -o $(@:%.dll=%.o) $(@:%.dll=%.cpp)
	${CXX} -mdll -o junk.tmp -Wl,--base-file,base.tmp $(@:%.dll=%.o)
	dlltool -l lib$(@:%.dll=%).a --dllname $@ --base-file base.tmp --output-exp temp.exp --def $(@:%.dll=%.def)
	${CXX} -mdll -o $@ $(@:%.dll=%.o) -Wl,temp.exp
	del /Q *.tmp
	del /Q *.exp
	del /Q *.o