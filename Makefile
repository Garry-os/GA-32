.PHONY: all asm clean

all: asm
asm:
	@ $(MAKE) -C asm

clean:
	rm -rf build

