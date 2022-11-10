#pragma once
#include "jsScene.h"
#include "jsGameObject.h"
#include "jsSceneManager.h"

namespace js
{
	namespace object
	{
		// ���ӿ�����Ʈ ���� �Լ�
		template <typename T>
		static __forceinline T* Instantiate(eColliderLayer type)
		{
			T* gameObject = new T();
			Scene* scene = SceneManager::GetCurScene();
			scene->AddGameObject(dynamic_cast<GameObject*>(gameObject), type);

			return gameObject;
		}
		template <typename T>
		static __forceinline T* Instantiate(eColliderLayer type, Pos pos)
		{
			T* gameObject = new T(pos);
			Scene* scene = SceneManager::GetCurScene();
			scene->AddGameObject(dynamic_cast<GameObject*>(gameObject), type);

			return gameObject;
		}

		static __forceinline void Destroy(GameObject* target)
		{
			target->Death();
		}

		static __forceinline void Destroy(GameObject* target, float time)
		{
			target->SetDeath(time);
		}

		static __forceinline void Release()
		{
			Scene* scene = SceneManager::GetCurScene();
			GameObjects objects = scene->GetGameObjects();
			
			for (size_t y = 0; y < _COLLIDER_LAYER; y++)
			{
				for (std::vector<GameObject*>::iterator iter = objects[y].begin(); iter != objects[y].end();)
				{
					if (true == (*iter)->IsDeath())
					{
						iter = objects[y].erase(iter);
						continue;
					}
					++iter;
				}
			}
		}
	}
}