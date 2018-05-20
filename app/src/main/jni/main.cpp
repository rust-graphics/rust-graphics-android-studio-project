#include <android/native_activity.h>
#include <android/log.h>

extern "C" void vulkust_on_create(ANativeActivity* activity, void* saved_state, size_t saved_state_size);

extern "C" void ANativeActivity_onCreate(ANativeActivity* activity, void* saved_state, size_t saved_state_size) {
    vulkust_on_create(activity, saved_state, saved_state_size);
}