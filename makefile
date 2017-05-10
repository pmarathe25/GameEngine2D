BUILDDIR = build/
INCLUDEDIR = include/
SRCDIR = src/
TESTDIR = test/
LIBDIR = lib/
LIBS =
OBJS = $(BUILDDIR)/Component.o $(BUILDDIR)/EntityManager.o $(BUILDDIR)/Entity.o $(BUILDDIR)/ResourceManager.o \
 	$(BUILDDIR)/RenderComponent.o $(BUILDDIR)/RenderSystem.o $(BUILDDIR)/PhysicsComponent.o $(BUILDDIR)/PhysicsSystem.o
TESTOBJS =  $(BUILDDIR)/tester.o
CXX = g++
CFLAGS = -fPIC -c -I$(INCLUDEDIR) -std=c++11
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

$(TESTDIR)/test: $(OBJS) $(TESTOBJS)
	$(CXX) $(OBJS) $(TESTOBJS) -o $(TESTDIR)/test $(LFLAGS)

$(BUILDDIR)/tester.o: $(TESTDIR)/tester.cpp $(INCLUDEDIR)/GameEngine2D/Entity/EntityManager.hpp $(INCLUDEDIR)/GameEngine2D/Entity/Entity.hpp \
	$(INCLUDEDIR)/GameEngine2D/Component/Component.hpp $(INCLUDEDIR)/GameEngine2D/Component/RenderComponent.hpp $(INCLUDEDIR)/GameEngine2D/System/RenderSystem.hpp
	$(CXX) $(CFLAGS) $(TESTDIR)/tester.cpp -o $(BUILDDIR)/tester.o

$(BUILDDIR)/Component.o: $(SRCDIR)/Component/Component.cpp $(INCLUDEDIR)/GameEngine2D/Component/Component.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Component/Component.cpp -o $(BUILDDIR)/Component.o

$(BUILDDIR)/EntityManager.o: $(SRCDIR)/Entity/EntityManager.cpp $(INCLUDEDIR)/GameEngine2D/Entity/EntityManager.hpp $(INCLUDEDIR)/GameEngine2D/Entity/Entity.hpp \
	$(INCLUDEDIR)/GameEngine2D/Component/Component.hpp $(INCLUDEDIR)/GameEngine2D/Component/RenderComponent.hpp $(INCLUDEDIR)/GameEngine2D/System/RenderSystem.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Entity/EntityManager.cpp -o $(BUILDDIR)/EntityManager.o

$(BUILDDIR)/Entity.o: $(SRCDIR)/Entity/Entity.cpp $(INCLUDEDIR)/GameEngine2D/Entity/Entity.hpp $(INCLUDEDIR)/GameEngine2D/Component/Component.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Entity/Entity.cpp -o $(BUILDDIR)/Entity.o

$(BUILDDIR)/ResourceManager.o: $(SRCDIR)/ResourceManager.cpp $(INCLUDEDIR)/GameEngine2D/ResourceManager.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/ResourceManager.cpp -o $(BUILDDIR)/ResourceManager.o

$(BUILDDIR)/RenderComponent.o: $(SRCDIR)/Component/RenderComponent.cpp $(INCLUDEDIR)/GameEngine2D/Component/RenderComponent.hpp \
	$(INCLUDEDIR)/GameEngine2D/Component/Component.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Component/RenderComponent.cpp -o $(BUILDDIR)/RenderComponent.o

$(BUILDDIR)/RenderSystem.o: $(SRCDIR)/System/RenderSystem.cpp $(INCLUDEDIR)/GameEngine2D/System/RenderSystem.hpp \
	$(INCLUDEDIR)/GameEngine2D/Component/RenderComponent.hpp $(INCLUDEDIR)/GameEngine2D/System/System.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/System/RenderSystem.cpp -o $(BUILDDIR)/RenderSystem.o

$(BUILDDIR)/PhysicsComponent.o: $(SRCDIR)/Component/PhysicsComponent.cpp $(INCLUDEDIR)/GameEngine2D/Component/PhysicsComponent.hpp \
	$(INCLUDEDIR)/GameEngine2D/Component/Component.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Component/PhysicsComponent.cpp -o $(BUILDDIR)/PhysicsComponent.o

$(BUILDDIR)/PhysicsSystem.o: $(SRCDIR)/System/PhysicsSystem.cpp $(INCLUDEDIR)/GameEngine2D/System/PhysicsSystem.hpp \
	$(INCLUDEDIR)/GameEngine2D/Component/PhysicsComponent.hpp $(INCLUDEDIR)/GameEngine2D/System/System.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/System/PhysicsSystem.cpp -o $(BUILDDIR)/PhysicsSystem.o

clean:
	rm $(OBJS)

test: $(TESTDIR)/test
	$(TESTDIR)/test
