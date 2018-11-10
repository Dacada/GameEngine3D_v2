CFLAGS += $(shell pkg-config --cflags glfw3)

SRCFILES = $(wildcard $(SRCDIR)/*.c)
INCFILES = $(wildcard $(INCDIR)/*.h)
DBGOBJFILES = $(patsubst $(SRCDIR)/%, debug/%, $(SRCFILES:.c=.o))
RELOBJFILES = $(patsubst $(SRCDIR)/%, release/%, $(SRCFILES:.c=.o))
BASELIBINCFILES = $(wildcard $(LIBINCDIR)/Base/*.h)

FINAL = RenderingEngine.a

.PHONY: all rel dbg clean

all: rel

rel: CFLAGS += $(RELCFLAGS)
rel: | release
rel: release/$(FINAL)

dbg: CFLAGS += $(DBGCFLAGS)
dbg: | debug
dbg: debug/$(FINAL)

clean:
	rm -f debug/* release/*

debug/$(FINAL): $(DBGOBJFILES)
	$(AR) rcs $@ $^
release/$(FINAL): $(RELOBJFILES)
	$(AR) rcs $@ $^

debug:
	mkdir -p debug
release:
	mkdir -p release

debug/%.o: $(SRCDIR)/%.c $(INCFILES) $(BASELIBINCFILES)
	$(CC) -c -o $@ $< $(CFLAGS)
release/%.o: $(SRCDIR)/%.c $(INCFILES) $(BASELIBINCFILES)
	$(CC) -c -o $@ $< $(CFLAGS)
