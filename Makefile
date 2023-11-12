.PHONY: all clean

FTP_USERNAME ?= w # set these fields to what your ftp server uses on switch (if it has one)
FTP_PASSWORD ?= w

LOGGER_IP ?=  10.0.0.101 # server IP 
FTP_IP ?= 10.0.0.59 # console IP

all:
	cmake --toolchain=cmake/toolchain.cmake -DFTP_IP=$(FTP_IP) -DFTP_USERNAME=$(FTP_USERNAME) -DFTP_PASSWORD=$(FTP_PASSWORD) -DLOGGER_IP=$(LOGGER_IP) -S . -B build && $(MAKE) -C build subsdk9_meta 

clean:
	rm -r build || true

log: all
	python3.8 scripts/tcpServer.py 0.0.0.0