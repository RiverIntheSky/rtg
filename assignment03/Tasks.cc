#include "AI.hh"

#include <algorithm>
#include <cassert>

#include <glow/common/log.hh>

#include <glm/ext.hpp>

#include "Components.hh"

/// Note: Entity is NOT included.
/// You are not allowed to change any component
/// All information is given and the only side effect should be the return value

using namespace ai;

float ai::simpleAI(size_t paddleIdx,
                   const Paddle& paddle,
                   const std::vector<Paddle>& allPaddles,
                   const std::vector<Ball>& balls,
                   const Parameters& params,
                   float elapsedSeconds,
                   glm::vec3& debugColor)
{
    auto maxAccel = params.paddleMaxAcceleration;

    // brake acceleration always reduces velocity
    auto brakeAccel = maxAccel * glm::sign(-paddle.transform->velocity.y);

    if (paddleIdx >= balls.size())
        return brakeAccel; // we don't have any ball -> brake

    // i-th paddle takes i-th ball
    auto ballY = balls[paddleIdx].transform->position.y;

    auto dy = ballY - paddle.transform->position.y;
    dy -= glm::min(paddle.shape->halfExtent.y * 0.6f, glm::abs(dy)) * glm::sign(dy);

    if (glm::abs(paddle.transform->velocity.y) < 0.1) // accelerate towards dy if no velocity
    {
        debugColor = {1, 1, 1}; // no velocity? -> black
        return maxAccel * glm::sign(dy);
    }

    auto arrivalTime = dy / paddle.transform->velocity.y;
    auto brakeTime = glm::abs(paddle.transform->velocity.y) / maxAccel * 1.5f; // 50% braking margin

    auto hasVelo = glm::abs(paddle.transform->velocity.y) > 400; // used to prevent flickering at target

    if (brakeTime < arrivalTime) // we have time to brake -> we can accelerate towards dy
    {
        debugColor = hasVelo ? glm::vec3(0, 1, 0) : glm::vec3(1, 1, 1); // accelerating -> green
        return maxAccel * glm::sign(dy);
    }
    else // .. otherwise brake
    {
        debugColor = hasVelo ? glm::vec3(1, 0, 0) : glm::vec3(1, 1, 1); // braking -> red
        return brakeAccel;
    }
}

