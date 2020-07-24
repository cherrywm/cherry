cherry: src/cherry.c
	gcc src/cherry.c -o cherry -lxcb -llua5.3

xephyr:
	Xephyr -br -ac -noreset -screen 1920x1080 :1 &

kill_xephyr:
	killall Xephyr

test:
	DISPLAY=:1 ./cherry