### Squa TUI Library Tutorial

Welcome to the Squa TUI library tutorial! This guide will walk you through the features and usage of Squa, a simplified text-based user interface (TUI) library built on top of `ncurses`. Squa is designed to be easy to use, reducing the complexity typically associated with creating TUIs.

---

### Table of Contents

1. [Getting Started](#getting-started)
2. [Initialization](#initialization)
3. [Creating Buttons](#creating-buttons)
4. [Handling Input](#handling-input)
5. [Message Boxes](#message-boxes)
6. [Asking Questions](#asking-questions)
7. [Graphics Functions](#graphics-functions)
8. [Termination](#termination)

---

### Getting Started

To begin using Squa, include the necessary header files in your project:

```cpp
#include <squa.h>
#include <squa_gfx.h>
```
Or (if the files are in the current directory)
```cpp
#include "squa.h"
#include "squa_gfx.h"
```

These headers provide all the functions you need to create and manage TUIs.

---

### Initialization

Before creating any UI elements, you need to initialize Squa:

```cpp
SQUA_Init(bool hideCursor = true, bool makeESCKeyInstant = true);
```

- **hideCursor**: Optional argument (default: `true`). If set to `true`, the cursor will be hidden.
- **makeESCKeyInstant**: Optional argument (default: `true`). If set to `true`, it reduces the delay for the ESC key detection.

Example:

```cpp
SQUA_Init();
```

---

### Creating Buttons

Creating a button is simple and can be done with the `SQUA_CreateButton` function:

```cpp
SQUA_CreateButton(int posX, int posY, const char *text, std::function<void(void)> onClick);
```

- **posX, posY**: The position of the button.
- **text**: The label displayed on the button.
- **onClick**: The function to be executed when the button is clicked.

**Important:** Ensure buttons are created outside of the main loop to avoid creating multiple instances.
**If not click listener is availaible:** If no click listener is availaible, Simply use constant variable NO_ONCLICK_COMMAND from `squa.h`

Example:

```cpp
void onButtonClick() {
    SQUA_MessageBox("Button clicked!", "Notice");
}

int main() {
    SQUA_Init();
    SQUA_CreateButton(10, 5, "Click Me", SQUA_ConvertToListener(onButtonClick));
    
    // Event loop...
}
```

---

### Handling Input

Use `SQUA_Begin` to handle user input and render the UI elements. This function should be called inside the main loop:

```cpp
int SQUA_Begin(char exitKey = ESC, char selectKey = '\t', char useKey = '\n');
```

- **exitKey**: Key to exit the loop (default: `ESC`).
- **selectKey**: Key to move between buttons (default: `TAB`).
- **useKey**: Key to select a button (default: `ENTER`).

**Return Value:**

- **1**: When the exit key is pressed, signaling to break the loop.
- **0**: Continue processing.

Example:

```cpp
while (true) {
    int result = SQUA_Begin();
    if (result == 1) {
        break;
    }
}
```

---

### Message Boxes

Display a simple message box with a title and message using `SQUA_MessageBox`:

```cpp
void SQUA_MessageBox(const char *msg, const char *title = "Message");
```

- **msg**: The message to display.
- **title**: The title of the message box.

Example:

```cpp
SQUA_MessageBox("This is a message.", "Info");
```

---

### Asking Questions

You can prompt the user with a question using `SQUA_Question`, which allows for simple input selection:

```cpp
int SQUA_Question(const char *msg, const char *title = "Question", const char *opt_1 = "<Ok>", const char *opt_2 = "<Cancel>");
```

- **msg**: The question text.
- **title**: The title of the question box.
- **opt_1, opt_2**: The options to choose from.

**Return Value:**

- **OPTION_OK**: If the user selects "Ok".
- **OPTION_CANCEL**: If the user selects "Cancel".

Example:

```cpp
int response = SQUA_Question("Do you want to continue?", "Confirm", "<Yes>", "<No>");
if (response == OPTION_OK) {
    // User selected Yes
} else {
    // User selected No
}
```

---

### Graphics Functions

Squa provides basic graphics functions for cursor manipulation and text printing:

- **Move Cursor**: `SQUA_MoveCursor(int newX, int newY);`
- **Print at Cursor**: `SQUA_PrintAtCursor(const char *text);`
- **Move and Print**: `SQUA_MoveAndPrint(int newX, int newY, const char *text);`
- **Highlight Mode**: `SQUA_SetModeToHighlight();`
- **Normal Mode**: `SQUA_SetModeToNormal();`

These functions are useful for more fine-tuned control over the display.

---

### Termination

Always call `SQUA_Terminate` at the end of your program to clean up and avoid memory leaks:

```cpp
SQUA_Terminate();
```

Example:

```cpp
int main() {
    SQUA_Init();

    // Your code here...

    SQUA_Terminate();
    return 0;
}
```

---

### Conclusion

Squa simplifies TUI development by offering easy-to-use functions while maintaining the flexibility of `ncurses`. With just a few lines of code, you can create complex interfaces with buttons, message boxes, and more. This tutorial covered the basics, but feel free to explore the library further to tailor it to your specific needs!