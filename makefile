BUILDDIR = build/
INCLUDE = -Iinclude/
SRCDIR = src/
TESTDIR = test/
LIBDIR = lib/
LIBS =
OBJS = $(addprefix $(BUILDDIR)/, World.o ResourceManager.o RenderSystem.o EntityGroup.o)
HEADERS = $(addprefix include/, $(addsuffix .hpp, ResourceManager World Entity/EntityFactory Entity/EntityGroup System/SystemManager EventManager))
TESTOBJS = $(BUILDDIR)/test.o
CXX = g++
CFLAGS = -fPIC -c $(INCLUDE) -std=c++17
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

$(TESTDIR)/test: $(TESTOBJS) $(OBJS)
	$(CXX) $(TESTOBJS) $(OBJS) $(LFLAGS) -o $(TESTDIR)/test

$(BUILDDIR)/test.o: test/test.cpp $(HEADERS)
	$(CXX) $(CFLAGS) test/test.cpp -o $(BUILDDIR)/test.o

$(BUILDDIR)/ResourceManager.o: $(SRCDIR)/ResourceManager.cpp include/ResourceManager.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/ResourceManager.cpp -o $(BUILDDIR)/ResourceManager.o

$(BUILDDIR)/World.o: $(SRCDIR)/World.cpp include/World.hpp include/EventManager.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/World.cpp -o $(BUILDDIR)/World.o

$(BUILDDIR)/EntityGroup.o: $(SRCDIR)/Entity/EntityGroup.cpp include/Entity/EntityGroup.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Entity/EntityGroup.cpp -o $(BUILDDIR)/EntityGroup.o

$(BUILDDIR)/RenderSystem.o: $(SRCDIR)/System/Render/RenderSystem.cpp include/System/Render/RenderSystem.hpp \
	include/System/System.hpp include/EventManager.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/System/Render/RenderSystem.cpp -o $(BUILDDIR)/RenderSystem.o

clean:
	rm $(OBJS) $(TESTOBJS) $(TESTDIR)/test

test: $(TESTDIR)/test
	$(TESTDIR)/test
