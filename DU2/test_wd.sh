#!/usr/bin/env bash

echo "Testing wordcount on Shakespeare:"
# Compare wordcount and wordcount-cc outputs
./wordcount < shake.txt | sort > a
./wordcount-cc < shake.txt | sort > b

if diff a b > /dev/null; then
    echo "wordcount vs wordcount-cc: successful tests"
else
    echo "wordcount vs wordcount-cc: failed test"
fi
rm a b

# Compare wordcount-dynamic and wordcount-cc outputs
./wordcount-dynamic < shake.txt | sort > a
./wordcount-cc < shake.txt | sort > b

if diff a b > /dev/null; then
    echo "wordcount-dynamic vs wordcount-cc: successful tests"
else
    echo "wordcount-dynamic vs wordcount-cc: failed test"
fi
rm a b

# Test tail functionality
echo "Testing tail functionality:"

# Compare your tail with the system tail
./tail < shake.txt > my_tail_output.txt
tail < shake.txt > system_tail_output.txt

if diff my_tail_output.txt system_tail_output.txt > /dev/null; then
    echo "Your tail vs system tail: successful tests"
else
    echo "Your tail vs system tail: failed test"
fi

echo "Testing wordcout:"
# Generating a shuffled sequence of numbers for testing
seq 1000000 2000000 | shuf > test.txt

# Comparing wordcount implementations on a large, shuffled input
./wordcount-cc < test.txt | sort > a
./wordcount < test.txt | sort > b
./wordcount-dynamic < test.txt | sort > c

if diff a b > /dev/null; then
    echo "wordcount-cc vs wordcount: successful tests"
else
    echo "wordcount-cc vs wordcount: failed test"
fi

if diff a c > /dev/null; then
    echo "wordcount-cc vs wordcount-dynamic: successful tests"
else
    echo "wordcount-cc vs wordcount-dynamic: failed test"
fi

# Cleanup
rm test.txt a b c my_tail_output.txt system_tail_output.txt
