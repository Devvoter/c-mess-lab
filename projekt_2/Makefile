CC = gcc
#STATISTICS=-DSTATISTICS  # pokud chcete statistic + pokud mate maly text tak musite zmnenit v wordcount.c na radku 20 pocet na init
STATISTICS=            		# pokud ne - nechat prazdny
HASH_FUN=-DSDBM_HASH_FUN_ # Dve moznosti pro hash funkce: -DDJB2_HASH_FUN_ nebo -DSDBM_HASH_FUN_
CFLAGS=-Wall -std=c11 -pedantic -Wextra $(STATISTICS) $(HASH_FUN)
LDFLAGS = -L.
LDLIBS = -lhtab
SRC = htab_init.c htab_lookup_add.c htab_free.c htab_clear.c htab_hash_function.c htab_erase.c htab_find.c htab_for_each.c htab_bucket_count.c htab_statistics.c
OBJ = $(SRC:.c=.o)
PROGRAMS = tail wordcount wordcount-dynamic

.PHONY: all clean

all: $(PROGRAMS) libhtab.a libhtab.so

# Cil pro program tail
tail:
	$(CC) $(CFLAGS) -o $@ tail.c

# Staticka knihovna
libhtab.a: $(OBJ)
	ar rcs $@ $^

# Dynamicka knihovna
libhtab.so: $(OBJ)
	$(CC) -shared -o $@ $^

# Staticky sestaveny program wordcount
wordcount: wordcount.o libhtab.a
	$(CC) $(CFLAGS) -static -o $@ wordcount.o $(LDFLAGS) -lhtab

# Dynamicky sestaveny program wordcount-dynamic
wordcount-dynamic: wordcount.o libhtab.so
	$(CC) $(CFLAGS) -o $@ wordcount.o $(LDFLAGS) -lhtab

# Pridani souboru io.c
io.o: io.c
	$(CC) $(CFLAGS) -c -o $@ $^

# Obecna pravidla pro sestaveni .o souboru z .c
%.o: %.c
	$(CC) $(CFLAGS) -fPIC -c $< -o $@

clean:
	rm -f $(PROGRAMS) *.o *.a *.so

# Pro dynamickou knihovnu v Linuxu
export LD_LIBRARY_PATH=.
run: all
	./wordcount
	./wordcount-dynamic
