//metadoc CollectorMarker copyright Steve Dekorte 2002
//metadoc CollectorMarker license BSD revised

#include "Common_inline.h"

void CollectorMarker_clear(CollectorMarker *self);
void CollectorMarker_insertAfter_(CollectorMarker *self, CollectorMarker *other);
//void CollectorMarker_insertBefore_(CollectorMarker *self, CollectorMarker *other);
void CollectorMarker_remove(CollectorMarker *self);
void CollectorMarker_removeAndInsertAfter_(CollectorMarker *self, CollectorMarker *other);
//void CollectorMarker_removeAndInsertBefore_(CollectorMarker *self, CollectorMarker *other);
void CollectorMarker_removeIfNeededAndInsertAfter_(CollectorMarker *self, CollectorMarker *other);
int CollectorMarker_isEmpty(CollectorMarker *self);
