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
static Window *prepWindow;
static SimpleMenuLayer *menuLayer;
static GBitmap *menuIcons[NUM_MENU_ITEMS];
static SimpleMenuSection menuSections[NUM_MENU_SECTIONS];
static SimpleMenuItem menuItems[NUM_MENU_ITEMS];
static GBitmap *prepImage;
static BitmapLayer *prepBitmapLayer;
static TextLayer *beanLabel;
static TextLayer *waterWeightLabel;
static TextLayer *timeLabel;
static TextLayer *grindLabel;
int currentIndex = 0;


// Function prototypes.
static void init();
static void deinit();
static void main_window_load(Window *mainWindow);
static void main_window_unload(Window *mainWindow);
static void prep_window_load(Window *prepWindow);
static void prep_window_unload(Window *prepWindow);
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

    prepWindow = window_create();
    window_set_window_handlers(prepWindow, (WindowHandlers) {
        .load = prep_window_load,
        .unload = prep_window_unload,
    });
    window_set_background_color(prepWindow, GColorBlack);
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
    currentIndex = index;
    window_stack_push(prepWindow, true);
}

static void prep_window_load(Window *prepWindow) {
    if(currentIndex == 0) {
        prepImage = gbitmap_create_with_resource(RESOURCE_ID_PREP_V60);
    }
    else if(currentIndex == 1){
        prepImage = gbitmap_create_with_resource(RESOURCE_ID_PREP_CHEMEX);
    }
    
    prepBitmapLayer = bitmap_layer_create(GRect(50, 6, 44, 44));
    bitmap_layer_set_compositing_mode(prepBitmapLayer, GCompOpSet);
    bitmap_layer_set_bitmap(prepBitmapLayer, prepImage);
    layer_add_child(window_get_root_layer(prepWindow), 
        bitmap_layer_get_layer(prepBitmapLayer));

    beanLabel = text_layer_create(GRect(0, 56, 72, 20));
    text_layer_set_text(beanLabel, "Bean");
    text_layer_set_text_alignment(beanLabel, GTextAlignmentCenter);
    text_layer_set_background_color(beanLabel, GColorBlack);
    text_layer_set_text_color(beanLabel, GColorWhite);
    layer_add_child(window_get_root_layer(prepWindow), 
        text_layer_get_layer(beanLabel));

    waterWeightLabel = text_layer_create(GRect(0, 112, 72, 20));
    text_layer_set_text(waterWeightLabel, "Water");
    text_layer_set_text_alignment(waterWeightLabel, GTextAlignmentCenter);
    text_layer_set_background_color(waterWeightLabel, GColorBlack);
    text_layer_set_text_color(waterWeightLabel, GColorWhite);
    layer_add_child(window_get_root_layer(prepWindow), 
        text_layer_get_layer(waterWeightLabel));

    timeLabel = text_layer_create(GRect(72, 56, 72, 20));
    text_layer_set_text(timeLabel, "Time");
    text_layer_set_text_alignment(timeLabel, GTextAlignmentCenter);
    text_layer_set_background_color(timeLabel, GColorBlack);
    text_layer_set_text_color(timeLabel, GColorWhite);
    layer_add_child(window_get_root_layer(prepWindow), 
        text_layer_get_layer(timeLabel));

    grindLabel = text_layer_create(GRect(72, 112, 72, 20));
    text_layer_set_text(grindLabel, "Grind");
    text_layer_set_text_alignment(grindLabel, GTextAlignmentCenter);
    text_layer_set_background_color(grindLabel, GColorBlack);
    text_layer_set_text_color(grindLabel, GColorWhite);
    layer_add_child(window_get_root_layer(prepWindow), 
        text_layer_get_layer(grindLabel));
}

static void prep_window_unload(Window *prepWindow) {
    gbitmap_destroy(prepImage);
    bitmap_layer_destroy(prepBitmapLayer);
    text_layer_destroy(beanLabel);
    text_layer_destroy(waterWeightLabel);
    text_layer_destroy(timeLabel);
    text_layer_destroy(grindLabel);
}
