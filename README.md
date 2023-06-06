# Game description

Reaction Time game, when the game is turned on, a random time is created and then after that random time occurs, a light either on the right or left side will turn on and the player will have to quickly push down the right or left button respectively.  The player then is scored on how quickly they pressed the button after it turned on.  If they don’t press the button a sour tone is played.

User inputs/outputs sheet
“switch button” – turns the game on or off
“led outputs” – led will turn on after random delay
“right button” – used to turn the right led off
“left button” – used to turn the left led off
“serial print output” – used to tell the player how long they took to press the button after the led came on
“speech output”  - speech output that tells the player how long & additionally Game on and off speech

Async delay count evbery 1 ms check if expired and then add up to count
Buttons are flags
If expired end, else keeps counting
Use stopwatch assignment

