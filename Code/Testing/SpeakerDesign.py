import math

def my_range(start, end, step):
    while start <= end:
        yield start
        start += step
def my_range2(start, end, step):
    while start >= end:
        yield start
        start -= step
max = 0
for w in my_range(1, 10, 0.1):
    for s in my_range2(10,1.5,0.1):
        n = (-(2*w+4*s)+math.sqrt(pow((s*w+4*s),2)+4*(w+s)*(2*4*w/0.035)))/(4*(w+s))
        l = (2*((4*w)/0.035)+2*n*(2*n+1)*(w+s)-4*s*n)/(3+4*n)
        if math.floor(n) > math.floor(max):
            max = n
            print('W = ', w)
            print('S = ', s)
            print('n = ', n)
            print('l = ', l)
