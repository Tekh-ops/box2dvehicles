/*
* Copyright (c) 2006-2010 Erin Catto http://www.box2d.org
*
* This software is provided 'as-is', without any express or implied
* warranty.  In no event will the authors be held liable for any damages
* arising from the use of this software.
* Permission is granted to anyone to use this software for any purpose,
* including commercial applications, and to alter it and redistribute it
* freely, subject to the following restrictions:
* 1. The origin of this software must not be misrepresented; you must not
* claim that you wrote the original software. If you use this software
* in a product, an acknowledgment in the product documentation would be
* appreciated but is not required.
* 2. Altered source versions must be plainly marked as such, and must not be
* misrepresented as being the original software.
* 3. This notice may not be removed or altered from any source distribution.
*/

#include <Box2D/Collision/Shapes/b2LoopShape.h>
#include <Box2D/Collision/Shapes/b2EdgeShape.h>
#include <new>
#include <cstring>
using namespace std;

b2LoopShape::~b2LoopShape()
{
	b2Free(m_vertices);
	m_vertices = NULL;
	m_count = 0;
}

void b2LoopShape::Create(const b2Vec2* vertices, int32 count)
{
        //b2Assert(m_vertices == NULL && m_count == 0); //change to allow replacing of vertices
        if (m_vertices)
        {
                b2Free(m_vertices);
                m_vertices = NULL;
                m_count = 0;
        }

	b2Assert(count >= 2);
	m_count = count;
	m_vertices = (b2Vec2*)b2Alloc(count * sizeof(b2Vec2));
	memcpy(m_vertices, vertices, m_count * sizeof(b2Vec2));
}

b2Shape* b2LoopShape::Clone(b2BlockAllocator* allocator) const
{
	void* mem = allocator->Allocate(sizeof(b2LoopShape));
	b2LoopShape* clone = new (mem) b2LoopShape;
	clone->Create(m_vertices, m_count);
	return clone;
}

int32 b2LoopShape::GetChildCount() const
{
	return m_count;
}

void b2LoopShape::GetChildEdge(b2EdgeShape* edge, int32 index) const
{
	b2Assert(2 <= m_count);
	b2Assert(0 <= index && index < m_count);
	edge->m_type = b2Shape::e_edge;
	edge->m_radius = m_radius;
	edge->m_hasVertex0 = true;
	edge->m_hasVertex3 = true;

	int32 i0 = index - 1 >= 0 ? index - 1 : m_count - 1;
	int32 i1 = index;
	int32 i2 = index + 1 < m_count ? index + 1 : 0;
	int32 i3 = index + 2;
	while (i3 >= m_count)
	{
		i3 -= m_count;
	}

	edge->m_vertex0 = m_vertices[i0];
	edge->m_vertex1 = m_vertices[i1];
	edge->m_vertex2 = m_vertices[i2];
	edge->m_vertex3 = m_vertices[i3];
}

bool b2LoopShape::TestPoint(const b2Transform& xf, const b2Vec2& p) const
{
	B2_NOT_USED(xf);
	B2_NOT_USED(p);
	return false;
}

bool b2LoopShape::RayCast(b2RayCastOutput* output, const b2RayCastInput& input,
							const b2Transform& xf, int32 childIndex) const
{
	b2Assert(childIndex < m_count);

	b2EdgeShape edgeShape;

	int32 i1 = childIndex;
	int32 i2 = childIndex + 1;
	if (i2 == m_count)
	{
		i2 = 0;
	}

	edgeShape.m_vertex1 = m_vertices[i1];
	edgeShape.m_vertex2 = m_vertices[i2];

	return edgeShape.RayCast(output, input, xf, 0);
}

void b2LoopShape::ComputeAABB(b2AABB* aabb, const b2Transform& xf, int32 childIndex) const
{
	b2Assert(childIndex < m_count);

	int32 i1 = childIndex;
	int32 i2 = childIndex + 1;
	if (i2 == m_count)
	{
		i2 = 0;
	}

	b2Vec2 v1 = b2Mul(xf, m_vertices[i1]);
	b2Vec2 v2 = b2Mul(xf, m_vertices[i2]);

	aabb->lowerBound = b2Min(v1, v2);
	aabb->upperBound = b2Max(v1, v2);
}

float32 b2LoopShape::ComputeMass(b2MassData* massData, float32 density) const
{
	B2_NOT_USED(density);

	massData->mass = 0.0f;
	massData->center.SetZero();
	massData->I = 0.0f;

        return 0;
}
