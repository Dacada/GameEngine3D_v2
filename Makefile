.PHONY: all rel dbg clean

all: rel

rel:
	$(MAKE) -C RenderingEngine rel
	$(MAKE) -C PhysicsEngine rel
	$(MAKE) -C CoreEngine rel
	$(MAKE) -C Main rel

dbg:
	$(MAKE) -C RenderingEngine dbg
	$(MAKE) -C PhysicsEngine dbg
	$(MAKE) -C CoreEngine dbg
	$(MAKE) -C Main dbg

clean:
	$(MAKE) -C Main clean
	$(MAKE) -C CoreEngine clean
	$(MAKE) -C PhysicsEngine clean
	$(MAKE) -C RenderingEngine clean

