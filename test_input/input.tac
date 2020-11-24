a = 3
b = 5
c = 10
if (a > 5)
{
    d = sum(a,b)
    e = c - d   
}
else
{
    d = sub(b,a)
    e = c + d
}

int sum(a,b){
    return a+b
}

int sub(a,b) {
    return a-b
}

a = 3
b = 5
c = 10
_t1 = a < 5
_t2 = a == 5
_t3 = _t1 || _t2
If _t3 Goto L1




a = 3
b = 5
c = 10
if (!(a == 5))
{
    d = sum(a,b)
    e = c - d   
}
else
{
    d = sub(b,a)
    e = c + d
}


int sum(a,b){
    return a+b
}

int sub(a,b) {
    return a-b
}