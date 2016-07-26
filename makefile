BUILDDIR = build/
INCLUDEDIR = include/
SRCDIR = src/
BIN = bin
LIBDIR = lib/
LIBS =
OBJS = $(BUILDDIR)/Component.o $(BUILDDIR)/Entity.o $(BUILDDIR)/RenderComponent.o $(BUILDDIR)/System.o $(BUILDDIR)/RenderSystem.o
CXX = g++
CFLAGS = -fPIC -c -I$(INCLUDEDIR) -std=c++11
LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: $(OBJS)

$(BUILDDIR)/Component.o: $(SRCDIR)/Component/Component.cpp $(INCLUDEDIR)/GameEngine2D/Component/Component.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Component/Component.cpp -o $(BUILDDIR)/Component.o

$(BUILDDIR)/Entity.o: $(SRCDIR)/Entity/Entity.cpp $(INCLUDEDIR)/GameEngine2D/Entity/Entity.hpp $(INCLUDEDIR)/GameEngine2D/Component/Component.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Entity/Entity.cpp -o $(BUILDDIR)/Entity.o

$(BUILDDIR)/RenderComponent.o: $(SRCDIR)/Component/RenderComponent.cpp $(INCLUDEDIR)/GameEngine2D/Component/RenderComponent.hpp \
	$(INCLUDEDIR)/GameEngine2D/Component/Component.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/Component/RenderComponent.cpp -o $(BUILDDIR)/RenderComponent.o

$(BUILDDIR)/System.o: $(SRCDIR)/System/System.cpp $(INCLUDEDIR)/GameEngine2D/System/System.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/System/System.cpp -o $(BUILDDIR)/System.o

$(BUILDDIR)/RenderSystem.o: $(SRCDIR)/System/RenderSystem.cpp $(INCLUDEDIR)/GameEngine2D/System/RenderSystem.hpp \
	$(INCLUDEDIR)/GameEngine2D/Component/RenderComponent.hpp $(INCLUDEDIR)/GameEngine2D/System/System.hpp
	$(CXX) $(CFLAGS) $(SRCDIR)/System/RenderSystem.cpp -o $(BUILDDIR)/RenderSystem.o

clean:
	rm $(OBJS)
