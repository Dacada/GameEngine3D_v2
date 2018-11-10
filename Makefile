.PHONY: all rel dbg clean

SRCDIR = src
INCDIR = include
LIBINCDIR = lib/include
LIBS = -lGLEW -lGLU -lGL -lfreeimage -lm

AR = gcc-ar
CC = gcc
CFLAGS = -I$(INCDIR) -I$(LIBINCDIR) -Wall -Wextra -Werror -std=gnu99 -Wformat\
	         -Wformat-security -D_FORTIFY_SOURCE=2
LDFLAGS = -Wall -Werror -std=gnu99 $(LIBS)

DBGCFLAGS = -Og -DDEBUG -fsanitize=address -fsanitize=undefined -fsanitize=leak -fno-omit-frame-pointer
RELCFLAGS = -O3 -flto -fuse-linker-plugin

DBGLDFLAGS = -fsanitize=address -fsanitize=undefined -fsanitize=leak
RELLDFLAGS = -O3 -flto -fuse-linker-plugin

export

all: rel

rel:
	$(MAKE) -C Base rel
	$(MAKE) -C RenderingEngine rel
	$(MAKE) -C PhysicsEngine rel
	$(MAKE) -C CoreEngine rel
	$(MAKE) -C Main rel
	$(MAKE) -C UnitTests rel

dbg:
	$(MAKE) -C Base dbg
	$(MAKE) -C RenderingEngine dbg
	$(MAKE) -C PhysicsEngine dbg
	$(MAKE) -C CoreEngine dbg
	$(MAKE) -C Main dbg
	$(MAKE) -C UnitTests dbg

clean:
	$(MAKE) -C UnitTests clean
	$(MAKE) -C Main clean
	$(MAKE) -C CoreEngine clean
	$(MAKE) -C PhysicsEngine clean
	$(MAKE) -C RenderingEngine clean
	$(MAKE) -C Base clean
