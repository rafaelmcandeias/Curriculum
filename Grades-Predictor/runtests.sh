#!/bin/bash

# Loop through all .in files in ./tests directory
for input_file in ./tests/*.in; do
    # Extract the test number (e.g., T01 from T01.in)
    test_name=$(basename "$input_file" .in)

    # Run the main program with the input file
    ./main < "$input_file" > temp_output.txt

    # Compare the program output with the expected output
    if diff -q temp_output.txt "./tests/$test_name.out" > /dev/null; then
        # If the outputs match, print "PASSED" in green
        echo -e "\033[32mPASSED $test_name\033[0m"
    else
        # If the outputs do not match, print "FAILED" in red
        echo -e "\033[31mFAILED $test_name\033[0m"
    fi
done

# Clean up temporary output file
rm temp_output.txt
