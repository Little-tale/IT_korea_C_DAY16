#include "../../headers/structure.h"

//�������� ������� ������ ������ �ڷᱸ��
// stack �ڷ� ���� -> �������� ���Է� �� ���

//������ -> �����͸� �����ϴµ� �ʹ� ��ƴ�.
// �л��� ������ �����ϴ� ���α׷��̳�
// �������� ���α׷�
// ��� ���� ���α׷�
// ������ ��ŷ �ý��� - 30�и���, ���ΰ�ħ


// �����͸� �����ϴ� ��� -> ���ı��, ��������, ������, ������,...

// �ƿ� �����͸� ������� �Է��ϴ� ����� ����� ���� ������?
// �����Ͱ� �߰� �Ǹ鼭 �ڵ����� ������� ����� ���� ��ұ�?

// ����Ʈ�� ���� -> �����͸� �߰��Ҷ� �ڵ����� ������� ���Ľ�Ű�鼭 �߰��ϴ� �ڷᱸ��.
// �������� ������ ����µ� -> 

// ���� ���
	// 1~ 1000���� �߿� ���� 1���� �����Ͻÿ� 2^10 10���� ������.
	
	// ����Ʈ�� -> �����Ϳ� ������ ���� �˻� �ӵ��� ������ �ϴ� �ڷᱸ��.

typedef struct ControlData {
	Dec number;
}ControlData,*pControlData;


typedef struct Node {
	pControlData data;
	struct Node* left;
	struct Node* right;
	struct Node* parent;
}Node, *pNode;




typedef struct BinaryTree {
	pNode root;
	Dec(*comp)(pControlData, pControlData);

}BinaryTree, *pBinaryTree;

pBinaryTree CreateBinaryTree(Dec(*comp)(pControlData, pControlData)) {

	pBinaryTree result = Allocation(sizeof(BinaryTree));
	result->comp = comp;

	return result;
}


Void ReleaseNode(pNode now) {
	if (!now) return 0;
	ReleaseNode(now->left);
	ReleaseNode(now->right);
	free(now->data);
	free(now);

}


Void ReleaseBinaryTree(pBinaryTree this) {
	ReleaseNode(this->root);
	free(this);
}


pControlData CD(Dec number) {
	pControlData cd = Allocation(sizeof(ControlData));
	cd->number = number;
	return cd;
}


Dec CompareUp(pControlData origin, pControlData other) {
	return origin->number > other->number;
}

Dec CompareDown(pControlData origin, pControlData other) {
	return origin->number < other->number;
}





Void InsertBinaryTree(pBinaryTree this, pBinaryTree data)
{
	pNode node = Allocation(sizeof(Node));
	node->data = data;
	if (this->root) {
		pNode now = this->root;
		while (1)
		{
			if (this->comp(now->data, node->data))
			{
				//�¾�����
				if (now->left)
				{
					now = now->left;
				}
				else {
					now->left = node;
					node->parent = now;
					break;
				}
			}
			else {
				//Ʋ������
				if (now->right) now = now->right;
				else {
					now->right = node;
					node->parent = now;
					break;
				}
			}

		}
	}
	else {
		this->root = node;
	}
}

pControlData FindCDVinaryTree(pBinaryTree this, pControlData data, Dec index)
{
	if (!this->root) return 0;
	if (index < 0) index = 0;
	pNode now = this->root;
	while (1) {
		if (!now) {
			free(data);
			return 0;
		}
		if (now->data->number == data->number) {
			if (index) {
				--index;
				if (this->comp(now->data, data)) now = now->left;
				else now = now->right;
			}
			else
			{
				free(data);
				return now->data;
			}
		}
		else if (this->comp(now->data, data)) now = now->left;
		else now = now->right;
	}
	
}


pNode FindNodeVinaryTree(pBinaryTree this, pControlData data)
{
	if (!this->root) return 0;
	pNode now = this->root;
	while (1) {
		if (!now) {
			free(data);
			return 0;
		}
		if (now->data->number == data->number) {
			
			free(data);
			return now;
			
		}
		else if (this->comp(now->data, data)) now = now->left;
		else now = now->right;
	}

}






Void ShowBinaryTreeCD(pControlData data) {
	if (data)
		printf("%d > ", data->number);
	else
		printf("����> ");
}




Void ShowBinaryTreeNode(pNode now) {
	if (!now)return 0;
	ShowBinaryTreeNode(now->left);
	printf("%d >", now->data->number);
	ShowBinaryTreeNode(now->right);
}

Void ShowBinaryTree(pBinaryTree this) {
	ShowBinaryTreeNode(this->root);
}

Void RemoveVinaryTree(pBinaryTree this, pControlData data)
{
	pNode node = FindNodeVinaryTree(this, data);
	if (!node) return;
	if (node->left && node->right) {
		pNode changer = node->left;
		while (changer->right != 0) changer = changer->right;
		if (changer->left) {
			changer->left->parent = changer->parent;
			if (changer->parent->left == changer) changer->parent->left = changer->left;
			else changer->parent->right = changer->left;
		}
		else {
			if (changer->parent->left == changer) changer->parent->left = 0;
			else changer->parent->right = 0;
		}

		free(node->data);
		node->data = changer->data;
		free(changer);
	}
	else if (node->left) {
		node->left->parent = node->parent;
		if (node->parent)
		{
			if (node->parent->left == node) node->parent->left = node->left;
			else node->parent->right = node->left;
		}
		else this->root = node->left;
		free(node->data);
		free(node);


	}
	else if (node->right) {
		node->right->parent = node->parent;
		if (node->parent)
		{
			if (node->parent->left == node) node->parent->left = node->right;
			else node->parent->right = node->right;
		}
		else this->root = node->right;
		free(node->data);
		free(node);
	}
	else {
		if (node->parent) {
			if (node->parent->left == node) node->parent->left = 0;
			else {
				node->parent->right = 0;
			}
		}
		else {
			this->root = 0;
			free(node->data);
			free(node);
		}
	}
}


