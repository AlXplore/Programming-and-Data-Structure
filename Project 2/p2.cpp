#include <iostream>
#include <cstdlib>
#include "p2.h"
#include "recursive.h"

using namespace std;

/**************************************List**************************************/

static int size_helper(list_t list, int size)
{
	if (!list_isEmpty(list))
		return size_helper(list_rest(list),(size + 1));
	else
		return size;
}

int size(list_t list)
{
	//done
	int size_of_list = 0;
	size_of_list = size_helper(list, size_of_list);
	
	return size_of_list;
}

bool memberOf(list_t list, int val)
{
	//done
	if (list_isEmpty(list))
		return false;
	else
	{
		if (list_first(list) == val)
			return true;
		else
			return memberOf(list_rest(list), val);
	}
}

static int dot_helper(list_t list1, list_t list2, int product)
{
	if (list_isEmpty(list1) or list_isEmpty(list2))
		return product;
	else
		return dot_helper(list_rest(list1), list_rest(list2), 
			(product + list_first(list1)*list_first(list2)));
}

int dot(list_t v1, list_t v2)
{
	//done
	if (list_isEmpty(v1) or list_isEmpty(v2))
	{
		cout<< "List is empty!" << endl;
		return 0;
	}
	else
	{
		return dot_helper(v1, v2, 0);
	}
}

bool isIncreasing(list_t v)
{
	//done
	if (list_isEmpty(v) or list_isEmpty(list_rest(v)))
		return true;
	else
		if (list_first(v) > list_first(list_rest(v)))
			return false;
		else
			return isIncreasing(list_rest(v));
}

static list_t reverse_helper(list_t list, list_t list_rev)
{
	if (!list_isEmpty(list))
	{
		list_rev = list_make(list_first(list), list_rev);
		return reverse_helper(list_rest(list), list_rev);
	}
	else
		return list_rev;
}

list_t reverse(list_t list)
{
	//done test01
	list_t list_rev;
	list_rev = list_make();
	return reverse_helper(list, list_rev);
}

static list_t append_helper(list_t first, list_t second)
{
	if (!list_isEmpty(second))
	{
		first = list_make(list_first(second), first);
		return append_helper(first, list_rest(second));
	}
	else
		return first;
}

list_t append(list_t first, list_t second)
{
	//done
	first = reverse(first);
	list_t append_result;
	append_result = reverse(append_helper(first, second));
	return append_result;
}

static bool isArithmeticSequence_helper(list_t v, int delta)
{
	if (!list_isEmpty(v) and !list_isEmpty(list_rest(v)))
	{
		if ((list_first(list_rest(v)) - list_first(v)) == delta)
			return isArithmeticSequence_helper(list_rest(v), delta);
		else
			return false;
	}
	else
		return true;
}

bool isArithmeticSequence(list_t v)
{
	//done
	int delta = list_first(list_rest(v)) - list_first(v);
	return isArithmeticSequence_helper(v, delta);
}

static list_t filter_odd_helper(list_t list0, list_t list_new)
{
	if(!list_isEmpty(list0))
	{
		if (list_first(list0) % 2 == 1)
		{
			list_new = list_make(list_first(list0), list_new);
			return filter_odd_helper(list_rest(list0), list_new);
		}
		else
			return filter_odd_helper(list_rest(list0), list_new);
	}
	else
		return reverse(list_new);
}

list_t filter_odd(list_t list)
{
	//done
	list_t list_new;
	list_new = list_make();
	return filter_odd_helper(list, list_new);
}

static list_t filter_helper(list_t list0, list_t list_new, bool (*fn)(int))
{
	if (!list_isEmpty(list0))
	{
		if (fn(list_first(list0)))
		{
			list_new = list_make(list_first(list0), list_new);
			return filter_helper(list_rest(list0), list_new, fn);
		}
		else
			return filter_helper(list_rest(list0), list_new, fn);
	}
	else
		return reverse(list_new);
}


list_t filter(list_t list, bool (*fn)(int))
{
	//done
	list_t list_new;
	list_new = list_make();
	return filter_helper(list, list_new, fn);
}

static list_t unique_helper(list_t list, list_t unqlist)
{
	if (!list_isEmpty(list))
	{
		if (!memberOf(unqlist, list_first(list)))
		{
			unqlist = list_make(list_first(list), unqlist);
			return unique_helper(list_rest(list), unqlist);
		}
		else
			return unique_helper(list_rest(list), unqlist);
	}
	else
		return reverse(unqlist);
}

