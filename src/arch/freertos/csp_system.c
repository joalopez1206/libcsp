#include <csp/csp_hooks.h>

#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

__attribute__((weak)) uint32_t csp_memfree_hook(void) {
#if (configSUPPORT_DYNAMIC_ALLOCATION == 1)
	return (uint32_t)xPortGetFreeHeapSize();
#else
	return 0;
#endif
}

__attribute__((weak)) unsigned int csp_ps_hook(csp_packet_t * packet) {
	return 0;
}

void csp_reboot_hook(void) {

    extern void __attribute__((weak)) cpu_set_reset_cause(unsigned int);
    if (cpu_set_reset_cause)
        cpu_set_reset_cause(1);

    extern void __attribute__((weak)) cpu_reset(void);
    if (cpu_reset) {
        cpu_reset();
        while (1);
    }

    printf("Failed to reboot");
}
void csp_shutdown_hook(void){
    extern void __attribute__((weak)) cpu_shutdown(void);
    if (cpu_shutdown) {
        cpu_shutdown();
        while (1);
    }
    printf("Failed to reboot");
}