// ����Ʈ�� ������ ���ڸ� �Է��ϸ� ��� �Էµǵ��� ���α׷���
// �Է��� ���ڰ� 0�̶�� ���̻� �Է����� �ʵ��� ���α׷���
// 0�� �Է��� �� ���ڸ� 2�� �Է��ϸ� ù��° ������ 2��° ��° ���ڸ� �˻��ؼ� ���
// ù��° �˻��� ���ڷ� 0�� �Է��ϸ� �˻��� ��������


// �����Ͱ� ���� ������ ���� �Ͼ��
// �����Ͱ� �������� �ڷᱸ��
// �������� �뷮�� ū �ڷᱸ��
// �� 3������ �������ٸ� ���� �ڷᱸ�� . 


Void main()
{
	pBinaryTree bt = CreateBinaryTree(CompareUp);
	// ����ִ� �Լ� ����.
	//InsertBinaryTree(bt, CD(3));
	//InsertBinaryTree(bt, CD(7));
	//InsertBinaryTree(bt, CD(5));
	//InsertBinaryTree(bt, CD(4));
	//InsertBinaryTree(bt, CD(6));
	//InsertBinaryTree(bt, CD(3));
	//InsertBinaryTree(bt, CD(7));
	//InsertBinaryTree(bt, CD(5));
	//InsertBinaryTree(bt, CD(4));
	//InsertBinaryTree(bt, CD(6));

	//// ��� �Լ� ����
	//ShowBinaryTree(bt); printf("\n");

	//// ã���ִ� �Լ� ����
	//ShowBinaryTreeCD(FindCDVinaryTree(bt, CD(4), 0));
	//ShowBinaryTreeCD(FindCDVinaryTree(bt, CD(4), 1));
	//ShowBinaryTreeCD(FindCDVinaryTree(bt, CD(4), 2));
	//ShowBinaryTreeCD(FindCDVinaryTree(bt, CD(4), 0));
	
	// ����Ʈ�� ������ ���ڸ� �Է��ϸ� ��� �Էµǵ��� ���α׷���
	// �Է��� ���ڰ� 0�̶�� ���̻� �Է����� �ʵ��� ���α׷���
	// 0�� �Է��� �� ���ڸ� 2�� �Է��ϸ� ù��° ������ 2��° ��° ���ڸ� �˻��ؼ� ���
	// ù��° �˻��� ���ڷ� 0�� �Է��ϸ� �˻��� ��������
	pBinaryTree bt2 = CreateBinaryTree(CompareUp);
	/*while (1) {
		user = Scan("���� �Է� : ");
		while(user != 0)
		{ 
			if (user == 0) {
				user = Scan("�� ���� �Է� 1 : ");
				if (user == 0) {
					break;
				}
				user2 = Scan("�ι�° ���� : ");
				ShowBinaryTreeCD(FindCDVinaryTree(bt, CD(user), user2));
			}
		}
		if (user == 0) continue;
		else;
		InsertBinaryTree(bt2, CD(user));
	}*/
	/*Dec sel;
	while (1) {
		sel = Scan(" in >>> ");
		if (sel == 0) break;

		InsertBinaryTree(bt2, CD(sel));
		
	}
	while (1) {
		sel = Scan(" select >>> ");
		if (sel == 0) break;
		ShowBinaryTreeCD(FindCDVinaryTree(bt2, CD(sel), Scan("nth >>> ")));
	}*/
	

	/*Dec sel;

	for (Dec i = 0; i < 100; ++i)
	{
		InsertBinaryTree(bt, CD(Random(100,900)));
	}

	while (1) {
		system("cls");
		ShowBinaryTree(bt); printf("\n");
		sel = Scan("Remove >>> ");
		if (sel == 0) break;
		RemoveVinaryTree(bt, CD(sel));
	}
*/

	// ������ ���ڸ� 1000�� �Է��Ͻÿ�
	// ���ڸ� �Է��ϰ� �Է��� ������ ����� ���ڵ��� ��� �� �����ϴ� ���α׷��� �ۼ��Ͻÿ�
	// �� ������ �ݺ��ϰ� 0�� �Է��ϸ� ���α׷��� ���� .

	Dec sel;
	srand(time(0));
	for (Dec i = 0; i < 1000; ++i)
	{
		InsertBinaryTree(bt, CD(Random(1, 9999)));
	}
	while (1) {
		system("cls");
		ShowBinaryTree(bt); printf("\n");

		sel = Scan("Remove >>> ");
		if (sel == 0) break;
		for (Dec i = 2; i * sel < 9999; ++i)
		{
			RemoveVinaryTree(bt, CD(i * sel));
		}
		RemoveVinaryTree(bt, CD(sel));
	}


	//ShowBinaryTree(bt);



	ReleaseBinaryTree(bt2);
	ReleaseBinaryTree(bt);

}