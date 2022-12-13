; This example program checks if the input string is a binary palindrome.
; Input: a string of 0's and 1's, e.g. '1001001'

; the finite set of states
#Q = {
    scanL, 
    scanR, 
    compare, 
        readA, readAskipC,
        readB, readBskipC,
    matchskipC,
    skipAB,
    checkDone,
    allC,
    accept
}


; the finite set of input symbols
#S = {a, b, c}

; the complete set of tape symbols
#G = {a, b, c, _}

; the start state
#q0 = scanL 

; the blank symbol
#B = _

; the set of final states
#F = {accept}

; the number of tapes
#N = 1

; the transition functions

scanL a a r scanL
scanL b b r scanL
scanL c c r scanR

scanR a a r scanR
scanR b b r scanR
scanR _ c l compare
compare c c * checkDone

compare a c l readA 
readA a a l readA 
readA b b l readA 
readA c c l readAskipC 
readAskipC c c l readAskipC 
readAskipC a c * matchskipC 
; readAskipC _ _ r checkDone 

compare b c l readB 
readB a a l readB 
readB b b l readB 
readB c c l readBskipC 
readBskipC c c l readBskipC 
readBskipC b c * matchskipC 
; readBskipC _ _ r checkDone 

matchskipC c c r matchskipC 
matchskipC a a r skipAB 
matchskipC b b r skipAB 
matchskipC _ _ l checkDone 

skipAB a a r skipAB 
skipAB b b r skipAB 
skipAB c c l compare

checkDone a a l checkDone 
checkDone b b l checkDone 
checkDone c c l checkDone 
checkDone _ _ r allC 

allC c c r allC 
allC _ _ * accept 
