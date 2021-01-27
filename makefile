CXX = g++ 
CXXFLAGS = -Wall -Wextra -L. -g 

LDFLAGS = -fPIC -shared 
RM = rm -f 
EXEC = firewall.exe
OTHER_LIB = input
LIB_OBJ = string.cpp field.cpp ip.cpp port.cpp 


all:${EXEC}

firewall:
	$(CXX) ${CXXFLAGS} ${LDFLAGS} ${LIB_OBJ} -o libfirewall.so


${EXEC}: firewall
	$(CXX) ${CXXFLAGS} main.cpp -o ${EXEC} -lfirewall -linput


clean:
	-${RM} firewall ${EXEC}