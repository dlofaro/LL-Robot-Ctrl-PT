#include <pebble.h>
#define TAP_NOT_DATA false
Window *window;	
void send_message(void);

int32_t x = 0;
int32_t y = 0;
int32_t z = 0;
int i = 0;

  int16_t theta_roll = 0;
  int16_t theta_pitch = 0;

	
// Key values for AppMessage Dictionary
enum {
	STATUS_KEY = 0,	
	MESSAGE_KEY = 1
};


static Window *s_main_window;
static TextLayer *s_output_layer;
static BitmapLayer *s_background_layer;
static GBitmap *s_background_bitmap;

static void data_handler(AccelData *data, uint32_t num_samples) {
  // Long lived buffer
  static char s_buffer[128];

  
  int16_t X = (data[0].x + data[1].x + data[2].x)/3;
  int16_t Y = (data[0].y + data[1].y + data[2].y)/3;
  int16_t Z = (data[0].z + data[1].z + data[2].z)/3;
  theta_roll = (int16_t)(360.0*((double)atan2_lookup(Y,Z)/(double)TRIG_MAX_RATIO)) - 180;
  theta_pitch = (int16_t)(360.0*((double)atan2_lookup(X,Z)/(double)TRIG_MAX_RATIO)) - 180;

  
  // Compose string of all data
  /*
  snprintf(s_buffer, sizeof(s_buffer), 
    "N X,Y,Z\n0 %d,%d,%d\n1 %d,%d,%d\n2 %d,%d,%d\nRoll = %d\nPitch= %d i=%d\n", 
    data[0].x, data[0].y, data[0].z, 
    data[1].x, data[1].y, data[1].z, 
    data[2].x, data[2].y, data[2].z,
    theta_roll, theta_pitch, i
  );
  */
  
    snprintf(s_buffer, sizeof(s_buffer), 
    "%d,%d,%d\nRoll = %d\nPitch= %d\ni=%d\n", 
    data[0].x, data[0].y, data[0].z, 
    theta_roll, theta_pitch, i
  );
  
  /* working send message */
  send_message();
  
  //Show the data
  text_layer_set_text(s_output_layer, s_buffer);
}

static void tap_handler(AccelAxisType axis, int32_t direction) {
  switch (axis) {
  case ACCEL_AXIS_X:
    if (direction > 0) {
      text_layer_set_text(s_output_layer, "X axis positive.");
    } else {
      text_layer_set_text(s_output_layer, "X axis negative.");
    }
    i = i+100;
    x = direction;
    break;
  case ACCEL_AXIS_Y:
    if (direction > 0) {
      text_layer_set_text(s_output_layer, "Y axis positive.");
    } else {
      text_layer_set_text(s_output_layer, "Y axis negative.");
    }
    y = direction;
    i = i + 10;
    break;
  case ACCEL_AXIS_Z:
    if (direction > 0) {
      text_layer_set_text(s_output_layer, "Z axis positive.");
    } else {
      text_layer_set_text(s_output_layer, "Z  axis negative.");
    }
    i = i + 1;
    z = direction;
    break;
  }
  // Long lived buffer
  static char s_buffer[128];

  // Compose string of all data
  snprintf(s_buffer, sizeof(s_buffer), 
    "X,Y,Z\n %d,%d,%d\n %d\n", 
    (int)x,(int)y,(int)z, i
  );
  
  //Show the data
  text_layer_set_text(s_output_layer, s_buffer);
}



static void main_window_load(Window *window) { 
  Layer *window_layer = window_get_root_layer(window);
  GRect window_bounds = layer_get_bounds(window_layer);
  
  // Create GBitmap, then set to created BitmapLayer
 
  s_background_bitmap = gbitmap_create_with_resource(RESOURCE_ID_LOFARO_LABS_FRONT_IDENTIFIER);
  s_background_layer = bitmap_layer_create(GRect(0, 0, 144, 168));
  bitmap_layer_set_bitmap(s_background_layer, s_background_bitmap);
  layer_add_child(window_get_root_layer(window), bitmap_layer_get_layer(s_background_layer));


  // Create output TextLayer
  /*
  s_output_layer = text_layer_create(GRect(5, 52, 139, 50));
  text_layer_set_background_color(s_output_layer, GColorClear);
  text_layer_set_text_color(s_output_layer, GColorBlack);
  text_layer_set_text(s_output_layer, "00:00");
  */
  
  s_output_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 10, window_bounds.size.h-50));
  text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(s_output_layer, "No data yet.");
  text_layer_set_overflow_mode(s_output_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_output_layer));

