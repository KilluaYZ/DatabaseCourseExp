CXX = clang++
CXXFLAGS = -fsanitize=address -g

SERVER_SRC = myserver.cpp
CLIENT_SRC = myclient.cpp 
SERVER_EXEC = myserver
CLIENT_EXEC = myclient

all: $(SERVER_EXEC) $(CLIENT_EXEC)

$(SERVER_EXEC): $(SERVER_SRC) 
	$(CXX) $(CXXFLAGS) -o $@ $^

$(CLIENT_EXEC): $(CLIENT_SRC) 
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -f *.o $(SERVER_EXEC) $(CLIENT_EXEC)