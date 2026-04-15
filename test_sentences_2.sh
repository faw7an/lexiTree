#!/bin/bash
sentences=(
    "the two smart students passed"
    "the beautiful old clock is ticking"
    "the following school term is long"
    "running water destroyed the old bridge"
    "three large files are downloading"
    "we will have been waiting"
    "they have to do the final exams"
    "the teacher wants to give the students good grades"
    "you should be giving the children food"
    "she placed her phone on the white charger at the small hall during break time"
    "the brave men walked to the dark forest very slowly today"
    "the cat jumped over the fence into the yard quickly"
    "can the smart programmer build a computer"
    "why do all the people want to hide"
    "look at the tall building"
    "you will be available, won't you"
    "the school bus has arrived, hasn't it"
    "although the heavy rain fell the students went to the school"
    "we will come this christmas, however the circumstance"
    "you should watch attack on titan it is the best show"
    "the young boy is very happy"
    "hello, the two students will have been studying the following school lessons at the hotel library very carefully, won't they"
    "why did the three brave soldiers have to run through the dark forest very quickly"
    "although you were late you did your homework correctly you are a good student"
    "listen to me, we have to find the missing keys in the empty room before the sun sets"
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
