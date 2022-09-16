#include<iostream>
#include<algorithm>
#include<string>
using namespace std;
const int N = 210, M = 810, base = 400;//偏移，因为偏差范围在-400--400之间，数组没有负的
int f[N][21][M], p[N], d[N], ans[N], n, m;
int main()
{
    
    int T = 1;
    while (cin >> n >> m, n, m)
    {
        for (int i = 1; i <= n; i++)
        {
            cin >> p[i] >> d[i];
        }  //读入

        memset(f, -0x3f, sizeof f);   //因为求最大值, 故赋值为负无穷   在memset函数里面0x3f为无穷大，前面加负号表示负无穷

        f[0][0][base] = 0;  //初始化为0 
        int cnt = 0;   

        for (int i = 1; i <= n; i++)  //枚举前i个人
            for (int j = 0; j <= m; j++) //枚举已经选了的人
                for (int k = 0; k < M; k++) //枚举差值 0~801
                {
                    f[i][j][k] = f[i - 1][j][k];  //不选第 i 个人
                    int t = k - (p[i] - d[i]);   //计算出差值,看是否符合题意
                    if (t < 0 || t > M) continue;
                    if (j < 1) continue;  //是否可以转移
                    f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][t] + p[i] + d[i]);   //状态转移
                }

        int v = 0;
        while (f[n][m][base + v] < 0 && f[n][m][base - v] < 0) v++;
        // 从 dp[n,m,Base]开始往两边开始找，直到找到大于0的总和数为止，v增加，如果在0到800这个范围找不到则没有，
        if (f[n][m][base + v] > f[n][m][base - v]) v = base + v;
        else v = base - v;
        //当v,-v都存在时,取最大值
        int j = m, i = n, k = v;

        while (j)
        {
            if (f[i][j][k] == f[i - 1][j][k]) i--;//第i个人没有被选择
            else
            {
                ans[cnt++] = i;  //选了第i个人
                k = k-(p[i] - d[i]);  //差值减小

                i--, j--; //减小
            }
        }

        int a = 0, b = 0;
        for (int i = 0; i < cnt; i++) a += p[ans[i]], b += d[ans[i]];
        //记录答案
        printf("Jury #%d\n", T++);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", a, b);

        sort(ans, ans + cnt);  //排序,保证编号是从小到大的
        //打印方案
        for (int i = 0; i < cnt; i++) cout << ans[i] << ' ';

        cout << '\n';
        cout << '\n';
    }
}

/*
示例输入


4 2
1 2
2 3 
4 1
6 2
0 0
示例输出

Jury #1
Best jury has value 6 for prosecution and value 4 for defence:
 2 3 
 */
