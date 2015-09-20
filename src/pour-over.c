//
// Name: pour-over.c
// Author: Mark Spicer
// Purpose: Main for pour-over Pebble Time application.
//

#include <pebble.h>

// Global variables.
static Window *mainWindow;


// Function prototypes.
static void init();
static void deinit();
static void main_window_load(Window *mainWindow);
static void main_window_unload(Window *mainWindow);


// Main.
int main(void) {
    init();
    app_event_loop();
    deinit();
}


//
// Name: init
// Purpose: Creates all windows neccessary for the app.
// Inputs: N/A
// Returns: N/A
//
static void init(void) {
    mainWindow = window_create();
    window_set_window_handlers(mainWindow, (WindowHandlers) {
        .load = main_window_load,
        .unload = main_window_unload,
    });
    const bool animated = true;
    window_stack_push(mainWindow, animated);
}

//
// Name: deinit
// Purpose: Destroys all windows created during init.
// Inputs: N/A
// Returns: N/A
//
static void deinit(void) {
    window_destroy(mainWindow);
}

//
// Name: main_window_load 
// Purpose: Takes care of all tasks required to view the main window.
// Inputs: A window pointer. 
// Returns: N/A
//
static void main_window_load(Window *mainWindow) {
}

//
// Name: main_window_unload 
// Purpose: Unloads all of the elements from the main window.
// Inputs: A window pointer.
// Returns: N/A
//
static void main_window_unload(Window *mainWindow) {
}
