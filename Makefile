all: 
	make -f src/voip/client/Makefile
	make -f src/voip/server/Makefile
	make -f src/server/Makefile
	make -f src/network/client/Makefile
	make -f src/network/server/Makefile

test:
	@echo "No test defined yet"
.PHONY: all test 
