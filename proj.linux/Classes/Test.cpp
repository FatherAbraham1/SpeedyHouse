#include <Box2D/Box2D.h>
#include "GLES-Render.cpp"

#include <cstdlib>
#include <stdio.h>

class Test;
struct Settings;

typedef Test* TestCreateFcn();

struct Settings
{
    Settings() :
        viewCenter(0.0f, 20.0f),
        hz(60.0f),
        velocityIterations(8),
        positionIterations(3),
        drawShapes(1),
        drawJoints(1),
        drawAABBs(0),
        drawPairs(0),
        drawContactPoints(0),
        drawContactNormals(0),
        drawContactForces(0),
        drawFrictionForces(0),
        drawCOMs(0),
        drawStats(0),
        drawProfile(0),
        enableWarmStarting(1),
        enableContinuous(1),
        enableSubStepping(0),
        pause(0),
        singleStep(0)
        {}

    b2Vec2 viewCenter;
    float32 hz;
    int32 velocityIterations;
    int32 positionIterations;
    int32 drawShapes;
    int32 drawJoints;
    int32 drawAABBs;
    int32 drawPairs;
    int32 drawContactPoints;
    int32 drawContactNormals;
    int32 drawContactForces;
    int32 drawFrictionForces;
    int32 drawCOMs;
    int32 drawStats;
    int32 drawProfile;
    int32 enableWarmStarting;
    int32 enableContinuous;
    int32 enableSubStepping;
    int32 pause;
    int32 singleStep;
};

const int32 k_maxContactPoints = 2048;

struct ContactPoint
{
    b2Fixture* fixtureA;
    b2Fixture* fixtureB;
    b2Vec2 normal;
    b2Vec2 position;
    b2PointState state;
};



class QueryCallback : public b2QueryCallback
{
public:
    QueryCallback(const b2Vec2& point)
    {
        m_point = point;
        m_fixture = NULL;
    }

    bool ReportFixture(b2Fixture* fixture)
    {
        b2Body* body = fixture->GetBody();
        if (body->GetType() == b2_dynamicBody)
        {
            bool inside = fixture->TestPoint(m_point);
            if (inside)
            {
                m_fixture = fixture;

                // We are done, terminate the query.
                return false;
            }
        }

        // Continue the query.
        return true;
    }

    b2Vec2 m_point;
    b2Fixture* m_fixture;
};

class Test : public b2ContactListener
{
public:

    Test()
    { 
        b2Vec2 gravity;
        gravity.Set(0.0f, -10.0f);
        m_world = new b2World(gravity);
        m_bomb = NULL;
        m_textLine = 30;
        m_mouseJoint = NULL;
        m_pointCount = 0;

        m_world->SetContactListener(this);
        m_world->SetDebugDraw(&m_debugDraw);

        m_stepCount = 0;

        b2BodyDef bodyDef;
        m_groundBody = m_world->CreateBody(&bodyDef);

        memset(&m_maxProfile, 0, sizeof(b2Profile));
        memset(&m_totalProfile, 0, sizeof(b2Profile));
    }

    ~Test()
    {
        // By deleting the world, we delete the bomb, mouse joint, etc.
        delete m_world;
        m_world = NULL;
    }

    void Step(Settings* settings)
    {
        float32 timeStep = settings->hz > 0.0f ? 1.0f / settings->hz : float32(0.0f);

        uint32 flags = 0;
        flags += settings->drawShapes            * b2Draw::e_shapeBit;
        flags += settings->drawJoints            * b2Draw::e_jointBit;
        flags += settings->drawAABBs            * b2Draw::e_aabbBit;
        flags += settings->drawPairs            * b2Draw::e_pairBit;
        flags += settings->drawCOMs                * b2Draw::e_centerOfMassBit;
        m_debugDraw.SetFlags(flags);

        m_world->SetWarmStarting(settings->enableWarmStarting > 0);
        m_world->SetContinuousPhysics(settings->enableContinuous > 0);
        m_world->SetSubStepping(settings->enableSubStepping > 0);

        m_pointCount = 0;

        m_world->Step(timeStep, settings->velocityIterations, settings->positionIterations);

        m_world->DrawDebugData();

        if (timeStep > 0.0f)
        {
            ++m_stepCount;
        }
    }








bool MouseDown(const b2Vec2& p)
{
    m_mouseWorld = p;
    
    if (m_mouseJoint != NULL)
    {
        return false;
    }

    // Make a small box.
    b2AABB aabb;
    b2Vec2 d;
    d.Set(0.001f, 0.001f);
    aabb.lowerBound = p - d;
    aabb.upperBound = p + d;

    QueryCallback callback(p);
    m_world->QueryAABB(&callback, aabb);

    if (callback.m_fixture)
    {
        b2Body* body = callback.m_fixture->GetBody();
        b2MouseJointDef md;
        md.bodyA = m_groundBody;
        md.bodyB = body;
        md.target = p;
        md.maxForce = 1000.0f * body->GetMass();
        m_mouseJoint = (b2MouseJoint*)m_world->CreateJoint(&md);
        body->SetAwake(true);
        return true;
    }
    return false;
}

void ShiftMouseDown(const b2Vec2& p)
{
    m_mouseWorld = p;
    
    if (m_mouseJoint != NULL)
    {
        return;
    }
}

void MouseUp(const b2Vec2& p)
{
    if (m_mouseJoint)
    {
        m_world->DestroyJoint(m_mouseJoint);
        m_mouseJoint = NULL;
    }
}

void MouseMove(const b2Vec2& p)
{
    m_mouseWorld = p;
    
    if (m_mouseJoint)
    {
        m_mouseJoint->SetTarget(p);
    }
}

public:
    friend class DestructionListener;
    friend class BoundaryListener;
    friend class ContactListener;

    b2Body* m_groundBody;
    b2AABB m_worldAABB;
    ContactPoint m_points[k_maxContactPoints];
    int32 m_pointCount;
    GLESDebugDraw m_debugDraw;
    int32 m_textLine;
    b2World* m_world;
    b2Body* m_bomb;
    b2MouseJoint* m_mouseJoint;
    b2Vec2 m_bombSpawnPoint;
    b2Vec2 m_mouseWorld;
    int32 m_stepCount;

    b2Profile m_maxProfile;
    b2Profile m_totalProfile;
};