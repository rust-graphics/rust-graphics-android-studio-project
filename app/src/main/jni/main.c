#include <stdlib.h>

extern void rust_graphics_main(void* activity, void* saved_state, size_t saved_state_size);

extern void ANativeActivity_onCreate(void* activity, void* saved_state, size_t saved_state_size) {
    rust_graphics_main(activity, saved_state, saved_state_size);
}