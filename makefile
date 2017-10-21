BUILDDIR = build/
INCLUDEDIR = include/
SRCDIR = src/
TESTDIR = test/
LIBDIR = lib/
LIBS =
OBJS = $(addprefix $(BUILDDIR)/, Component.o EntityManager.o Entity.o ResourceManager.o RenderComponent.o \
		RenderSystem.o PhysicsComponent.o PhysicsSystem.o CollisionComponent.o)
TESTOBJS = $(BUILDDIR)/tester.o
CXX = g++
CFLAGS = -fPIC -c -I$(INCLUDEDIR) -std=c++17
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

clean:
	rm $(OBJS) $(TESTDIR)/test

test: $(TESTDIR)/test
	$(TESTDIR)/test
