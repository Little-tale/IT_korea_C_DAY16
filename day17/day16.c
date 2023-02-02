#include "../../headers/structure.h"

//데이터의 입출력의 순서에 관련한 자료구조
// stack 자료 구조 -> 데이터의 선입력 후 출력

//분편함 -> 데이터를 정렬하는데 너무 어렵다.
// 학생의 정보를 관리하는 프로그램이나
// 학점관리 프로그램
// 재고 관리 프로그램
// 게임의 랭킹 시스템 - 30분마다, 새로고침


// 데이터를 정렬하는 기법 -> 정렬기능, 버블정렬, 힙정렬, 합정렬,...

// 아예 데이터를 순서대로 입력하는 기법을 만들면 되지 않을까?
// 데이터가 추가 되면서 자동으로 순서대로 만들어 지면 어떠할까?

// 이진트리 구조 -> 데이터를 추가할때 자동으로 순서대로 정렬시키면서 추가하는 자료구조.
// 데이터의 순서가 생기는데 -> 

// 예를 들어
	// 1~ 1000가지 중에 숫자 1개를 생각하시오 2^10 10번만 물어보면됨.
	
	// 이진트리 -> 데이터에 순서를 만들어서 검색 속도를 빠르게 하는 자료구조.

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
				//맞았을때
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
				//틀렸을때
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
		printf("에러> ");
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


// 이진트리 구조에 숫자를 입력하면 계속 입력되도록 프로그래밍
// 입력한 숫자가 0이라면 더이상 입력하지 않도록 프로그래밍
// 0을 입력한 후 숫자를 2개 입력하면 첫번째 숫자의 2번째 번째 숫자를 검색해서 출력
// 첫번째 검색할 숫자로 0을 입력하면 검색이 끝나도록


// 데이터가 삽입 삭제가 가끔 일어나는
// 데이터가 무작위한 자료구조
// 데이터의 용량이 큰 자료구조
// 이 3가지가 갖춰진다면 좋은 자료구조 . 


Void main()
{
	pBinaryTree bt = CreateBinaryTree(CompareUp);
	// 집어넣는 함수 구현.
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

	//// 출력 함수 구현
	//ShowBinaryTree(bt); printf("\n");

	//// 찾아주는 함수 구현
	//ShowBinaryTreeCD(FindCDVinaryTree(bt, CD(4), 0));
	//ShowBinaryTreeCD(FindCDVinaryTree(bt, CD(4), 1));
	//ShowBinaryTreeCD(FindCDVinaryTree(bt, CD(4), 2));
	//ShowBinaryTreeCD(FindCDVinaryTree(bt, CD(4), 0));
	
	// 이진트리 구조에 숫자를 입력하면 계속 입력되도록 프로그래밍
	// 입력한 숫자가 0이라면 더이상 입력하지 않도록 프로그래밍
	// 0을 입력한 후 숫자를 2개 입력하면 첫번째 숫자의 2번째 번째 숫자를 검색해서 출력
	// 첫번째 검색할 숫자로 0을 입력하면 검색이 끝나도록
	pBinaryTree bt2 = CreateBinaryTree(CompareUp);
	/*while (1) {
		user = Scan("숫자 입력 : ");
		while(user != 0)
		{ 
			if (user == 0) {
				user = Scan("두 숫자 입력 1 : ");
				if (user == 0) {
					break;
				}
				user2 = Scan("두번째 숫자 : ");
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

	// 무작위 숫자를 1000개 입력하시오
	// 숫자를 입력하고 입력한 숫자의 배수인 숫자들을 모두 다 삭제하는 프로그램을 작성하시오
	// 위 동작을 반복하고 0을 입력하면 프로그램을 종료 .

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