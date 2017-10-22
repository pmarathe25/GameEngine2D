BUILDDIR = build/
INCLUDE = -Iinclude/
SRCDIR = src/
TESTDIR = test/
LIBDIR = lib/
LIBS =
OBJS = $(addprefix $(BUILDDIR)/, TransformSystem.o StaticRenderSystem.o)
TESTOBJS = $(BUILDDIR)/test.o
CXX = g++
CFLAGS = -fPIC -c $(INCLUDE) -std=c++17
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

$(TESTDIR)/test: $(TESTOBJS) $(OBJS)
	$(CXX) $(TESTOBJS) $(OBJS) $(LFLAGS) -o $(TESTDIR)/test

$(BUILDDIR)/test.o: test/test.cpp include/ResourceManager.hpp
	$(CXX) $(CFLAGS) test/test.cpp -o $(BUILDDIR)/test.o

$(BUILDDIR)/TransformSystem.o: $(SRCDIR)/System/TransformSystem.cpp include/System/TransformSystem.hpp include/System/System.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/System/TransformSystem.cpp -o $(BUILDDIR)/TransformSystem.o

$(BUILDDIR)/StaticRenderSystem.o: $(SRCDIR)/System/StaticRenderSystem.cpp include/System/StaticRenderSystem.hpp include/System/System.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/System/StaticRenderSystem.cpp -o $(BUILDDIR)/StaticRenderSystem.o

clean:
	rm $(OBJS) $(TESTOBJS) $(TESTDIR)/test

test: $(TESTDIR)/test
	$(TESTDIR)/test
