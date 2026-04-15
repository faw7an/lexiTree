#!/bin/bash
SENTENCES=(
"The boy runs"
"A girl reads a book"
"Dogs chase cats"
"She eats an apple"
"They are playing football"
"The tall boy quickly runs to the small house"
"A very intelligent student solved the problem easily"
"The dog under the table is barking loudly"
"She carefully placed the glass on the wooden shelf"
"The old man with a long beard walks slowly"
"The boy runs and the girl walks"
"She was tired but she continued working"
"I went home because it was raining heavily"
"Although he was late he still attended the meeting"
"The teacher explained the lesson while the students listened carefully"
"John said that he would come later"
"Mary gave her book to Jane because she trusted her"
"The boy saw the dog and it barked at him"
"When Ahmed met Ali he smiled"
"Sarah told her sister that she should study harder"
"The man who was sitting near the window is my uncle"
"The book that the teacher who I met yesterday recommended is interesting"
"The student who solved the problem that the professor gave is brilliant"
"I know the person who knows the person who built this house"
"The cat that chased the mouse that stole the cheese ran away"
"The boy who was wearing a red shirt and black shoes was running quickly across the field while his friends were shouting loudly"
"Although the weather was extremely cold and the roads were covered with ice the driver continued his journey because he had an important meeting to attend"
"The teacher who had been working at the school for more than twenty years decided to retire after she realized that she wanted to spend more time with her family"
"The software engineer who designed the system that processes user requests in real time explained how it works during the conference"
"The student who forgot to submit the assignment that the professor had given last week tried to explain the situation but the professor refused to accept the excuse"
"Visiting relatives can be annoying"
"I saw the man with a telescope"
"Flying planes can be dangerous"
"The chicken is ready to eat"
"Old men and women were sitting quietly"
"The boy the girl and the teacher went to the market"
"She bought apples oranges bananas and grapes"
"The system stores names addresses phone numbers and email accounts"
"He likes reading books watching movies and playing games"
"The manager hired engineers designers and analysts who were highly skilled"
"The boy who said that he would come did not show up which made everyone angry"
"If the student who you recommended passes the exam then the teacher who taught him will be proud"
"The developer who wrote the code that fixed the bug said that it was harder than he expected"
"When the manager who leads the team that builds the application arrives we will start the meeting"
"The scientist who discovered the method that improves performance explained why it works and how it can be applied"
"The boy who the teacher who the principal hired last year praised during the ceremony is my neighbor"
"The system that the engineer who the company hired recently designed processes data that users who are registered in the platform submit daily"
"Although the student who forgot that he had an exam tried to study quickly he realized that the material that the professor had taught was too complex to understand in a short time"
)

for s in "${SENTENCES[@]}"; do
    echo -n "Testing: $s ... "
    ./english-parser "$s" --top-down > /dev/null 2>&1
    TD=$?
    ./english-parser "$s" --bottom-up > /dev/null 2>&1
    BU=$?
    if [ $TD -eq 0 ] && [ $BU -eq 0 ]; then echo "BOTH PASS";
    elif [ $TD -eq 0 ]; then echo "ONLY TD PASS";
    elif [ $BU -eq 0 ]; then echo "ONLY BU PASS";
    else echo "BOTH FAIL"; fi
done