float ai::task2a(size_t paddleIdx,
                 Paddle const& paddle,
                 std::vector<Paddle> const& allPaddles,
                 std::vector<Ball> const& balls,
                 Parameters const& params,
                 float elapsedSeconds,
                 glm::vec3& debugColor)
{
    /// Task 2.a
    /// For the paddle with index "paddleIdx", the paddle position
    /// can be controlled only indirectely by returning an acceleration value.
    /// You cannot set any component properties directly.
    ///
    /// Your job is to:
    ///     - accelerate the paddle so that it always collides with the ball
    ///     - make sure the ball hits almost exactly the paddle center
    ///
    /// Notes:
    ///     - you can assume the paddle to be the left one
    ///     - the ball will always move horizontally from right to left
    ///     - you can slow down if the acceleration and velocity go in opposite directions
    ///     - the return value is clamped to +- params.paddleMaxAcceleration
    ///     - have a look at the console output to see where the ball hit the paddle
    ///       (It should be between 45% and 55% except at field boundaries)
    ///     - For debugging purposes, you can set the debugColor of the paddle
    ///     - when the ball is moving away from you we recommend returning to the center
    ///
    /// ============= STUDENT CODE BEGIN =============

    auto maxAccel = params.paddleMaxAcceleration;
    float dis;
    Ball ball = balls.front();
    if(ball.transform->velocity.x > 0) {
        dis = params.fieldHeight/2 - paddle.transform->position.y;
    } else {
        dis = glm::clamp(ball.transform->position.y, paddle.shape->halfExtent.y, params.fieldHeight - paddle.shape->halfExtent.y) - paddle.transform->position.y;
    }

    auto a = glm::sign(dis) * maxAccel;
    if (glm::abs(paddle.transform->velocity.y + a * elapsedSeconds) > glm::sqrt(2 * a * dis))
        a = -a;

    // adjust acceleration if close enough so that the paddle stops
    if (glm::abs(dis) < 0.1*paddle.shape->halfExtent.y) {
        if (dis != 0.f) {
            a = - glm::pow2(paddle.transform->velocity.y) / (2 * dis);
        } else {
            a = -paddle.transform->velocity.y/elapsedSeconds;
        }
    }
    return a;

    /// ============= STUDENT CODE END =============
}
float ai::task2b(size_t paddleIdx,
                 Paddle const& paddle,
                 std::vector<Paddle> const& allPaddles,
                 std::vector<Ball> const& balls,
                 Parameters const& params,
                 float elapsedSeconds,
                 glm::vec3& debugColor)
{
    /// Task 2.b
    /// Here, wall reflections have to be taken into account,
    /// i.e. the ball does not only move horizontally.
    ///
    /// Your job is to:
    ///     - predict the ball trajectory incl. all reflections
    ///     - return the acceleration the paddle needs to reach the predicted position in time
    ///     - make sure the ball hits almost exactly the paddle center (exception: field boundary)
    ///
    /// Notes:
    ///     - don't forget the paddle extent
    ///     - don't forget the ball radius when predicting reflections
    ///     - you can use `glow::info() << targetY;` to see if your prediction is stable
    ///     - when the ball is moving away from you we recommend returning to the center
    ///
    /// ============= STUDENT CODE BEGIN =============

    auto maxAccel = params.paddleMaxAcceleration;
    Ball ball = balls.front();
    float dis;

    if(ball.transform->velocity.x > 0) {
        dis = params.fieldHeight/2 - paddle.transform->position.y;
    } else {

        // position and time of the ball hitting the paddle
        auto hit_x = paddle.transform->position.x + ball.shape->radius + paddle.shape->halfExtent.x;
        auto hit_t = (hit_x - ball.transform->position.x) / ball.transform->velocity.x;
        auto hit_y = ball.transform->position.y + ball.transform->velocity.y * hit_t;

        // f(x + T) = f(T), T = 2 * params.fieldHeight - 4 * ball.shape->radius
        auto period = 2 * params.fieldHeight - 4 * ball.shape->radius;
        while (hit_y > (period + ball.shape->radius))
            hit_y -= period;
        while (hit_y < ball.shape->radius)
            hit_y += period;

        if (hit_y > (period/2 + ball.shape->radius))
            hit_y = period + 2 * ball.shape->radius - hit_y;

        dis = glm::clamp(hit_y, paddle.shape->halfExtent.y, params.fieldHeight - paddle.shape->halfExtent.y) - paddle.transform->position.y;
    }

    auto a = glm::sign(dis) * maxAccel;
    if (glm::abs(paddle.transform->velocity.y + a * elapsedSeconds) > glm::sqrt(2 * a * dis))
        a = -a;

    // adjust acceleration if close enough so that the paddle stops
    if (glm::abs(dis) < 0.2*paddle.shape->halfExtent.y) {
        if (dis != 0.f) {
            a = - glm::pow2(paddle.transform->velocity.y) / (2 * dis);
        } else {
            a = -paddle.transform->velocity.y/elapsedSeconds;
        }
    }
    return a;

    /// ============= STUDENT CODE END =============
}
float ai::task2c(size_t paddleIdx,
                 Paddle const& paddle,
                 std::vector<Paddle> const& allPaddles,
                 std::vector<Ball> const& balls,
                 Parameters const& params,
                 float elapsedSeconds,
                 glm::vec3& debugColor)
{
    /// Task 2.c
    /// The paddle should be able to control where the ball arrives on the other side.
    /// Here, every reflected ball should arive at the center of the right side.
    ///
    /// Your job is to:
    ///     - Hit the ball so that its destination is the center of the right side
    ///     - if it is impossible to reflect the ball towards the right center, do not hit it at all
    ///
    /// Notes:
    ///     - this tasks exploits the mechanic that you implemented in 1.b
    ///     - don't forget the paddle extent
    ///     - don't forget the ball radius when predicting reflections
    ///     - you may have to use a reflection to hit the opposite center
    ///     - when the ball is moving away from you we recommend returning to the center
    ///
    /// ============= STUDENT CODE BEGIN =============

    auto maxAccel = params.paddleMaxAcceleration;
    Ball ball = balls.front();
    float dis;

    if(ball.transform->velocity.x > 0) {
        dis = params.fieldHeight/2 - paddle.transform->position.y;
    } else {

        // position and time of the ball hitting the paddle
        auto hit_x = paddle.transform->position.x + ball.shape->radius + paddle.shape->halfExtent.x;
        auto hit_t = (hit_x - ball.transform->position.x) / ball.transform->velocity.x;
        auto hit_y = ball.transform->position.y + ball.transform->velocity.y * hit_t;

        // f(x + T) = f(T), T = 2 * params.fieldHeight - 4 * ball.shape->radius
        auto period = 2 * params.fieldHeight - 4 * ball.shape->radius;
        while (hit_y > (period + ball.shape->radius))
            hit_y -= period;
        while (hit_y < ball.shape->radius)
            hit_y += period;

        glm::vec2 reflected_v = {-ball.transform->velocity.x, ball.transform->velocity.y};
        if (hit_y > (period/2 + ball.shape->radius)) {
            hit_y = period + 2 * ball.shape->radius - hit_y;
            reflected_v = {-ball.transform->velocity.x, -ball.transform->velocity.y};
        }

        int cases = -1;
        float t, d_y;
        glm::vec2 g;
        do {
            if (cases > 1) {
                d_y = hit_y;
                break;
            }
            // desired velocity direction to hit the opposite center
            glm::vec2 d_v = normalize(glm::vec2(params.fieldWidth, params.fieldHeight/2*(1+2*cases) - 2*cases*ball.shape->radius) - glm::vec2(hit_x, hit_y));

            // guiding direction
            g = - reflected_v + 2 * dot(reflected_v, d_v) * d_v;

            // relative hit position on the paddle
            t = ((g / g.x).y + 1) / 2;

            // position that the paddle should move to
            d_y = hit_y - 2 * paddle.shape->halfExtent.y * t + paddle.shape->halfExtent.y;
            cases++;

        } while (glm::abs(glm::atan(g.y, g.x)) > glm::pi<float>()/4 || d_y < paddle.shape->halfExtent.y || d_y > params.fieldHeight - paddle.shape->halfExtent.y);
        glow::info() << cases;

        dis = d_y - paddle.transform->position.y;
    }

    auto a = glm::sign(dis) * maxAccel;
    if (glm::abs(paddle.transform->velocity.y + a * elapsedSeconds) > glm::sqrt(2 * a * dis))
        a = -a;

    // adjust acceleration if close enough so that the paddle stops
    if (glm::abs(dis) < 0.1*paddle.shape->halfExtent.y) {
        if (dis != 0.f) {
            a = - glm::pow2(paddle.transform->velocity.y) / (2 * dis);
        } else {
            a = -paddle.transform->velocity.y/elapsedSeconds;
        }
    }

    return a;

    /// ============= STUDENT CODE END =============
}

