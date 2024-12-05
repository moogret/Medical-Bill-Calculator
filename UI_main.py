import customtkinter as ctk
from tkinter import *
from UI_constants import *
import sys
import locale
locale.setlocale(locale.LC_ALL, 'en_US.UTF-8')


procedure_list_box = None
cost_label = None
search_entry = None
itemListFrame = None
insurance_dropdown = None
Total_cost_int = None
added_items = {}
cost_items = {}
# Sets theme for main window
def change_appearance(selection): # changes window appearance based on selection
    ctk.set_appearance_mode(selection)

# Sets resolution for main window
def change_res(selection): # changes window resolution based on selection
    app.geometry(selection)

def procedure_search(choice):
    print("combobox dropdown clicked:", choice)

def on_search(event):
    query = search_entry.get().upper()  # Get user input and convert to uppercase
    # Filter the PROCEDURE_LIST for items that contain the query as a substring
    filtered_items = []
    for item in PROCEDURE_LIST:
        if query in item:
            filtered_items.append(item)

    update_procedure_list(filtered_items)

def on_search2(event):
    query = search_entry.get().upper()  # Get user input and convert to uppercase
# Filter the PROCEDURE_LIST for items that contain the query as a substring
    filtered_items = []
    for item in PROCEDURE_LIST:
        if query in item:
            filtered_items.append(item)

    update_procedure_list(filtered_items)


def update_total_cost(name, add):
    sum = 0.00
    for cost in cost_items.values():
        sum += cost
    formattedOut = locale.currency(sum, grouping=True)
    cost_label.configure(text=formattedOut)

    # global Total_cost_int
    # print(name)
    # with open("price_data.txt", "r") as file:
    #     content = file.read()  # Reads the entire content of the file
    #     content = float(content.strip())
    # if (add):
    #     Total_cost_int += content
    # else:
    #     Total_cost_int -= content
    # formattedOut = locale.currency(Total_cost_int, grouping=True)
    # cost_label.configure(text=formattedOut)


def delete_the_procedure(name):
    del cost_items[name]
    added_items[name].destroy()
    del added_items[name]
    if len(added_items) == 0:
        insurance_dropdown.configure(state="normal")
    update_total_cost(name, False)


def add_to(name):
    # send code to the c++, find the price
    print(name)

    # lock up the state of the inusrance
    insurance_dropdown.configure(state="disabled")

    # Open the file in read mode
    with open("price_data.txt", "r") as file:
        content = file.read()  # Reads the entire content of the file
        # print("Python Recieved: " + content)
        content = float(content.strip())
        price = locale.currency(content, grouping=True)

    cost_items[name] = content
    added_items[name] = ctk.CTkFrame(master=itemListFrame, width=200, height=100, border_width=2, border_color="black",
                         fg_color="white")
    added_items[name].pack(pady=5, padx=10, anchor="w")
    label = ctk.CTkLabel(master=added_items[name], text=name, font=("Helvetica", 14), width=200, anchor="w")
    label.grid(column=0, row=0, pady=5, padx=10)
    label2 = ctk.CTkLabel(master=added_items[name], text=price, font=("Helvetica", 14), width=80, anchor="w")
    label2.grid(column=1, row=0, pady=5, padx=10)
    button = ctk.CTkButton(master=added_items[name], text="Remove", fg_color="red", width=50, height=30, command=lambda n=name: delete_the_procedure(n))
    button.grid(column=2, row=0, pady=5, padx=10)
    update_total_cost(name, True)



def update_procedure_list(filtered_items):
    # Clear the current scrollable frame
    for widget in procedure_list_box.winfo_children():
        widget.destroy()

    # Add filtered items to the scrollable frame
    for item in filtered_items:

        frame = ctk.CTkFrame(master=procedure_list_box, width=200, height=100, border_width=2, border_color="black", fg_color="white")
        frame.pack(pady=5, padx=10, anchor="w")
        label = ctk.CTkLabel(master=frame, text=item, font=("Helvetica", 14), width=225, anchor="w")
        label.grid(column=0, row=0, pady=5, padx=10)
        button = ctk.CTkButton(master=frame, text="Add", width=50, height=30, command=lambda n=item: add_to(n))
        button.grid(column=2, row=0, pady=5, padx=10)





def printInsurance(name):
    update_procedure_list(PROCEDURE_LIST)
    search_entry.configure(state="normal")
    print(name)

