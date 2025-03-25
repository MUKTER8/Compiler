import re

# Function to process input and check the regular expressions


def process_input(patterns, test_strings):
    results = []

    # Iterate through each test string
    for test_string in test_strings:
        match_found = False

        # Check each pattern against the test string
        for i, pattern in enumerate(patterns):
            try:
                # Compile the regular expression
                regex = re.compile(pattern)
                # Check if the string matches the pattern
                # fullmatch ensures the entire string matches
                if regex.fullmatch(test_string):
                    results.append(f"YES, {i + 1}")
                    match_found = True
                    break  # If a match is found, break out of the loop
            except re.error:
                continue  # If regex fails, continue with the next pattern

        # If no pattern matched, output NO, 0
        if not match_found:
            results.append("NO, 0")

    # Print all results with 'Output:' before the results
    print("Output:")
    for result in results:
        print(result)

# Function to handle the program start/stop logic


def program_start_stop():
    while True:
        user_choice = input(
            "Press 1: Program start or 2: Program stop: ").strip()

        if user_choice == '1':
            # Start the program
            print("How many regular expressions (RE) would you like to input?")
            num_patterns = int(input())  # Number of patterns (3 patterns)
            patterns = []

            print(f"Please enter {num_patterns} regular expressions.")
            # Get the regular expressions
            for _ in range(num_patterns):
                pattern = input().strip()
                patterns.append(pattern)

            print("How many grammar strings would you like to check?")
            num_grammar = int(input())  # Number of grammar strings
            test_strings = []

            print(
                f"Please enter {num_grammar} grammar strings to check against the regular expressions.")
            # Get the grammar strings
            for _ in range(num_grammar):
                test_string = input().strip()
                test_strings.append(test_string)

            # Process the input with the patterns and test strings
            process_input(patterns, test_strings)

        elif user_choice == '2':
            print("Program stopped.")
            break  # Stop the loop and exit the program
        else:
            print("Invalid input. Please press 1 to start or 2 to stop.")


# Call the function to start the program
program_start_stop()
