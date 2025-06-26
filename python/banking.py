List_of_currency_notes = []
for i in range(5):
    item = input("Enter the currency note: ")
    List_of_currency_notes.append(item)
print("List of currency notes:", List_of_currency_notes)

search_currency_note = input("Enter the currency note to search: ")
if search_currency_note in List_of_currency_notes:
    print(f"{search_currency_note} is present in the list.")
else:
    print(f"{search_currency_note} is not present in the list.")