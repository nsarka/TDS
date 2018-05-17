IDIR=./include
CC=g++
CFLAGS=-Wall -g

ODIR=./src/obj
LDIR=./lib
BDIR=./bin

LIBS=-lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_net -lSDL2_ttf

MKDIR_P=mkdir -p

all: directories game

# Directories that need to exist (that are not in the repository) are created here
directories: $(ODIR) $(LDIR) $(BDIR)

$(ODIR):
	$(MKDIR_P) $(ODIR)

$(LDIR):
	$(MKDIR_P) $(LDIR)

$(BDIR):
	$(MKDIR_P) $(BDIR)
# End directories

# All header files that need to be compiled go here
_DEPS=timer.h player.h entity.h physics.h spritesheet.h text.h
DEPS=$(patsubst %,$(IDIR)/%,$(_DEPS))

# All object files (which correspond to compiled .c files, duh) go here
_OBJ=tds.o player.o timer.o physics.o spritesheet.o text.o
OBJ=$(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o:./src/%.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

game: $(OBJ)
	$(CC) -o ./bin/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean directories

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
