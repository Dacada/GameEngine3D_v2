LDFLAGS += $(shell pkg-config --static --libs glfw3)

SRCFILES = $(wildcard $(SRCDIR)/*.c)
DBGOBJFILES = $(patsubst $(SRCDIR)/%, debug/%, $(SRCFILES:.c=.o))
RELOBJFILES = $(patsubst $(SRCDIR)/%, release/%, $(SRCFILES:.c=.o))
STATICLIBS = CoreEngine.a PhysicsEngine.a RenderingEngine.a Base.a
DBGSTATICLIBS = $(patsubst %, lib/debug/%, $(STATICLIBS))
RELSTATICLIBS = $(patsubst %, lib/release/%, $(STATICLIBS))
BASELIBINCFILES = $(wildcard $(LIBINCDIR)/Base/*.h)
RENDERINGLIBINCFILES = $(wildcard $(LIBINCDIR)/RenderingEngine/*.h)
PHYSICSLIBINCFILES = $(wildcard $(LIBINCDIR)/PhysicsEngine/*.h)
CORELIBINCFILES = $(wildcard $(LIBINCDIR)/CoreEngine/*.h)

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
	$(CC) -o $@ $^ $(LDFLAGS)
release/$(FINAL): $(RELOBJFILES) $(RELSTATICLIBS)
	$(CC) -o $@ $^ $(LDFLAGS)

debug:
	mkdir -p debug
release:
	mkdir -p release

debug/%.o: $(SRCDIR)/%.c $(BASELIBINCFILES) $(RENDERINGLIBINCFILES) $(PHYSICSLIBINCFILES) $(CORELIBINCFILES)
	$(CC) -c -o $@ $< $(CFLAGS)
release/%.o: $(SRCDIR)/%.c $(BASELIBINCFILES) $(RENDERINGLIBINCFILES) $(PHYSICSLIBINCFILES) $(CORELIBINCFILES)
	$(CC) -c -o $@ $< $(CFLAGS)
