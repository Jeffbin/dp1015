#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

const int N = 210, M = 810, base = 400;

int f[N][21][M], p[N], d[N], ans[N], n, m;

int main()
{
    
    int T = 1;
    while (cin >> n >> m, n, m)
    {
        for (int i = 1; i <= n; i++) cin >> p[i] >> d[i];  //����

        memset(f, -0x3f, sizeof f);   //��Ϊ�����ֵ, �ʸ�ֵΪ������

        f[0][0][base] = 0;  //��ʼ��Ϊ0
        int cnt = 0;   //��ʼ��

        for (int i = 1; i <= n; i++)  //ö��ǰi����
            for (int j = 0; j <= m; j++) //ö���Ѿ�ѡ�˵���
                for (int k = 0; k < M; k++) //ö�ٲ�ֵ 0~801
                {
                    f[i][j][k] = f[i - 1][j][k];  //��ѡ�� i ����
                    int t = k - (p[i] - d[i]);   //�������ֵ,���Ƿ��������
                    if (t < 0 || t > M) continue;
                    if (j < 1) continue;  //�Ƿ����ת��
                    f[i][j][k] = max(f[i][j][k], f[i - 1][j - 1][t] + p[i] + d[i]);   //״̬ת��
                }

        int v = 0;
        while (f[n][m][base + v] < 0 && f[n][m][base - v] < 0) v++;
        // ��vС��0��v����0 ������������, v++;
        if (f[n][m][base + v] > f[n][m][base - v]) v = base + v;
        else v = base - v;
        //��v,-v������ʱ,ȡ���ֵ
        int j = m, i = n, k = v;

        while (j)
        {
            if (f[i][j][k] == f[i - 1][j][k]) i--;//������Բ�ѡ��i����
            else
            {
                ans[cnt++] = i;  //ѡ�˵�i����
                k -= p[i] - d[i];  //��ֵ��С

                i--, j--; //��С
            }
        }

        int a = 0, b = 0;
        for (int i = 0; i < cnt; i++) a += p[ans[i]], b += d[ans[i]];
        //��¼��
        printf("Jury #%d\n", T++);
        printf("Best jury has value %d for prosecution and value %d for defence:\n", a, b);

        sort(ans, ans + cnt);  //����,��֤����Ǵ�С�����
        //��ӡ����
        for (int i = 0; i < cnt; i++) cout << ans[i] << ' ';

        cout << '\n';
        cout << '\n';
    }
}

/*
ʾ������

4 2
1 2
2 3
4 1
6 2
0 0
ʾ�����

Jury #1
Best jury has value 6 for prosecution and value 4 for defence:
 2 3 
 */
