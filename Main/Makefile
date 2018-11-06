SRCDIR = src
INCDIR = include
LIBINCDIR = lib/include
LIBS = -lGLEW -lGLU -lGL -lfreeimage -lm

CC = gcc
CFLAGS = -I$(INCDIR) -I$(LIBINCDIR) -Wall -Wextra -Werror -std=gnu99 -Wformat\
         -Wformat-security -D_FORTIFY_SOURCE=2 -flto -fuse-linker-plugin\
         $(shell pkg-config --cflags glfw3)
LDFLAGS = -Wall -Werror -std=gnu99 -flto -fuse-linker-plugin\
	  $(LIBS) $(shell pkg-config --static --libs glfw3)

DBGCFLAGS = -Og -DDEBUG -fsanitize=address -fsanitize=undefined -fsanitize=leak -fno-omit-frame-pointer
RELCFLAGS = -O3

DBGLDFLAGS = -Og
RELLDFLAGS = -O3

SRCFILES = $(wildcard $(SRCDIR)/*.c)
INCFILES = $(wildcard $(INCDIR)/*.h)
DBGOBJFILES = $(patsubst $(SRCDIR)/%, debug/%, $(SRCFILES:.c=.o))
RELOBJFILES = $(patsubst $(SRCDIR)/%, release/%, $(SRCFILES:.c=.o))
STATICLIBS = CoreEngine.a PhysicsEngine.a RenderingEngine.a
DBGSTATICLIBS = $(patsubst %, lib/debug/%, $(STATICLIBS))
RELSTATICLIBS = $(patsubst %, lib/release/%, $(STATICLIBS))

FINAL = Main

.PHONY: all rel dbg clean

all: rel

rel: CFLAGS += $(RELCFLAGS)
rel: LDFLAGS += $(RELLDFLAGS)
rel: | release
rel: release/$(FINAL)

dbg: CFLAGS += $(DBGCFLAGS)
dbg: LDFLAGS += $(DBGLDFLAGS)
dbg: | debug
dbg: debug/$(FINAL)

clean:
	rm -f debug/* release/*

debug/$(FINAL): $(DBGOBJFILES) $(DBGSTATICLIBS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
release/$(FINAL): $(RELOBJFILES) $(RELSTATICLIBS)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

debug:
	mkdir -p debug
release:
	mkdir -p release

debug/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)
release/%.o: $(SRCDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)

