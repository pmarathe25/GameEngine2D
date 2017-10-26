BUILDDIR = build/
INCLUDE = -Iinclude/
SRCDIR = src/
TESTDIR = test/
LIBDIR = lib/
LIBS =
OBJS = $(addprefix $(BUILDDIR)/, World.o ResourceManager.o StaticRenderSystem.o DynamicRenderSystem.o)
TESTOBJS = $(BUILDDIR)/test.o
CXX = g++
CFLAGS = -fPIC -c $(INCLUDE) -std=c++17
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

$(TESTDIR)/test: $(TESTOBJS) $(OBJS)
	$(CXX) $(TESTOBJS) $(OBJS) $(LFLAGS) -o $(TESTDIR)/test

$(BUILDDIR)/test.o: test/test.cpp include/ResourceManager.hpp include/World.hpp include/Entity/EntityFactory.hpp \
	include/System/SystemManager.hpp include/EventManager.hpp
	$(CXX) $(CFLAGS) test/test.cpp -o $(BUILDDIR)/test.o

$(BUILDDIR)/ResourceManager.o: $(SRCDIR)/ResourceManager.cpp include/ResourceManager.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/ResourceManager.cpp -o $(BUILDDIR)/ResourceManager.o

$(BUILDDIR)/World.o: $(SRCDIR)/World.cpp include/World.hpp include/EventManager.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/World.cpp -o $(BUILDDIR)/World.o

$(BUILDDIR)/StaticRenderSystem.o: $(SRCDIR)/System/Render/StaticRenderSystem.cpp include/System/Render/StaticRenderSystem.hpp \
	include/System/System.hpp include/EventManager.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/System/Render/StaticRenderSystem.cpp -o $(BUILDDIR)/StaticRenderSystem.o

$(BUILDDIR)/DynamicRenderSystem.o: $(SRCDIR)/System/Render/DynamicRenderSystem.cpp include/System/Render/DynamicRenderSystem.hpp \
	include/System/Render/StaticRenderSystem.hpp include/EventManager.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/System/Render/DynamicRenderSystem.cpp -o $(BUILDDIR)/DynamicRenderSystem.o

clean:
	rm $(OBJS) $(TESTOBJS) $(TESTDIR)/test

test: $(TESTDIR)/test
	$(TESTDIR)/test
