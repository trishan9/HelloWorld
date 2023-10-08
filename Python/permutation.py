from itertools import permutations

inp_str=input("Enter string:")

# iterartive
def itr_permutation(inp_str):
    perm=[''.join(p) for p in permutations(inp_str)]
    return perm

perm_list=itr_permutation(inp_str)
print("iterartive permuation:")
for p in perm_list:
    print(p)


# recursive
def recur_permutation(s,l,r):
    if l==r:
        print(''.join(s))
    else:
        for i in range(l,r+1):
            s[l],s[i]=s[i],s[l]
            recur_permutation(s,l+1,r)
            s[l],s[i]=s[i],s[l]

print("resursive permuation:")
recur_permutation(list(inp_str),0,len(inp_str)-1)