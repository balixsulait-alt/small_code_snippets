print("Bin_Sula") #hhggg
# Compute avg amount per user while preventing division-by-zero
amount_collected = int(input("amount_collected"))
number_of_users = int(input("number_of_users"))
try:
    average = amount_collected / number_of_users
    print("Average amount per user:", average)
except ZeroDivisionError: #error handling
    print("Error: Cannot divide by zero")


print(\n next \t error check \n)
#######🤞🤞🤞 ###################
    # Attempt to open report.txt and handle the case where the file is missing
try:
    report_file = open("report.txt", "r")
    print("Report loaded successfully.")
    # close file
    report_file.close()
except FileNotFoundError:
    print("File not found.")
