APPEARANCE = "Light"
APPEARANCE_OPTIONS = ["Dark", "Light", "System"]
COLOR_THEME = "green"
WINDOW_SIZE = "1280x720" + "+0+0"
WINDOW_SIZE_OPTIONS = ["2560x1440", "1920x1080", "1280x720"]
FRAME_BORDER_COLOR = ""
FRAME_COLOR = "#3E434B"

PROCEDURE_LIST = ["10001", "10003", "10007", "10012", "10016", "10017", "10021", "10032", "10038", "10042", "10045", "10050", "10055", "10056", "10065", "10067", "10074", "10079", "10084", "10086", "10093", "10108", "10118", "10119", "10121", "10125", "10126", "10127", "10130", "10133", "10137", "10140", "10141", "10143", "10144", "10152", "10155", "10156", "10158", "10159", "10168", "10173", "10174", "10180", "10187", "10188", "10189", "10204", "10207", "10210"
]
INSURANCE_LIST = ["", "United Health", "Florida Blue", "Cigna"]

import customtkinter as ctk

def on_search(event):
    query = search_entry.get().lower()  # Get the input and convert to lowercase
    filtered_items = [item for item in items if query in item.lower()]  # Filter list
    update_scrollable_list(filtered_items)

def update_scrollable_list(filtered_items):
    # Clear the current scrollable frame
    for widget in scrollable_frame.winfo_children():
        widget.destroy()

    # Add filtered items to the scrollable frame
    for item in filtered_items:
        label = ctk.CTkLabel(scrollable_frame, text=item, font=("Helvetica", 14))
        label.pack(pady=5, padx=10, anchor="w")  # Align items to the left

# Main app
app = ctk.CTk()
app.geometry("400x500")
app.title("Search Bar Example")

# Sample data
items = ["Heart Surgery", "Knee Replacement", "MRI Scan", "Blood Test", "Physical Therapy"]

# Search bar
search_entry = ctk.CTkEntry(app, placeholder_text="Search procedures...")
search_entry.pack(pady=10, padx=20)
search_entry.bind("<KeyRelease>", on_search)  # Trigger search on key release

# Scrollable frame to display results
scrollable_frame = ctk.CTkScrollableFrame(app, width=300, height=300)
scrollable_frame.pack(pady=10)

# Initialize scrollable list with all items
update_scrollable_list(items)

app.mainloop()
