#! /bin/bash
# regression suite for vis

PROG_NAME='bin/vis'
# warn: print a message on error on stderr and stdout
function warn() {
	echo "${1}" 2>&1
}

# test: check the expected output matches the actual output
function test() {
	case $# in
		3)
			local message="${1}"
			local actual="${2}"
			local expected="${3}"
			;;
		*)
			warn "test needs actual, expected output, and fail message"
			exit 1
			;;
	esac

	if [[ "${actual}" != "${expected}" ]]
	then
		warn "${message}"
		warn "Expected: ${expected}"
		warn "Actual: ${actual}"
		exit 2
	fi
}

# testing stdin
output=$(echo "This is another test containing longer words" | $PROG_NAME -s5)
test 'processing stdin filtering words of 5 or more characters' \
	"${output}" \
	'another containing longer words '

output=$(echo "This is a test containing longer words" | $PROG_NAME -s3)
test 'processing stdin filtering words of 3 or more characters' \
	"${output}" \
	'This test containing longer words '

output=$(echo "This is another test containing longer words" | $PROG_NAME)
test 'processing stdin with no arguments' \
	"${output}" \
	'This is another test containing longer words '

# testing with a file
trap 'rm -f /tmp/vis.test.$$' 1 2 15
echo "This is another test containing longer words" > /tmp/vis.test.$$
output=$($PROG_NAME -s5 /tmp/vis.test.$$)
test 'processing file filtering words of 5 or more characters' \
	"${output}" \
	'another containing longer words '

output=$($PROG_NAME -s3 /tmp/vis.test.$$)
test 'processing file filtering words of 3 or more characters' \
	"${output}" \
	'This another test containing longer words '

output=$($PROG_NAME /tmp/vis.test.$$)
test 'processing file with no arguments' \
	"${output}" \
	'This is another test containing longer words '

# testing invalid arguments
output=$($PROG_NAME -s 2>&1)
test 'processing minimum word length with no value' \
	"${output}" \
	'Usage: vis [-sX] [file1 ...]'

output=$($PROG_NAME - 2>&1)
test 'processing invalid filename' \
	"${output}" \
	'Unable to open file: -'

output=$($PROG_NAME - /tmp/vis.test.$$ 2>&1)
test 'processing invalid filename' \
	"${output}" \
	'Unable to open file: -
This is another test containing longer words '

rm -f /tmp/vis.test.$$
