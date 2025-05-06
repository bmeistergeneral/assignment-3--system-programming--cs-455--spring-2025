CC = gcc
CFLAGS = -Wall -g

CAT_FILENAME = 01--cat-using-read-write-open-and-close
COMPARE_FILENAME = 02--compare-two-files-and-print-first-line-where-they-differ

all: $(CAT_FILENAME) $(COMPARE_FILENAME)

$(CAT_FILENAME): $(CAT_FILENAME).c
	$(CC) $(CFLAGS) $(CAT_FILENAME).c -o $(CAT_FILENAME)

$(COMPARE_FILENAME): $(COMPARE_FILENAME).c
	$(CC) $(CFLAGS) $(COMPARE_FILENAME).c -o $(COMPARE_FILENAME)

run_cat: $(CAT_FILENAME)
	./$(CAT_FILENAME)

run_compare: $(COMPARE_FILENAME)
	./$(COMPARE_FILENAME) file1.txt file2.txt

clean:
	rm -fr $(CAT_FILENAME) $(COMPARE_FILENAME) *.dSYM
