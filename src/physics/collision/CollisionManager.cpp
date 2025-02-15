#include "CollisionManager.h"
#include "../PhysicsEngine.h"
#include "../../game/DynamicObjectsRenderer.h"
namespace physics{
    std::pair<bool, glm::vec2> CollisionManager::checkCollision(const std::vector<std::unique_ptr<Collider>>& firstColliders,
        const glm::vec2& firstPosition,
        const std::vector<std::unique_ptr<Collider>>& secondColliders,
        const glm::vec2& secondPosition)
    {
        if (firstColliders[0]->getType()  == Collider::ColliderType::AABB &&
            secondColliders[0]->getType() == Collider::ColliderType::AABB)
        {
            for (const auto& colliderFirst : firstColliders)
            {
                auto* firstAABB = static_cast<const AABBCollider*>(colliderFirst.get());
                for (const auto& colliderSecond : secondColliders)
                {
                    auto* secondAABB = static_cast<const AABBCollider*>(colliderSecond.get());
                    if (checkCollisionAABB_AABB(*firstAABB, firstPosition, *secondAABB, secondPosition))
                    {
                        return std::make_pair<bool, glm::vec2>(true, getCollisionLocation(*firstAABB, firstPosition, *secondAABB, secondPosition));
                    }
                }
            }
            return std::make_pair<bool, glm::vec2>(false, glm::vec2(0));
        }
        return std::make_pair<bool, glm::vec2>(false, glm::vec2(0)); //not implemented yet
    }

    void CollisionManager::handleCollision(std::shared_ptr<GameObject> first, std::shared_ptr<GameObject> second, const glm::vec2& collisionPoint)
    {
        first->OnCollisionCallback(second, collisionPoint);
        second->OnCollisionCallback(first, collisionPoint);

        switch (first->getCollisionLayer())
        {
        case Collider::CollisionLayer::Bullet:
            PhysicsEngine::addObjectToRemove(first);
        default:
            break;
        }

        switch (second->getCollisionLayer())
        {
        case Collider::CollisionLayer::Bullet:
            PhysicsEngine::addObjectToRemove(second);
        default:
            break;
        }
    }

    glm::vec2 CollisionManager::getCollisionLocation(const AABBCollider& first,
                                                     const glm::vec2& firstPosition,
                                                     const AABBCollider& second,
                                                     const glm::vec2& secondPosition)
    {
        glm::vec2 bottomLeft_first = first.getBottomLeft() + firstPosition;
        glm::vec2 topRight_first = first.getTopRight() + firstPosition;
        glm::vec2 bottomLeft_second = second.getBottomLeft() + secondPosition;
        glm::vec2 topRight_second = second.getTopRight() + secondPosition;

        return glm::vec2(
            (std::max(bottomLeft_first.x, bottomLeft_second.x) + std::min(topRight_first.x, topRight_second.x)) / 2.0f,
            (std::max(bottomLeft_first.y, bottomLeft_second.y) + std::min(topRight_first.y, topRight_second.y)) / 2.0f
        );
    }


    bool CollisionManager::checkCollisionAABB_AABB(const AABBCollider& first,
                                                   const glm::vec2& firstPosition,
                                                   const AABBCollider& second,
                                                   const glm::vec2& secondPosition)
    {
        if (!first.canCollideWith(second))
        {
            return false;
        }
        auto& bottomLeft_first  = first.getBottomLeft()  + firstPosition;
        auto& topRight_first    = first.getTopRight()    + firstPosition;
        auto& bottomLeft_second = second.getBottomLeft() + secondPosition;
        auto& topRight_second   = second.getTopRight()   + secondPosition;

        if (bottomLeft_first.x > topRight_second.x)
        {
            return false;
        }
        if (topRight_first.x < bottomLeft_second.x)
        {
            return false;
        }
        if (topRight_first.y < bottomLeft_second.y)
        {
            return false;
        }
        if (bottomLeft_first.y > topRight_second.y)
        {
            return false;
        }

        return true;
    }
}