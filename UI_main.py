import customtkinter as ctk
from tkinter import *
from UI_constants import *

# Sets theme for main window
def change_appearance(selection): # changes window appearance based on selection
    ctk.set_appearance_mode(selection)

# Sets resolution for main window
def change_res(selection): # changes window resolution based on selection
    app.geometry(selection)

def procedure_search(choice):
    print("combobox dropdown clicked:", choice)

def procedure_find(choice):
    print("combobox button clicked:", choice)

# initializes root as app for main window
app = ctk.CTk()

def main():

    # sets default window size and title
    app.geometry(WINDOW_SIZE)
    app.title("Project 3 (Change this later)")


    # sets default appearance and color theme
    ctk.set_appearance_mode(APPEARANCE)
    ctk.set_default_color_theme(COLOR_THEME)

    # build main user interface frames
    leftBottomButtons = ctk.CTkFrame(master=app, width=350, height=45, fg_color=FRAME_COLOR)
    leftBottomButtons.place(relx=0.01, rely=0.92, anchor=ctk.NW)

    itemListFrame = ctk.CTkScrollableFrame(master=app, width=400, height=550, border_width=5, border_color="black", fg_color="white")
    itemListFrame.place(relx=0.85, rely=0.05, anchor=ctk.NW)


    # appearance dropdown selector
    appearance_dropdown = ctk.CTkOptionMenu(master=leftBottomButtons, values=APPEARANCE_OPTIONS, anchor=ctk.NW, command=change_appearance)
    appearance_dropdown.set(APPEARANCE)
    appearance_dropdown.grid(row=0, column=0, padx=4, pady=8)

    # window size dropdown selector
    window_size_dropdown = ctk.CTkOptionMenu(master=leftBottomButtons, values=WINDOW_SIZE_OPTIONS, command=change_res)
    window_size_dropdown.set(WINDOW_SIZE)
    window_size_dropdown.grid(row=0, column=1, padx=4, pady=8)

    insurance_dropdown = ctk.CTkOptionMenu(master=app, values=["", "United Health", "Florida Blue", "Cigna"])
    insurance_dropdown.place(relx=0.55, rely=0.3, anchor=ctk.NW)


    procedure_searchbox_var = ctk.StringVar(value="")
    procedure_searchbox = ctk.CTkComboBox(master=app, values=PROCEDURE_LIST, command=procedure_search, variable=procedure_searchbox_var)
    procedure_searchbox_var.set("Select Procedure")
    procedure_searchbox.place(relx=0.20, rely=0.4, anchor=ctk.NW)

    procedure_searchbutton = ctk.CTkButton(master=app, text="Search", command=procedure_find, width=15)
    procedure_searchbutton.place(relx=0.33, rely=0.4, anchor=ctk.NW)


    procedure_output_label = ctk.CTkLabel(master=app, text="Welcome to Mary Squared + Abhik\nMedical Procedure Cost Calculator!")
    procedure_output_label.place(relx=0.4, rely=0.05, anchor=ctk.NW)





    app.mainloop()
if __name__ == "__main__":
    main()