/*
  s_output_layer = text_layer_create(GRect(5, 0, window_bounds.size.w - 10, window_bounds.size.h));
  text_layer_set_font(s_output_layer, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_text(s_output_layer, "No data yet.");
  text_layer_set_overflow_mode(s_output_layer, GTextOverflowModeWordWrap);
  layer_add_child(window_layer, text_layer_get_layer(s_output_layer));
  */
}


static void main_window_unload(Window *window) {
  // Destroy output TextLayer
  
  text_layer_destroy(s_output_layer);
  
      // Destroy GBitmap
    gbitmap_destroy(s_background_bitmap);

    // Destroy BitmapLayer
    bitmap_layer_destroy(s_background_layer);
}

















// Write message to buffer & send
void send_message(void){
	DictionaryIterator *iter;
	
	app_message_outbox_begin(&iter);
	dict_write_uint8(iter, MESSAGE_KEY, 0x1);
  //dict_write_uint8(iter, STATUS_KEY, 0x1);
  static const char *messageBuff = "HelloDan";
  i = i+1;
  //dict_write_int(iter, STATUS_KEY, &i, sizeof(i), true);
//  dict_write_cstring(iter, MESSAGE_KEY, messageBuff);
//  //dict_write_int16(iter, MESSAGE_KEY, i);
  char buff[15];
  snprintf(buff, sizeof(buff), "PR,%d,%d", theta_pitch, theta_roll);
  //snprintf(buff, '%d',200);
  dict_write_cstring(iter, MESSAGE_KEY, buff);
  //dict_write_int16(iter, STATUS_KEY, -42);
	
//	dict_write_end(iter);
  	app_message_outbox_send();
}

// Called when a message is received from PebbleKitJS
static void in_received_handler(DictionaryIterator *received, void *context) {
	Tuple *tuple;
	
	tuple = dict_find(received, STATUS_KEY);
	if(tuple) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Received Status: %d", (int)tuple->value->uint32); 
	}
	
	tuple = dict_find(received, MESSAGE_KEY);
	if(tuple) {
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Received Message: %s", tuple->value->cstring);
	}}

// Called when an incoming message from PebbleKitJS is dropped
static void in_dropped_handler(AppMessageResult reason, void *context) {	
}

// Called when PebbleKitJS does not acknowledge receipt of a message
static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
}

static void tick_handler(struct tm *tick_time, TimeUnits units_changed) {
  send_message();
}

void init(void) {
//	window = window_create();
//	window_stack_push(window, true);

  
	// Register AppMessage handlers
	app_message_register_inbox_received(in_received_handler); 
	app_message_register_inbox_dropped(in_dropped_handler); 
	app_message_register_outbox_failed(out_failed_handler);
		
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
	
	send_message();
  
  // acc stuff
    // Create main Window
  
  s_main_window = window_create();
  	
  // full screen
  window_set_fullscreen(s_main_window, true);
  
  window_set_window_handlers(s_main_window, (WindowHandlers) {
    .load = main_window_load,
    .unload = main_window_unload
  });
  window_stack_push(s_main_window, true);

  // Use tap service? If not, use data service
  if (TAP_NOT_DATA) {
    // Subscribe to the accelerometer tap service
    accel_tap_service_subscribe(tap_handler);
  } else {
    // Subscribe to the accelerometer data service
    int num_samples = 3;
    accel_data_service_subscribe(num_samples, data_handler);

    // Choose update rate
    accel_service_set_sampling_rate(ACCEL_SAMPLING_10HZ);
  }
  tick_timer_service_subscribe(SECOND_UNIT, tick_handler);
}

void deinit(void) {
	app_message_deregister_callbacks();
//	window_destroy(window);
   // Destroy main Window
  window_destroy(s_main_window);

  if (TAP_NOT_DATA) {
    accel_tap_service_unsubscribe();
  } else {
    accel_data_service_unsubscribe();
  }
}

int main( void ) {
	init();
	app_event_loop();
	deinit();
}



// -----------------
