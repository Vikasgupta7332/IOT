shopping_list = []
for i in range(5):
    item = input("Enter an item for your shopping list: ")
    shopping_list.append(item)  

shopping_list.remove("potato")

shopping_list.pop()

shopping_list.pop(0)

print("Your shopping list:")
for item in shopping_list:
    print(item)


