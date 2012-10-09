#define COLLECTORMARKER_C
#include "CollectorMarker.h"
#undef COLLECTORMARKER_C

#include <assert.h>

// BEGIN CollectorMarker_inline

void CollectorMarker_clear(CollectorMarker *self)
{
	self->prev = NULL;
	self->next = NULL;
}

void CollectorMarker_insertAfter_(CollectorMarker *self, CollectorMarker *other)
{
	self->color = other->color;

	self->prev = other;
	self->next = other->next;

	other->next->prev = self;
	other->next = self;
}

/*
void CollectorMarker_insertBefore_(CollectorMarker *self, CollectorMarker *other)
{
	self->color = other->color;

	self->prev = other->prev;
	self->next = other;

	other->prev->next = self;
	other->prev = self;
}
*/

void CollectorMarker_remove(CollectorMarker *self)
{
	self->prev->next = self->next;
	self->next->prev = self->prev;
	//self->next = NULL; // temp
	//self->prev = NULL; // temp
}

void CollectorMarker_removeAndInsertAfter_(CollectorMarker *self, CollectorMarker *other)
{
	CollectorMarker_remove(self);
	CollectorMarker_insertAfter_(self, other);
}

/*
void CollectorMarker_removeAndInsertBefore_(CollectorMarker *self, CollectorMarker *other)
{
	CollectorMarker_remove(self);
	CollectorMarker_insertBefore_(self, other);
}
*/

void CollectorMarker_removeIfNeededAndInsertAfter_(CollectorMarker *self, CollectorMarker *other)
{
	if (self->prev)
	{
		CollectorMarker_remove(self);
	}

	CollectorMarker_insertAfter_(self, other);
}

int CollectorMarker_isEmpty(CollectorMarker *self)
{
	return (self->color != self->next->color);
}

// END CollectorMarker_inline

void CollectorMarker_check(CollectorMarker *self)
{
	CollectorMarker *v = self;

	while (v != self)
	{
		assert(v->next->prev == v);
		assert(v->prev->next == v);
		v = v->next;
	}
}

CollectorMarker *CollectorMarker_new(void)
{
	CollectorMarker *self = io_calloc(1, sizeof(CollectorMarker));
	return self;
}

CollectorMarker *CollectorMarker_newWithColor_(unsigned int color)
{
	CollectorMarker *self = CollectorMarker_new();
	self->color = color;
	return self;
}

void CollectorMarker_free(CollectorMarker *self)
{
	io_free(self);
}

void CollectorMarker_loop(CollectorMarker *self)
{
	self->prev = self;
	self->next = self;
}

int CollectorMarker_count(CollectorMarker *self)
{
	int count = 0;
	CollectorMarker *v = self->next;
	unsigned int c = self->color;

	while (v->color == c)
	{
		CollectorMarker *next = v->next;
		v = next;
		count ++;
	}

	return count;
}

int CollectorMarker_colorSetIsEmpty(CollectorMarker *self)
{
	return self->color != self->next->color;
}

