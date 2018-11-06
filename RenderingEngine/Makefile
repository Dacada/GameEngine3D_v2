SRCDIR = src
INCDIR = include

AR = gcc-ar
CC = gcc
CFLAGS = -I$(INCDIR) -I$(LIBINCDIR) -Wall -Wextra -Werror -std=gnu99 -Wformat\
         -Wformat-security -D_FORTIFY_SOURCE=2 -flto -fuse-linker-plugin

DBGCFLAGS = -Og -DDEBUG -fsanitize=address -fsanitize=undefined -fsanitize=leak -fno-omit-frame-pointer
RELCFLAGS = -O3

SRCFILES = $(wildcard $(SRCDIR)/*.c)
INCFILES = $(wildcard $(INCDIR)/*.h)
DBGOBJFILES = $(patsubst $(SRCDIR)/%, debug/%, $(SRCFILES:.c=.o))
RELOBJFILES = $(patsubst $(SRCDIR)/%, release/%, $(SRCFILES:.c=.o))

FINAL = RenderingEngine.a

.PHONY: all rel dbg clean

all: rel

rel: CFLAGS += RELCFLAGS
rel: | release
rel: release/$(FINAL)

dbg: CFLAGS += DBGCFLAGS
dbg: | debug
dbg: debug/$(FINAL)

clean:
	rm -f debug/* release/*

debug/$(FINAL): $(DBGOBJFILES) $(DBGSTATICLIBS)
	$(AR) rcs $@ $^
release/$(FINAL): $(RELOBJFILES) $(RELSTATICLIBS)
	$(AR) rcs $@ $^

debug:
	mkdir -p debug
release:
	mkdir -p release

debug/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)
release/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

