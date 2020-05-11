# Test file for "Lab7_LCDScreen"


# commands.gdb provides the following functions for ease:
#   test "<message>"
#       Where <message> is the message to print. Must call this at the beginning of every test
#       Example: test "PINA: 0x00 => expect PORTC: 0x01"
#   checkResult
#       Verify if the test passed or failed. Prints "passed." or "failed." accordingly, 
#       Must call this at the end of every test.
#   expectPORTx <val>
#       With x as the port (A,B,C,D)
#       The value the port is epected to have. If not it will print the erroneous actual value
#   setPINx <val>
#       With x as the port or pin (A,B,C,D)
#       The value to set the pin to (can be decimal or hexidecimal
#       Example: setPINA 0x01
#   printPORTx f OR printPINx f 
#       With x as the port or pin (A,B,C,D)
#       With f as a format option which can be: [d] decimal, [x] hexadecmial (default), [t] binary 
#       Example: printPORTC d
#   printDDRx
#       With x as the DDR (A,B,C,D)
#       Example: printDDRB

echo ======================================================\n
echo Running all tests..."\n\n

test "PINA: 0xFF => LED: 0x00"
setPINA 0xFF
timeContinue
expect LED 0x00
expect state Wait_Press
checkResult

test "PINA: 0xFE => LED: 0x01"
setPINA 0xFE
timeContinue
expect LED 0x01
expect state Increment
checkResult

test "PINA: 0xFE (wait 1500 ms) => LED: 0x01"
setPINA 0xFE
timeContinue 15
expect LED 0x02
expect state Increment
checkResult

test "PINA: 0xFD => LED: 0x01"
setPINA 0xFD
timeContinue
expect LED 0x01
expect state Decrement
checkResult


# Report on how many tests passed/tests ran
set $passed=$tests-$failed
eval "shell echo Passed %d/%d tests.\n",$passed,$tests
echo ======================================================\n
