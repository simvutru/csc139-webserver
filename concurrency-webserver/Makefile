CC = gcc
CFLAGS = -Wall -O3
LDFLAGS = -lpthread

SRC_DIR = src
BUILD_DIR = build

# Targets inside build directory
TARGETS = $(BUILD_DIR)/wserver $(BUILD_DIR)/wclient 

all: $(TARGETS)

# Link wserver
$(BUILD_DIR)/wserver:$(BUILD_DIR)/wserver.o $(BUILD_DIR)/request.o $(BUILD_DIR)/io_helper.o $(BUILD_DIR)/queue.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Link wclient
$(BUILD_DIR)/wclient: $(BUILD_DIR)/wclient.o $(BUILD_DIR)/io_helper.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

# Compile src/*.c to build/*.o (creates build directory if missing)
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Order-only rule to create the build folder
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR) log.txt

server:
	./$(BUILD_DIR)/wserver -d www -p 8003 -t 8 -b 16 -s SFF
test:
	ab -n 1000 -c 1 localhost:8003/godzilla.gif
test1:
	ab -n 1000 -c 1 localhost:8003/cgi-bin/adder?4\&5
test2:
	ab -n 100 -c 5 localhost:8003/cgi-bin/spin?2

test_SFF:
	# generate the test files
	head -c 10M /dev/urandom > www/large.txt
	head -c 1M /dev/urandom > www/medium.txt
	head -c 1K /dev/urandom > www/small.txt
	# start the server
	./build/wserver -d www -p 10000 -t 1 -b 10 -s SFF &
	# Fire Large first, Medium second, Small last
	curl -s -o /dev/null -w "large.txt finished at: %{time_total}s\n" http://localhost:10000/large.txt &
	curl -s -o /dev/null -w "medium.txt finished at: %{time_total}s\n" http://localhost:10000/medium.txt &
	curl -s -o /dev/null -w "small.txt finished at: %{time_total}s\n" http://localhost:10000/small.txt &
	wait
	# shutdown server
	pkill wserver

.PHONY: all clean test
