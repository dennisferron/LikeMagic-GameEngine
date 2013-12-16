//metadoc Collector copyright Steve Dekorte 2002
//metadoc Collector license BSD revised

#include "Common_inline.h"

// inspecting markers -------------------

int Collector_markerIsWhite_(Collector *self, CollectorMarker *m);
int Collector_markerIsGray_(Collector *self, CollectorMarker *m);
int Collector_markerIsBlack_(Collector *self, CollectorMarker *m);

// changing marker colors -------------------

void Collector_makeFree_(Collector *self, CollectorMarker *v);
void Collector_makeWhite_(Collector *self, CollectorMarker *v);
void Collector_makeGray_(Collector *self, CollectorMarker *v);
void Collector_makeBlack_(Collector *self, CollectorMarker *v);
void Collector_makeGrayIfWhite_(Collector *self, CollectorMarker *v);

/*
void Collector_makeFreed_(Collector *self, void *v);
*/
#ifdef COLLECTOR_USE_NONINCREMENTAL_MARK_SWEEP

	#define Collector_value_addingRefTo_(self, v, ref)

#else

	#define Collector_value_addingRefTo_(self, v, ref) XIMPLX_Collector_value_addingRefTo_(self, v, ref)
    void *XIMPLX_Collector_value_addingRefTo_(Collector *self, CollectorMarker *v, void *ref);

#endif

