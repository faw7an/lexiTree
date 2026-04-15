#!/bin/bash
sentences=(
    "hello"
    "hello world again"
    "hi, my name is fauzan"
    "come back"
    "is that a cat"
    "why do we have to do exams"
    "you will be available, won't you"
    "the two students went to the hotel"
    "the following school time is long"
    "we will be having dinner soon"
    "we have to do the exams this week"
    "she placed her phone on the white charger at the small hall during break time"
    "although, you were late you did your homework correctly"
    "you should watch attack on titan it is the best show of all time"
    "10 - 2 + 5 * ( 3 + 4 )"
)

for s in "${sentences[@]}"; do
    echo "----------------------------------------"
    echo "Testing: $s"
    
    td_out=$(./parser_test "$s" 2>&1)
    if [ $? -eq 0 ]; then
        echo "[✓] Top-Down"
    else
        echo "[x] Top-Down FAILED"
    fi
    
    bu_out=$(./parser_test --bottom-up "$s" 2>&1)
    if [ $? -eq 0 ]; then
        echo "[✓] Bottom-Up"
    else
        echo "[x] Bottom-Up FAILED"
    fi
done