float ai::task3(size_t paddleIdx,
                Paddle const& paddle,
                std::vector<Paddle> const& allPaddles,
                std::vector<Ball> const& balls,
                Parameters const& params,
                float elapsedSeconds,
                glm::vec3& debugColor)
{
    /// Task 3
    /// Try to direct the ball so that the enemy AI (right paddle) has a hard time reaching it!
    ///
    /// Your job is to:
    ///     - write an artificial intelligence that beats the enemy AI
    ///
    /// Notes:
    ///     - you actually control three paddles, but this method is called
    ///       once for every one of those (with different paddleIdx and paddle)
    ///     - your AI must be fair, i.e. the return value of this method is
    ///       the only way to change the global state (no memhacks, no calling our AI, etc.)
    ///     - you may take a look at simpleAI(). It should be easy to beat if you've done 2a-2c.
    ///
    /// ============= STUDENT CODE BEGIN =============

    auto maxAccel = params.paddleMaxAcceleration;

    struct ballData {
        float hit_t;
        float hit_y;
        float hit_x;
        glm::vec2 reflected_v;
    } b;

    std::vector<ballData> bds;
    Ball ball = balls.front();

    for (auto ball: balls) {
        glow::info() << "how many balls" << ball.transform->velocity.x;
        if(ball.transform->velocity.x < 0) {
            b.hit_x = paddle.transform->position.x + ball.shape->radius + paddle.shape->halfExtent.x;
            b.hit_t = (b.hit_x - ball.transform->position.x) / ball.transform->velocity.x;
            b.reflected_v = {-ball.transform->velocity.x, ball.transform->velocity.y};
        } else {
            b.hit_x = allPaddles[4].transform->position.x - ball.shape->radius - paddle.shape->halfExtent.x;
            b.hit_t = (2 * b.hit_x - ball.transform->position.x - paddle.transform->position.x - ball.shape->radius - paddle.shape->halfExtent.x) / ball.transform->velocity.x;
            b.reflected_v = -ball.transform->velocity;
        }
        // compute hit_y
        b.hit_y = ball.transform->position.y + ball.transform->velocity.y * b.hit_t;

        auto period = 2 * params.fieldHeight - 4 * ball.shape->radius;
        while (b.hit_y > (period + ball.shape->radius))
            b.hit_y -= period;
        while (b.hit_y < ball.shape->radius)
            b.hit_y += period;
        if (b.hit_y > (period/2 + ball.shape->radius)) {
            b.hit_y = period + 2 * ball.shape->radius - b.hit_y;
            b.reflected_v = {b.reflected_v.x, -b.reflected_v.y};
        }
        bds.push_back(b);
    }

    sort(bds.begin( ), bds.end( ), [](const ballData& lhs, const ballData& rhs) {
       return lhs.hit_t < rhs.hit_t;
    });

    if (bds.front().hit_t < 0.f) {
        debugColor = {0.5f,0.5f,0.f};
    }


    struct paddleData {
        float dis_temp;
        float dis;
        float d_y = 0.f;
    };

    std::vector<paddleData> pds(allPaddles.size() / 2);
    std::vector<float> oppositePaddle;
    float t, r_y, d_y;
    glm::vec2 g;

    for (size_t i = 0; i != allPaddles.size(); i++) {
        if (allPaddles[i].owner != paddle.owner) {
            oppositePaddle.push_back(allPaddles[i].transform->position.y);
        }
    }

//    auto meanPos = std::accumulate(oppositePaddle.begin(), oppositePaddle.end(), 0) / oppositePaddle.size();
    float sum_pos = 0.f;
    std::for_each(oppositePaddle.rbegin(), oppositePaddle.rend(), [&](int n) { sum_pos += n; });
    float meanPos = sum_pos / allPaddles.size() * 2;

    glow::info() << "meanPos" << meanPos;

    if (meanPos < params.fieldHeight / 4) {
        r_y = params.fieldHeight - ball.shape->radius;
    } else {
        r_y = ball.shape->radius;
    }
    r_y = ball.shape->radius;

    for (auto bd: bds) {
        int cases = -1;
        do {
            if (cases > 1) {
                d_y = bd.hit_y;
                glow::info() << "failed";
                break;
            }
            // desired velocity direction to hit the opposite side
            glm::vec2 d_v = normalize(glm::vec2(params.fieldWidth, r_y + 2*cases*(params.fieldHeight-2*ball.shape->radius)) - glm::vec2(bd.hit_x, bd.hit_y));

            // guiding direction
            g = - b.reflected_v + 2 * dot(b.reflected_v, d_v) * d_v;

            // relative hit position on the paddle
            t = ((g / g.x).y + 1) / 2;

            // position that the paddle should move to
            d_y = bd.hit_y - 2 * paddle.shape->halfExtent.y * t + paddle.shape->halfExtent.y;

            cases++;
//            glow::info() << "g " << normalize(g);
//            glow::info() << "atan " << glm::abs(glm::atan(g.y, g.x));
//            glow::info() << "d_y " << d_y;


        } while (glm::abs(glm::atan(g.y, g.x)) > glm::pi<float>()/4 || d_y < paddle.shape->halfExtent.y || d_y > params.fieldHeight - paddle.shape->halfExtent.y);


        for (size_t i = 0; i != allPaddles.size(); i++) {
            if (allPaddles[i].owner == paddle.owner) {
                if (pds[i].d_y < 1)
                    pds[i].dis_temp = d_y - allPaddles[i].transform->position.y;
            }
        }
        size_t j = 3; float min_dis  = params.fieldHeight;
        for (size_t i = 0; i < allPaddles.size() / 2; i++) {
//            glow::info() << "dis " << abs(pds[i].dis_temp);
            if (abs(pds[i].dis_temp) < min_dis) {
//                glow::info() << i << " smaller";
                j = i; min_dis = abs(pds[i].dis_temp);
            }
        }
        if (j != 3) {
            pds[j].d_y = d_y;
            glow::info() << "d_y " << d_y;
            glow::info() << "bd.hit_t " << bd.hit_t;
            glow::info() << "which paddle " << j;
            pds[j].dis = pds[j].dis_temp;
            pds[j].dis_temp = params.fieldHeight;
        }

    }

    for (size_t i = 0; i < allPaddles.size() / 2; i++) {
        if (pds[i].d_y < 1) {
//            glow::info() << "which idle " << i;
            pds[i].d_y = params.fieldHeight / 2;
            pds[i].dis = params.fieldHeight / 2 - allPaddles[i].transform->position.y;
        }
    }

    auto dis = pds[paddleIdx].dis;
    glow::info() << "this paddle " << paddleIdx;
    glow::info() << "d_y " << pds[paddleIdx].d_y;
    glow::info() << "real_y " << allPaddles[paddleIdx].transform->position.y;

    auto a = glm::sign(dis) * maxAccel;
    if (glm::abs(paddle.transform->velocity.y + a * elapsedSeconds) > glm::sqrt(2 * a * dis))
        a = -a;

    // adjust acceleration if close enough so that the paddle stops
    if (glm::abs(dis) < 0.1*paddle.shape->halfExtent.y) {
        if (dis != 0.f) {
            a = - glm::pow2(paddle.transform->velocity.y) / (2 * dis);
        } else {
            a = -paddle.transform->velocity.y/elapsedSeconds;
        }
    }

    glow::info();

    return a;


    /// ============= STUDENT CODE END =============
}
