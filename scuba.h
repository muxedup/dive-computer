/**
 * @file scuba.h
 *
 * @brief Public declarations for the scuba module.
 */
#ifndef _SCUBA_H
#define _SCUBA_H

enum { MAX_AIR_IN_CL = (2000 * 100) };  // Compressed air capacity (in cL).
enum { MAX_DEPTH_IN_M = 40 };           // Maximum safe depth (in meters).
enum { ASCENT_RATE_LIMIT = 15 };        // Maximum safe ascent rate (in m/min).

#define MM2FT(mm)   ((mm) / 305)    // NOTE: It's actually 304.8 mm to a 1 ft.

#define depth_change_in_mm(ascent_rate_in_m) \
                    (((ascent_rate_in_m) * 1000) / (2 * 60))

uint32_t gas_rate_in_cl(uint32_t depth_in_mm);
uint32_t gas_to_surface_in_cl(uint32_t depth_in_mm);

int16_t adc_to_rate(uint16_t adc_sample);
#endif /* _SCUBA_H */
