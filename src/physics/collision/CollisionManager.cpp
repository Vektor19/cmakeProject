#include "CollisionManager.h"
#include "../PhysicsEngine.h"
#include "../../game/DynamicObjectsRenderer.h"
namespace physics{
    bool CollisionManager::checkCollision(const std::vector<std::unique_ptr<Collider>>& firstColliders,
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
                        return true;
                    }
                }
            }
            return false;
        }
        return false; //not implemented yet
    }

    void CollisionManager::handleCollision(std::shared_ptr<GameObject> first, std::shared_ptr<GameObject> second)
    {
        first->OnCollisionCallback(second);
        second->OnCollisionCallback(first);

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