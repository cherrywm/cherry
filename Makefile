TARGET = cherry
CC = gcc
CFLAGS = -o $(TARGET) -Iheaders -lxcb -l xcb-ewmh -llua5.3 -Wall -Wextra -pedantic
SRC_DIR = src
SRC = $(SRC_DIR)/cherry.c $(SRC_DIR)/config.c $(SRC_DIR)/containers.c $(SRC_DIR)/update.c $(SRC_DIR)/ewmh.c

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS)

channel: $(SRC_DIR)/cherryc.c
	$(CC) $(SRC_DIR)/cherryc.c -Iheaders -Wall -Wextra -pedantic -o cherryc

xephyr:
	Xephyr -br -ac -noreset -screen 1920x1080 :1 &

kill_xephyr:
	killall Xephyr

test:
	DISPLAY=:1 ./cherry