#include <assert.h>
#include <math.h>
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <time.h>

// Global angle offset
//
// To make working with the time and angle of the hands easier, this
// angle offset is applied to all angle measurements to shift 0 degrees
// to be full vertical (12 o'clock position). To make things consistent,
// the offset should be applied at the point nearest drawing.
static const float DEG_ANGLE_OFFSET = -90.0f;

// Number of degrees between the units of time
static const float DEG_PER_SECOND = 360.0f / 60.0f;
static const float DEG_PER_MINUTE = DEG_PER_SECOND;
static const float DEG_PER_HOUR   = 360.0f / 12.0f;

// Thicknesses of the different hands
static const float SECOND_HAND_THICKNESS = 2.0f;
static const float MINUTE_HAND_THICKNESS = 2.0f * SECOND_HAND_THICKNESS;
static const float HOUR_HAND_THICKNESS   = 2.0f * MINUTE_HAND_THICKNESS;


typedef struct
{
    Vector2 center;
    float   radius;
} Clock;


Vector2 PolarToRectangular(float mag, float thetaDegrees)
{
    return (Vector2) {
        .x = mag * cosf(thetaDegrees * DEG2RAD),
        .y = mag * sinf(thetaDegrees * DEG2RAD)
    };
}

Vector3 UpdateHandAngles(const struct tm *currTime)
{
    // seconds
    const float secondsAngleDegrees = currTime->tm_sec * DEG_PER_SECOND;

    // The minutes and hours hand will move between marks based on where the
    // lower magnitude hand is located. As an approximation, the additional
    // angle is computed as the ratio of the magnitude. The ratio is based off
    // the lower magnitude hand angle over 360 degrees. To prevent small
    // rounding errors from causing jitter on the hand, the lower magnitude
    // component is checked directly when close to the 12 o'clock position.

    // minutes
    float minutesRatio = secondsAngleDegrees / 360.0f;
    if (0 == currTime->tm_sec)
    {
        minutesRatio = 0.0f;
    }

    const float minutesAngleDegrees = (currTime->tm_min + minutesRatio)* DEG_PER_MINUTE;

    // hours
    float hoursRatio = minutesAngleDegrees / 360.0;
    if (0 == currTime->tm_min)
    {
        hoursRatio = 0.0f;
    }

    const int   currHour = currTime->tm_hour % 12;
    const float hoursAngleDegrees = (currHour + hoursRatio) * DEG_PER_HOUR;

    return (Vector3){
        .x = secondsAngleDegrees,
        .y = minutesAngleDegrees,
        .z = hoursAngleDegrees
    };
}

void DrawTicks(const Clock *c)
{
    for (int minMark = 0; minMark < 60; ++minMark)
    {
        const float angle = minMark * (360.0f / 60.0f) + DEG_ANGLE_OFFSET;

        float tickThickness = SECOND_HAND_THICKNESS;
        float tickScale     = 0.95f; // % length of radius (scale of the white space not tick)
        if (0 == (minMark % 5)) {
            tickThickness = MINUTE_HAND_THICKNESS;
            tickScale     = 0.9f;
        }

        // We can think the tick marks around the clock face as polar coordinates
        // and convert those polar coordinates into the rectangular (x, y) used
        // by the drawing functions.
        const Vector2 startOffset = PolarToRectangular(c->radius, angle);
        const Vector2 endOffset   = PolarToRectangular(c->radius * tickScale, angle);

        const Vector2 start = {
            .x = c->center.x + startOffset.x,
            .y = c->center.y + startOffset.y
        };

        const Vector2 end = {
            .x = c->center.x + endOffset.x,
            .y = c->center.y + endOffset.y
        };

        DrawLineEx(start, end, tickThickness, GRAY);
    }
}

void DrawHand(const Clock *c, float length, float angleDegrees, float thinkness, Color color)
{
    const float drawingAngle = angleDegrees + DEG_ANGLE_OFFSET;
    const Vector2 endOffset  = PolarToRectangular(length, drawingAngle);

    const Vector2 start = c->center;
    const Vector2 end   = {
        .x = c->center.x + endOffset.x,
        .y = c->center.y + endOffset.y
    };

    DrawLineEx(start, end, thinkness, color);
}

void DrawHingePin(const Clock *c)
{
    const float pinRadius = 0.03 * c->radius;
    DrawCircleV(c->center, pinRadius, DARKGRAY);
}


int main(void)
{
    const int width  = 800;
    const int height = 600;

    const Clock c = {
        .center = { .x = width / 2.0f, .y = height / 2.0f },
        .radius = (height / 2.0f) * 0.9f
    };

    SetTargetFPS(60);
    InitWindow(width, height, "Clock Application");

    while (!WindowShouldClose())
    {
        const time_t now = time(NULL);
        const struct tm *nowLocal = localtime(&now);

        // Compute the angle of the clock hands based on the current time.
        // Vector component breakdown:
        //  x - seconds hand angle
        //  y - minutes hand angle
        //  z - hours hand angle
        const Vector3 handAnglesDegrees = UpdateHandAngles(nowLocal);

        BeginDrawing();
            ClearBackground(BLACK);
            DrawCircleV(c.center, c.radius, RAYWHITE);
            DrawTicks(&c);
            DrawHand(&c, c.radius * 0.70, handAnglesDegrees.z, HOUR_HAND_THICKNESS,   RED);
            DrawHand(&c, c.radius * 0.90, handAnglesDegrees.y, MINUTE_HAND_THICKNESS, BLUE);
            DrawHand(&c, c.radius * 0.97, handAnglesDegrees.x, SECOND_HAND_THICKNESS, GOLD);
            DrawHingePin(&c);
            DrawFPS(5, 5);
        EndDrawing();
    }

    CloseWindow();

    return 0;
}