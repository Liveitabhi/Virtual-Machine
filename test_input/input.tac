function func 0 a b
_t2 = a + 5
return _t2


function func1 0 c d
return

_L4 :
function main 3
int a
int b
int c
_t1 = a == b
If _t1 goto _L2
pushParam a
_t1 = b + 3
pushParam _t1
_t1 = call func 2
goto _L3
_L2 :
_t1 = a + b
_t2 = b + c
_L3 :
call func1 0
