CC = gcc
CFLAGS = -Wall -O3 -march=armv8.2-a+crypto
LDFLAGS = -lpthread

mecanumbot: main.c network_mgr.c motor_driver.c
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f mecanumbot
	sync && echo 3 | sudo tee /proc/sys/vm/drop_caches
