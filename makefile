BUILDDIR = build/
INCLUDEDIR = include/
SRCDIR = src/
TESTDIR = test/
BIN = bin/
LIBDIR = lib/
LIBS =
OBJS = $(BUILDDIR)/Component.o $(BUILDDIR)/Entity.o $(BUILDDIR)/RenderComponent.o $(BUILDDIR)/RenderSystem.o $(BUILDDIR)/EntityManager.o $(BUILDDIR)/tester.o \
	$(BUILDDIR)/ResourceManager.o $(BUILDDIR)/System.o
CXX = g++
CFLAGS = -fPIC -c -I$(INCLUDEDIR) -std=c++11
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

$(BIN)/test: $(OBJS)
	$(CXX) $(OBJS) -o $(BIN)/test $(LFLAGS)

$(BUILDDIR)/tester.o: $(TESTDIR)/tester.cpp $(INCLUDEDIR)/GameEngine2D/EntityManager.hpp $(INCLUDEDIR)/GameEngine2D/Entity/Entity.hpp \
	$(INCLUDEDIR)/GameEngine2D/Component/Component.hpp $(INCLUDEDIR)/GameEngine2D/Component/RenderComponent.hpp $(INCLUDEDIR)/GameEngine2D/System/RenderSystem.hpp
	$(CXX) $(CFLAGS) $(TESTDIR)/tester.cpp -o $(BUILDDIR)/tester.o

$(BUILDDIR)/ResourceManager.o: $(SRCDIR)/ResourceManager.cpp $(INCLUDEDIR)/GameEngine2D/ResourceManager.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/ResourceManager.cpp -o $(BUILDDIR)/ResourceManager.o

$(BUILDDIR)/Component.o: $(SRCDIR)/Component/Component.cpp $(INCLUDEDIR)/GameEngine2D/Component/Component.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Component/Component.cpp -o $(BUILDDIR)/Component.o

$(BUILDDIR)/RenderComponent.o: $(SRCDIR)/Component/RenderComponent.cpp $(INCLUDEDIR)/GameEngine2D/Component/RenderComponent.hpp \
	$(INCLUDEDIR)/GameEngine2D/Component/Component.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Component/RenderComponent.cpp -o $(BUILDDIR)/RenderComponent.o

$(BUILDDIR)/Entity.o: $(SRCDIR)/Entity/Entity.cpp $(INCLUDEDIR)/GameEngine2D/Entity/Entity.hpp $(INCLUDEDIR)/GameEngine2D/Component/Component.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Entity/Entity.cpp -o $(BUILDDIR)/Entity.o

$(BUILDDIR)/EntityManager.o: $(SRCDIR)/EntityManager.cpp $(INCLUDEDIR)/GameEngine2D/EntityManager.hpp $(INCLUDEDIR)/GameEngine2D/Entity/Entity.hpp \
	$(INCLUDEDIR)/GameEngine2D/Component/Component.hpp $(INCLUDEDIR)/GameEngine2D/Component/RenderComponent.hpp $(INCLUDEDIR)/GameEngine2D/System/RenderSystem.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/EntityManager.cpp -o $(BUILDDIR)/EntityManager.o

$(BUILDDIR)/System.o: $(SRCDIR)/System/System.cpp $(INCLUDEDIR)/GameEngine2D/System/System.hpp $(INCLUDEDIR)/GameEngine2D/Component/Component.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/System/System.cpp -o $(BUILDDIR)/System.o

$(BUILDDIR)/RenderSystem.o: $(SRCDIR)/System/RenderSystem.cpp $(INCLUDEDIR)/GameEngine2D/System/RenderSystem.hpp \
	$(INCLUDEDIR)/GameEngine2D/Component/RenderComponent.hpp $(INCLUDEDIR)/GameEngine2D/System/System.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/System/RenderSystem.cpp -o $(BUILDDIR)/RenderSystem.o

clean:
	rm $(OBJS)
