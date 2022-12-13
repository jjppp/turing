; This program right shifts the input string cyclically.

; Input : a string of 0's and 1's, e.g. '10001'.

; Output: cyclically right shifted input string, e.g. '11000'. 

#Q = {start,read0,read1,toLeftMostRead0,toLeftMostRead1,done}

#S = {0,1}

#G = {0,1,_}

#q0 = start

#B = _

#F = {done}

#N = 1

start 0 _ r read0
start 1 _ r read1

read0 0 0 r read0
read0 1 0 r read1
read0 _ _ l toLeftMostRead0

read1 0 1 r read0
read1 1 1 r read1
read1 _ _ l toLeftMostRead1

toLeftMostRead0 0 0 l toLeftMostRead0
toLeftMostRead0 1 1 l toLeftMostRead0
toLeftMostRead0 _ 0 * done

toLeftMostRead1 0 0 l toLeftMostRead1
toLeftMostRead1 1 1 l toLeftMostRead1
toLeftMostRead1 _ 1 * done
