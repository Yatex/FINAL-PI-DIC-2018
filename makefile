COMPILER= gcc
OUTPUT_FILE=Run
FILES= Airport.c Flights.c OpenFiles.c Main.c

all:
	$(COMPILER) -o $(OUTPUT_FILE) $(FILES)
clean:
	rm ./$(OUTPUT_FILE)
