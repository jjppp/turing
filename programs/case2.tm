; This program decides whether the input string is a perfect square.

; Input : a string of 1's, e.g. '1111' represents 4.

; Output: 'true' if n is perfect square, 'false' otherwise.

#Q = {done}

#S = {1}

; t is a counter
; s = t * t = sum(range(1, t * 2, 2))
#G = {1,t,r,u,e,f,a,l,s,_}

#q0 = check_skipIS

#B = _

#F = {dummy}

#N = 1

check_skipIS t t r check_skipIS
check_skipIS s s r check_skipIS
check_skipIS 1 1 l check_rollBack
check_skipIS _ _ l p_True

check_rollBack 1 1 l check_rollBack
check_rollBack t t l check_rollBack
check_rollBack s s l check_rollBack
check_rollBack _ _ r add_S1

add_S1 t u r add_S1_inc_S
add_S1 s s * inc_S
add_S1 1 1 * inc_S

add_S1_inc_S t t r add_S1_inc_S
add_S1_inc_S u u r add_S1_inc_S
add_S1_inc_S s s r add_S1_inc_S
add_S1_inc_S _ _ l p_False
add_S1_inc_S 1 s * add_S1_inc_S_rollBack

add_S1_inc_S_rollBack s s l add_S1_inc_S_rollBack
add_S1_inc_S_rollBack t t l add_S1_inc_S_rollBack
add_S1_inc_S_rollBack u u r add_S1

inc_S s s r inc_S
inc_S 1 s * inc_S_rollBack
inc_S _ _ l p_False

inc_S_rollBack s s l inc_S_rollBack
inc_S_rollBack u u * add_S2
inc_S_rollBack _ _ * add_S2

add_S2 u t r add_S2_inc_S
add_S2 _ _ r inc_counter

add_S2_inc_S t t r add_S2_inc_S
add_S2_inc_S s s r add_S2_inc_S
add_S2_inc_S _ _ l p_False
add_S2_inc_S 1 s * add_S2_inc_S_rollBack

add_S2_inc_S_rollBack s s l add_S2_inc_S_rollBack
add_S2_inc_S_rollBack t t l add_S2_inc_S_rollBack
add_S2_inc_S_rollBack u u * add_S2
add_S2_inc_S_rollBack _ _ * add_S2

inc_counter t t r inc_counter
inc_counter s t * rollBack
inc_counter 1 t * rollBack

rollBack t t l rollBack
rollBack _ _ r check_skipIS

; output true
p_True t _ l p_True
p_True s _ l p_True
p_True _ _ r p_T
p_T _ t r p_R
p_R _ r r p_U
p_U _ u r p_E
p_E _ e r done

; output false
p_False t t r p_False
p_False u u r p_False
p_False s s r p_False
p_False 1 1 r p_False
p_False _ _ l p_False_cleanup

p_False_cleanup t _ l p_False_cleanup
p_False_cleanup u _ l p_False_cleanup
p_False_cleanup s _ l p_False_cleanup
p_False_cleanup 1 _ l p_False_cleanup
p_False_cleanup _ _ r p_F

p_F _ f r p_A
p_A _ a r p_L
p_L _ l r p_S
p_S _ s r p_E1
p_E1 _ e r done
