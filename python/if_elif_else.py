num1 = int(input("Enter Number :"))
num2 = int(input("Enter Number :"))
num3 = int(input("Enter Number :"))

if num1>=num2 and num1>=num3:
    largest = num1
    print(f"largest number: {largest}" )
elif num2>=num1 and num2>=num3:
    largest = num2
    print(f"largest number: {largest}" )
else:
    largest = num3
    print(f"largest number: {largest}")