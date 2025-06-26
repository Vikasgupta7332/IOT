def check(num1):
    if num1 % 2 == 0:
        return "Even"
    elif num1 %2 != 0:
        return "Odd"
num1 = int(input("Enter number:"))
#num2 = int(input("Enter second number:"))
result = check(num1)
if result:
    print(result)
else:
    print("One is even and the second is odd")
    