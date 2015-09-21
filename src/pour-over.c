//
// Name: pour-over.c
// Author: Mark Spicer
// Purpose: Main for pour-over Pebble Time application.
//

#include <pebble.h>


// Preprocessor definitions.
#define NUM_MENU_SECTIONS 1
#define NUM_MENU_ITEMS 2


// Global variables.
static Window *mainWindow;
static SimpleMenuLayer *menuLayer;
static GBitmap *menuIcons[NUM_MENU_ITEMS];
static SimpleMenuSection menuSections[NUM_MENU_SECTIONS];
static SimpleMenuItem menuItems[NUM_MENU_ITEMS];


// Function prototypes.
static void init();
static void deinit();
static void main_window_load(Window *mainWindow);
static void main_window_unload(Window *mainWindow);
static void menu_select_callback(int index, void *ctx);


// Main.
int main(void) {
    init();
    app_event_loop();
    deinit();
}


// Function definitions.
static void init(void) {
    mainWindow = window_create();
    window_set_window_handlers(mainWindow, (WindowHandlers) {
        .load = main_window_load,
        .unload = main_window_unload,
    });
    window_stack_push(mainWindow, true);
}

static void deinit(void) {
    window_destroy(mainWindow);
}

static void main_window_load(Window *mainWindow) {
    menuIcons[0] = gbitmap_create_with_resource(RESOURCE_ID_MENU_V60);
    menuIcons[1] = gbitmap_create_with_resource(RESOURCE_ID_MENU_CHEMEX);

    menuItems[0] = (SimpleMenuItem) {
        .title = "v60",
        .callback = menu_select_callback,
        .icon = menuIcons[0]
    };
    menuItems[1] = (SimpleMenuItem) {
        .title = "Chemex",
        .callback = menu_select_callback,
        .icon = menuIcons[1]
    };

    menuSections[0] = (SimpleMenuSection) {
        .num_items = NUM_MENU_ITEMS,
        .items = menuItems,
    };
    
    Layer *windowLayer = window_get_root_layer(mainWindow);
    GRect bounds = layer_get_frame(windowLayer);
    menuLayer = simple_menu_layer_create(bounds, mainWindow, menuSections, 
        NUM_MENU_SECTIONS, NULL);

    menu_layer_set_normal_colors(simple_menu_layer_get_menu_layer(menuLayer), 
        GColorBlack, GColorWhite);
    menu_layer_set_highlight_colors(simple_menu_layer_get_menu_layer(menuLayer),
        GColorKellyGreen, GColorWhite);

    layer_add_child(windowLayer, simple_menu_layer_get_layer(menuLayer));
}

static void main_window_unload(Window *mainWindow) {
    simple_menu_layer_destroy(menuLayer);

    for (int i = 0; i < NUM_MENU_ITEMS; i++) {
        gbitmap_destroy(menuIcons[i]);
    }
}

static void menu_select_callback(int index, void *ctx) {
}
