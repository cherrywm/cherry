cherry: src/cherry.c
	gcc src/cherry.c src/loop.c -o cherry -lxcb -llua5.3 -Wall -Wextra

xephyr:
	Xephyr -br -ac -noreset -screen 1920x1080 :1 &

kill_xephyr:
	killall Xephyr

test:
	DISPLAY=:1 ./cherry