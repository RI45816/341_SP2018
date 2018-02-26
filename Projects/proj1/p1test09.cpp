// File: p1test08.cpp
//
// Large-scale and timing tests of SortedSquareList class
// Will work for reduced implementations, too.
//

#include <iostream>
#include <iomanip>
#include "SSLColumn.h"
#include "SortedSquareList.h"
#include <stdlib.h>
#include <sys/times.h>

using namespace std ;

#define NUM_TEST_ENTS  1000000
#define NUM_FINDS      2000000

// grading function used to examine private data members.
bool SSLColumn::inspect(int* &buf, int &cap, int &size, int &start, int &end) {
    buf = m_data;
    cap = m_capacity;
    size = m_size;
    start = m_start;
    end = m_end;
    return true;
}

bool SortedSquareList::inspect(SSLColumn** &buf, int &cap, int &size, int &start, int &end) {
    buf = m_cols;
    cap = m_capacity;
    size = m_size;
    start = m_start;
    end = m_end;
    return true;
}

void init_timing(void);
void start_timing(void);
void interval_timing(bool do_cumm = true);
void end_timing(void);

int main(int argc, char *argv[]) {
    int vals[NUM_TEST_ENTS];
    int i, j, p, val, pval, incr;
    SSLColumn **buf;
    int cap, size, start, end;
    int num_misses;
    int result;
    SortedSquareList ssl, ssl2;  // Test default constructor: should make 2x2
    SortedSquareList *ssl1p, *ssl2p, *ssl3p;

    init_timing();
    vals[0] = 0;
    for (i = 1; i < NUM_TEST_ENTS; i++) {
	p = rand() % (i + 1);
	if (p < i) {
	    int tmp = vals[p];
	    vals[p] = i;
	    vals[i] = tmp;
	}
	else {
	    vals[i] = i;
	}
    }

    //
    // Phase 1: add in all the generated values
    //
    cout << "Phase 1: Doing " << NUM_TEST_ENTS << " add()'s:\n";
    start_timing();

    for (i = 0; i < NUM_TEST_ENTS; i++) {
	ssl.add(vals[i]);
	if (i > 0 && i % (NUM_TEST_ENTS / 10) == 0) {
	    cout << "After adding " << i << ":\n";
	    interval_timing();
	}
    }
    cout << "Total for " << NUM_TEST_ENTS << " add()'s:\n";
    interval_timing();  // One last time

    cout << "ssl.size() = " << ssl.size()
	 << ", ssl.capacity() = " << ssl.capacity() << endl;
    ssl.inspect(buf, cap, size, start, end);
    cout << "buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start = " << start << ", end = " << end << endl;

    cout << "========================================================\n";
    //
    // Phase 2: remove all those values
    //
    cout << "Phase 2: Doing " << NUM_TEST_ENTS << " remove()'s:\n";
    start_timing();

    num_misses = 0;
    for (i = 0; i < NUM_TEST_ENTS; i++) {
	if (!ssl.remove(vals[i]))  num_misses++;
	if (i > 0 && i % (NUM_TEST_ENTS / 10) == 0) {
	    cout << "After removing " << i << ":\n";
	    interval_timing();
	}
    }
    cout << "Total for " << NUM_TEST_ENTS << " remove()'s:\n";
    interval_timing();  // One last time

    if (num_misses > 0) cout << num_misses << "ITEMS NOT REMOVED!?!\n";
    cout << "ssl.size() = " << ssl.size()
	 << ", ssl.capacity() = " << ssl.capacity() << endl;
    ssl.inspect(buf, cap, size, start, end);
    cout << "buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start = " << start << ", end = " << end << endl;

    cout << "========================================================\n";
    //
    // Now, add them all back in--should be faster for non-restricted
    // implementation, since ssl doesn't need to be grown
    //
    cout << "Phase 3: Doing " << NUM_TEST_ENTS << " re-add()'s:\n";
    start_timing();

    for (i = 0; i < NUM_TEST_ENTS; i++) {
	ssl.add(vals[i]);
	if (i > 0 && i % (NUM_TEST_ENTS / 10) == 0) {
	    cout << "After adding " << i << ":\n";
	    interval_timing();
	}
    }
    cout << "Total for " << NUM_TEST_ENTS << " add()'s:\n";
    interval_timing();  // One last time

    cout << "ssl.size() = " << ssl.size()
	 << ", ssl.capacity() = " << ssl.capacity() << endl;
    ssl.inspect(buf, cap, size, start, end);
    cout << "buf = " << buf << ", cap = " << cap << ", size = " << size
	 << ", start = " << start << ", end = " << end << endl;

    cout << "========================================================\n";
    //
    // Now, test find()
    //
    cout << "Phase 4: Doing " << NUM_FINDS << " find()/findAt()'s:\n";
    incr = 0;
    for (i = 0; i < NUM_TEST_ENTS; i++) {
	ssl2.add(vals[i]);
	if (i > 0 && i % (NUM_TEST_ENTS / 10) == 0) {
	    cout << "On SSL containing " << i << " vals:\n";
	    cout << "  find()'s: ";
	    num_misses = 0;
	    ++incr;
	    start_timing();
	    for (j = 0; j < NUM_FINDS; j++) {
		if (ssl2.find(vals[j % i]) == -1)  num_misses++;
	    }
	    interval_timing(false);
	    if (num_misses > 0) cout << num_misses << "ITEMS NOT FOUND!?!\n";

	    cout << "  findAt()'s: ";
	    num_misses = 0;
	    start_timing();
	    pval = -1;
	    for (j = 0; j < NUM_FINDS; j++) {
		val = ssl2.findAt(j % i);
		if (val < 0 || val >= NUM_TEST_ENTS || val <= pval)  num_misses++;
	    }
	    interval_timing(false);
	    if (num_misses > 0) cout << num_misses << "OUT-OF-ORDER VALUES RETURNED!?!\n";
	}
    }

    cout << "========================================================\n";
    //
    // Now, test final data layout
    //
    cout << "Final data verification test:" << endl;
    cout << "SSL 1:" << endl;
    num_misses = 0;
    for (i = 0; i < NUM_TEST_ENTS; i++) {
	val = ssl.findAt(i);
	if (val != i) {
	    if (++num_misses <= 100)
		cout << "BAD: findAt(" << i << ") returned " << val << endl;
	}
	p = ssl.find(i);
	if (p != i) {
	    if (++num_misses <= 100)
		cout << "ERR in find(" << i << "): returned bad pos " << p <<
		endl;
	}
    }
    cout << "Total errors for SSL 1: " << num_misses << endl;

    cout << "SSL 2:" << endl;
    num_misses = 0;
    for (i = 0; i < NUM_TEST_ENTS; i++) {
	val = ssl2.findAt(i);
	if (val != i) {
	    if (++num_misses <= 100)
		cout << "BAD: findAt(" << i << ") returned " << val << endl;
	}
	p = ssl2.find(i);
	if (p != i) {
	    if (++num_misses <= 100)
		cout << "ERR in find(" << i << "): returned bad pos " << p <<
		endl;
	}
    }
    cout << "Total errors for SSL2: " << num_misses << endl;

    return 0;
}

static clock_t ticks_per_sec;
static struct tms startTime, midTime, endTime;

void init_timing(void) {
    ticks_per_sec = sysconf(_SC_CLK_TCK);
}

inline void output_times(struct tms *start, struct tms *end) {
    cout << "user time = " << setprecision(6)
	 << ((end->tms_utime - start->tms_utime) / (double) ticks_per_sec)
	 << ", sys time = " << setprecision(6)
	 << ((end->tms_stime - start->tms_stime) / (double) ticks_per_sec)
	 << endl;
}

void start_timing(void) {
    times(&startTime);
    midTime = startTime;
}

void interval_timing(bool do_cumm) {
    times(&endTime);
    cout << "  Interval: ";
    output_times(&midTime, &endTime);
    if (do_cumm) {
	cout << "  Cummulative: ";
	output_times(&startTime, &endTime);
    }
    midTime = endTime;
}

void end_timing(void) {
    times(&endTime);
    cout << "Final cummulative: ";
    output_times(&startTime, &endTime);
    startTime = midTime = endTime;
}
