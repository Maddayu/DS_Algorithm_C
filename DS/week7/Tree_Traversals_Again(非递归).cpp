//An inorder binary tree traversal can be implemented in a non-recursive way with a stack.

/*Sample Input:
6
push 1
push 2
push 3
pop
pop
push 4
pop
pop
push 5
push 6
pop
pop
*/

//Given
//pre  1 2 3 4 5 6
//in   3 2 4 1 6 5
//pro  ? ? ? ? ? ?

/*                      1
                  2          5
              3      4    6

  pre  1,{2,3,4},{5,6} pre的第一个值是root
  in   {3,2,4},1,{6,5} 找到 root 后，分出左右子树，并使用divide concur策略

  post {3,4,2},{6,5},1
*/


void solve( int preL, int inL, int PostL, int n)
{
    if( n == 0) return;
    if( n == 1) {(post[postL] = pre[preL]); return;}

    root = pre[preL];
    post[PostL + n - 1 ] = root;
    for( i=0; i<n; i++)
        if (in[inL + i] == root) break;

    L = i; R = n - L - 1;

    solve(preL+1, inL, postL, L);
    solve(preL+1+L, inL+L+1, postL+L, R);

}
