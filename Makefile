all: 
	cd src/voip/client && make
	cd src/voip/server && make
	cd src/server && make
	cd src/network/client && make
	cd src/network/server && make

test:
	@echo "No test defined yet"
.PHONY: all test 
