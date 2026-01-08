#ifndef SCH_EVENT_MANAGEMENT_H
#define SCH_EVENT_MANAGEMENT_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    uint16_t sig;
} sch_event_header;

typedef struct {
    sch_event_header event_header;
    int16_t first_data;
    int16_t second_data;
} sch_event;

#ifdef __cplusplus
}
#endif

#endif