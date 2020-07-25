TARGET = cherry
CC = gcc
CFLAGS = -o $(TARGET) -lxcb -llua5.3 -Wall -Wextra
SRC_DIR = src
SRC = $(SRC_DIR)/cherry.c $(SRC_DIR)/loop.c $(SRC_DIR)/config.c $(SRC_DIR)/monitor.c $(SRC_DIR)/desktop.c $(SRC_DIR)/node.c

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS)

xephyr:
	Xephyr -br -ac -noreset -screen 1920x1080 :1 &

kill_xephyr:
	killall Xephyr

test:
	DISPLAY=:1 ./cherry