# initializes root as app for main window
app = ctk.CTk()

def main():
    global procedure_list_box
    global search_entry
    global itemListFrame
    global insurance_dropdown
    global cost_label
    global Total_cost_int

    Total_cost_int = 0.00

    # sets default window size and title
    app.geometry(WINDOW_SIZE)
    app.title("Medical Procedure Cost Calculator")


    # sets default appearance and color theme
    ctk.set_appearance_mode(APPEARANCE)
    ctk.set_default_color_theme(COLOR_THEME)

    # build main user interface frames
    leftBottomButtonsFrame = ctk.CTkFrame(master=app, width=350, height=45, fg_color=FRAME_COLOR)
    leftBottomButtonsFrame.place(relx=0.12, rely=0.92, anchor=ctk.N)

    itemListFrame = ctk.CTkScrollableFrame(master=app, width=450, height=425, border_width=5, border_color="black", fg_color="white")
    itemListFrame.place(relx=0.7, rely=0.2, anchor=ctk.N)

    procedureSearchFrame = ctk.CTkFrame(master=app, width=500, height=500, fg_color="gray")
    procedureSearchFrame.place(relx=0.3, rely=0.2, anchor=ctk.N)

    costFrame = ctk.CTkFrame(master=app, width=475, height=50, fg_color="#d3d3d3")
    costFrame.place(relx=0.7, rely=0.82, anchor=ctk.N)




# appearance dropdown selector
    appearance_dropdown = ctk.CTkOptionMenu(master=leftBottomButtonsFrame, values=APPEARANCE_OPTIONS, anchor=ctk.NW, command=change_appearance)
    appearance_dropdown.set(APPEARANCE)
    appearance_dropdown.grid(row=0, column=0, padx=4, pady=8)

    # window size dropdown selector
    window_size_dropdown = ctk.CTkOptionMenu(master=leftBottomButtonsFrame, values=WINDOW_SIZE_OPTIONS, command=change_res)
    window_size_dropdown.set(WINDOW_SIZE)
    window_size_dropdown.grid(row=0, column=1, padx=4, pady=8)

    insurance_dropdown_var = ctk.StringVar(value="")
    insurance_dropdown = ctk.CTkOptionMenu(master=procedureSearchFrame, values=INSURANCE_LIST, width=350, height=60, font=("Helvetica",17), command=printInsurance, variable=insurance_dropdown_var)
    insurance_dropdown.set("Select your insurance provider...")
    insurance_dropdown.place(relx=0.5, rely=0.1, anchor=ctk.N)

    search_entry = ctk.CTkEntry(master=procedureSearchFrame, placeholder_text="Search procedures...", width=350, height=60, font=("Helvetica",15), state="disabled")
    search_entry.place(relx=0.5, rely=0.25, anchor=ctk.N)
    #v search_entry.bind("<KeyRelease>", on_search)  # Trigger search on key release
    search_entry.bind("<Return>", on_search2)  # Trigger search on key release


# search_combo = ctk.CTkComboBox(master=procedureSearchFrame, values=PROCEDURE_LIST, width=200, height = 60)
    # search_combo.place(relx=0.5, rely=0.25, anchor=ctk.N)


    procedure_list_box = ctk.CTkScrollableFrame(master=procedureSearchFrame, width=350, height=250)
    procedure_list_box.place(relx=0.5, rely=0.4, anchor=ctk.N)


    heading_label = ctk.CTkLabel(master=app, text="Welcome to the \n Medical Procedure Cost Calculator!", font=("Helvetica",30))
    heading_label.place(relx=0.5, rely=0.05, anchor=ctk.N)


    label10 = ctk.CTkLabel(master=costFrame, text="Total Estimated Cost:", font=("Helvetica",18), anchor="w")
    label10.grid(column=0, row=0, padx=60, pady=5)

    directions = ctk.CTkLabel(master=procedureSearchFrame, height=15, text="Press enter to search", font=("Helvetica",12), anchor=ctk.W)
    directions.place(relx=0.36, rely=0.37)

    cost_label = ctk.CTkLabel(master=costFrame, text="$00.00", font=("Helvetica",18), anchor=ctk.W)
    cost_label.grid(column=1, row=0, padx=30, pady=5)


    app.mainloop()
if __name__ == "__main__":
    main()