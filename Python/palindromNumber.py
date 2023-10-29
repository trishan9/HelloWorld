def pal(num):
    temp = num
    ans = 0
    while(temp > 0):
        rem = temp % 10
        temp = temp//10
        ans = ans * 10 + rem
    if ans == num:
        return True
    else:
        return False

print(pal(121))