list_t unique(list_t list)
{
	//done +stat test
	list_t unqlist;
	unqlist = list_make();
	return unique_helper(list, unqlist);
}

static list_t insert_list_helper(list_t first, list_t second, list_t list_new, unsigned int n)
{
	if (size(list_new) < int(n))
	{
		list_t first_temp = list_make();
		first_temp = list_make(list_first(first), first_temp);
		list_new = append(list_new, first_temp);
		return insert_list_helper(list_rest(first), second, list_new, n);
	}
	else
	{
		list_new = append(list_new, second);
		list_new = append(list_new, first);
		return list_new;
	}
}

list_t insert_list(list_t first, list_t second, unsigned int n)
{
	//done +stat test
	if (int(n) > size(first))
	{
		cout << "Error: The first list is not that long." << endl;
		return 0;
	}
	else
	{
		list_t list_new;
		list_new = list_make();
		return insert_list_helper(first, second, list_new, n);
	}
}

static list_t chop_helper(list_t list, list_t list_new, int len_list, unsigned int n)
{
	if (size(list_new) == (len_list - int(n)))
		return list_new;
	else
	{
		list_new = list_make(list_first(list), list_new);
		return chop_helper(list_rest(list), list_new, len_list, n);
	}
}

list_t chop(list_t list, unsigned int n)
{
	//done
	if (int(n) > size(list))
	{
		cout << "Error: The list is not that long." << endl;
		return 0;
	}
	else
	{
		int len_list = size(list);
		list_t list_new;
		list_new = list_make();
		return reverse(chop_helper(list, list_new, len_list, n));
	}
}

/**************************************BinTree**************************************/

int tree_sum(tree_t tree)
{
	//done
	if (!tree_isEmpty(tree))
		return (tree_elt(tree)+tree_sum(tree_left(tree))+tree_sum(tree_right(tree)));
	else
		return 0;
}

bool tree_search(tree_t tree, int val)
{
	//done
	if (!tree_isEmpty(tree))
	{
		if (tree_elt(tree) == val)
			return true;
		else
		{
			bool torf = (tree_search(tree_left(tree), val) or tree_search(tree_right(tree), val));
			return torf;
		}
	}
	else
		return false;
}

static int max(int a, int b)
{
	if (a >= b)
		return a;
	else
		return b;
}

static int depth_helper(tree_t tree, int tree_depth)
{
	if (tree_isEmpty(tree))
		return tree_depth;
	else
	{
		int depth_left = depth_helper(tree_left(tree), tree_depth+1);
		int depth_right = depth_helper(tree_right(tree), tree_depth+1);
		return max(depth_left, depth_right);
	}
}

int depth(tree_t tree)
{
	//done
	int tree_depth = 0;
	return depth_helper(tree, tree_depth);
}

static int tree_max_helper(tree_t tree, int max_element)
{
	if (tree_isEmpty(tree))
		return max_element;
	else
	{
		max_element = max(tree_elt(tree), max_element);
		int max_left = tree_max_helper(tree_left(tree), max_element);
		int max_right = tree_max_helper(tree_right(tree), max_element);
		return max(max_left, max_right);
	}
}

int tree_max(tree_t tree)
{
	//done
	if (tree_isEmpty(tree))
	{
		cout << "Error: There is no element in it." << endl;
		return 0;
	}
	else
	{
		int max_element = 0;
		return tree_max_helper(tree, max_element);
	}
}

static list_t traversal_helper(tree_t tree, list_t trav_list)
{
	if (!tree_isEmpty(tree)) 
	{	
		list_t trav_list_left = list_make();
		list_t trav_list_right = list_make();
		trav_list_left = append(trav_list_left, traversal_helper(tree_left(tree), trav_list_left));
		trav_list_right = append(trav_list_right, traversal_helper(tree_right(tree), trav_list_right));
		list_t subtreeroot = list_make();
		subtreeroot = list_make(tree_elt(tree), subtreeroot);
		trav_list = append(trav_list, trav_list_left);
		trav_list = append(trav_list, subtreeroot);
		trav_list = append(trav_list, trav_list_right);
		return trav_list;
	}
	else
		return list_make();
}

