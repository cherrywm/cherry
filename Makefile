TARGET = cherry
CC = gcc
CFLAGS = -o $(TARGET) -Iheaders -lxcb -l xcb-ewmh -llua5.3 -Wall -Wextra -pedantic
SRC_DIR = src
SRC = $(SRC_DIR)/cherry.c $(SRC_DIR)/config.c $(SRC_DIR)/containers.c $(SRC_DIR)/update.c $(SRC_DIR)/ewmh.c

$(TARGET): $(SRC)
	$(CC) $(SRC) $(CFLAGS)

xephyr:
	Xephyr -br -ac -noreset -screen 1920x1080 :1 &

.PHONY: cherryc
cherryc: src/cherryc.c
	$(CC) src/cherryc.c -o cherryc -Wall -Wextra -pedantic -Iheaders

test:
	DISPLAY=:1 ./cherry