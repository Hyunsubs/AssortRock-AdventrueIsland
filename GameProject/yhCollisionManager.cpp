#include "yhCollisionManager.h"
#include "yhScene.h"
#include "yhSceneManager.h"

namespace yh
{
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};
	std::bitset<LAYER_MAX> CollisionManager::mLayerMasks[LAYER_MAX] = {};

	void CollisionManager::Initialize()
	{
	}
	void CollisionManager::Update()
	{
		Scene* activeScene = SceneManager::GetActiveScene();
		for (int row = 0; row < LAYER_MAX; row++)
		{
			for (int col = 0; col < LAYER_MAX; col++)
			{
				if (mLayerMasks[row][col] == true)
				{
					LayerCollision(activeScene,(eLayerType)row, (eLayerType)col);
				}
			}
		}
	}
	void CollisionManager::Render(HDC hdc)
	{
	}
	void CollisionManager::Release()
	{
	}
	void CollisionManager::Clear()
	{
		mLayerMasks->reset();
		mCollisionMap.clear();
	}
	void CollisionManager::CollisionLayerCheck(eLayerType left, eLayerType right, bool enable)
	{
		int row = -1;
		int col = -1;
		
		if (left > right)
		{
			row = (UINT)left;
			col = (UINT)right;
		}
		else
		{
			col = (UINT)left;
			row = (UINT)right;
		}

		mLayerMasks[row][col] = enable;
	}
	void CollisionManager::LayerCollision(Scene* scene,eLayerType left, eLayerType right)
	{
		//finds left layer Object


		//finds right layer Object

		Layer& leftLayer = scene->GetLayer(left);
		std::vector<GameObject*> lefts = leftLayer.GetGameObject();

		Layer& rightLayer = scene->GetLayer(left);
		std::vector<GameObject*> rights = rightLayer.GetGameObject();

		for  (GameObject* left: lefts)
		{
			Collider* leftCol = left->GetComponent<Collider>();
			if (leftCol == nullptr)
				continue;
			for (GameObject* right : rights)
			{
				Collider* rightCol = right->GetComponent<Collider>();
				if (rightCol == nullptr)
					continue;
				if (left == right)
					continue;

				ColliderCollision(leftCol, rightCol);
			}

		}


	}
	void CollisionManager::ColliderCollision(Collider* left, Collider* right)
	{
		//�� �浹ü�� ID�� Ȯ��
		ColliderID ID;
		ID.left = (UINT)left;
		ID.right = (UINT)right;



		//���� �浹ü�� ������ �����ͼ� Ȯ���Ѵ�.
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(ID.id);


		//Ȥ�� �浹 ������ ���ٸ� �������ָ� �ȴ�.
		if (iter == mCollisionMap.end())
		{
			mCollisionMap.insert(std::make_pair(ID.id, false));
			iter = mCollisionMap.find(ID.id);
		}

		//�浹�Լ� ȣ��

		if (Intersect(left, right))
		{
			//�浹���λ���
			if (iter->second == false)
			{
				left->OnCollisionEnter(right);
				right->OnCollisionEnter(left);

				iter->second = true;
	
			}
			//ó�� �浹�� ����
			else
			{
				

				left->OnCollisionStay(right);
				right->OnCollisionStay(left);

				iter->second = true;
			}
		}
		//�浹 ����
		else
		{
			//�浹 ���ߴµ� ������ �� ���� (�浹�� �������� ����)
			if (iter->second == true)
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);

				iter->second = false;
			}
		}

	}
	bool CollisionManager::Intersect(Collider* left, Collider* right)
	{
		Vector2 leftPos = left->GetPosition();
		Vector2 rightPos = right->GetPosition();

		Vector2 leftSize = left->GetSize();
		Vector2 rightSize = right->GetSize();

		if (fabs(leftPos.x - rightPos.x) < fabs(leftSize.x / 2.0f + rightSize.x / 2.0f)
			&& fabs(leftPos.y - rightPos.y) < fabs(leftSize.y / 2.0f + rightSize.y / 2.0f))
		{
			return true;
		}



		return false;
	}
}