list_t traversal(tree_t tree)
{
	//done (q)
	list_t trav_list = list_make();
	return traversal_helper(tree, trav_list);
}

static bool incre(int a, int b)
{
	if (b >= a)
		return true;
	else
		return false;
}

static bool decre(int a, int b)
{
	if (b <= a)
		return true;
	else
		return false;
}

static bool tree_hasMonotonicPath_helper(tree_t tree, bool (*fn)(int a, int b))
{
	if (tree_isEmpty(tree))
		return false;
	else
	{
		if (tree_isEmpty(tree_left(tree)) and tree_isEmpty(tree_right(tree)))
			return true;
		else
		{
			bool flag_left = false;
			bool flag_right = false;
			if (!tree_isEmpty(tree_left(tree))) 
			{
				if (fn(tree_elt(tree), tree_elt(tree_left(tree))))
					flag_left = tree_hasMonotonicPath_helper(tree_left(tree), fn);
				else
					flag_left = false;
			}
			if (!tree_isEmpty(tree_right(tree))) 
			{
				if (fn(tree_elt(tree), tree_elt(tree_right(tree))))
					flag_right = tree_hasMonotonicPath_helper(tree_right(tree), fn);
				else
					flag_right = false;			}
			return (flag_left or flag_right);
		}
	}
}

bool tree_hasMonotonicPath(tree_t tree)
{
	//done
	bool flag1 = tree_hasMonotonicPath_helper(tree, incre);
	bool flag2 = tree_hasMonotonicPath_helper(tree, decre);
	return (flag1 or flag2);
}

static bool tree_allPathSumGreater_helper(tree_t tree, int minimum, int sum)
{
	if (tree_isEmpty(tree))
		return false;
	else
	{
		if (sum <= minimum)
		{
			sum += tree_elt(tree);
			if (sum <= minimum)
				return (tree_allPathSumGreater_helper(tree_left(tree), minimum, sum) 
					and tree_allPathSumGreater_helper(tree_right(tree), minimum, sum));
			else
				return true;
		}
		else
			return true;
	}
}

bool tree_allPathSumGreater(tree_t tree, int sum)
{
	//done
	if (tree_isEmpty(tree))
	{
		cout << "Error: the tree is empty." << endl;
		return 0;
	}
	else
	{
		int path_sum = 0;
		return tree_allPathSumGreater_helper(tree, sum, path_sum);
	}
}

bool covered_by(tree_t A, tree_t B)
{
	//done
	if (tree_isEmpty(A))
		return true;

	if (tree_isEmpty(B))
		return false;
	else
	{
		if (tree_elt(A) != tree_elt(B))
			return false;
		else
		{
			bool flag1 = covered_by(tree_left(A), tree_left(B));
			bool flag2 = covered_by(tree_right(A), tree_right(B));
			return (flag1 and flag2);
		}
	}
}

bool contained_by(tree_t A, tree_t B)
{
	if (tree_isEmpty(B) and !tree_isEmpty(A))
		return false;
	if (tree_isEmpty(B) and tree_isEmpty(A))
		return true;
	if (covered_by(A, B))
		return true;
	else
	{
		if (covered_by(A, tree_left(B)))
			return true;
		else if (covered_by(A, tree_right(B)))
			return true;
		else
			return false;
	}
}

/*
static bool is_sorted_tree(tree_t tree)
{
	list_t tree_sorted_list = traversal(tree);
	if (isIncreasing(tree_sorted_list))
		return true;
	else
		return false;
} */

static tree_t insert_tree_helper(int elt, tree_t tree)
{
	if (tree_isEmpty(tree))
		return tree_make(elt, tree_make(), tree_make());
	else
	{	
		if (elt < tree_elt(tree))
			return tree_make(tree_elt(tree), insert_tree(elt, tree_left(tree)), tree_right(tree));
		else
			return tree_make(tree_elt(tree), tree_left(tree), insert_tree(elt, tree_right(tree)));
	}
}

tree_t insert_tree(int elt, tree_t tree)
{
/*	if (is_sorted_tree(tree) == false)
	{
		cout << "Error: The tree entered is not a sorted tree." << endl;
		return 0;
	}
	else*/
		return insert_tree_helper(elt, tree);

}

/**************************************END**************************************/