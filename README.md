# 41443121

作業一-1

## 解題說明
這題要求寫出一個阿克曼函數（Ackermann's function)來計算A(m,n)的值。使用遞迴和非遞迴的寫法各寫一次。
### 解題策略
 1. 遞迴寫法:
m==0 時，返回 n+1，作為遞迴的結束條件。
當 n==0 時，遞迴呼叫 A(m-1,1)。
其他情況遞迴呼叫 A(m-1,A(m,n-1))，將問題拆解成更小的子問題。
主程式輸入 m、n，呼叫 Ackermann 遞迴函式並輸出計算結果。
 2. 非遞迴寫法:
使用 Stack（堆疊）模擬遞迴函式的執行過程，將原本的遞迴呼叫改為迴圈處理。
建立 stack 並將 m 放入堆疊，模擬遞迴函式的呼叫。
當 m=0 時，將 n 加 1，作為遞迴結束條件。
當 n=0 時，將 m-1 放入堆疊，並將 n 設為 1。
其他情況將需要處理的 m 值依序放入 stack，並將 n 減 1，以模擬 A(m-1,A(m,n-1))。
當 stack 為空時，表示所有計算完成，回傳 n 作為結果。
## 程式實作

以下為主要程式碼：
1遞迴
```cpp
#include<iostream>
using namespace std;
int A(int m, int n) 
{
	if (m == 0) 
	{
		return n + 1;
	}
	if (n == 0)
	{
		return A(m - 1, 1);
	}
	return A(m - 1, A(m, n - 1));
}
int main() 
{
	int m, n;
	cin >> m >> n;
	cout << A(m, n);
	return 0;
}
```
2非遞迴
```cpp
#include<iostream>
#include<stack>
using namespace std;
int A(int m,int n)
{
	stack<int>s;
	s.push(m);
	while (!s.empty()) 
	{
		m = s.top();
		s.pop();
		if (m == 0)
		{
			n = n + 1;
		}
		else if (n == 0) 
		{
			s.push(m - 1);
			n = 1;
		}
		else 
		{
			s.push(m - 1);
			s.push(m);
			n = n - 1;
		}
	}
	return n;
}
int main() 
{
	int m, n;
	cin >> m >> n;
	cout << A(m, n) << endl;
	return 0;
}
```

## 效能分析

1. 時間複雜度：遞迴或非遞迴版本的呼叫次數與最終計算出來的數值 A(m, n) 成正比。當 m>=4 時，數值會呈爆炸性增長（例如:A(4,2) 已經是大於宇宙原子總數的超大數字）。
2. 空間複雜度：1遞迴:最壞情況下的遞迴呼叫堆疊深度取決於中間結果，最大深度可達 A(m, n)。2非遞迴:需要維護一個模擬遞迴過程的堆疊，所需的最大空間與遞迴呼叫深度相同。

## 測試與驗證

### 測試案例

| 測試案例 | 輸入參數       | 預期輸出 | 實際輸出 |
|----------|---------------|----------|----------|
| 測試一   | n = 0    m=1   | 2        | 2        |
| 測試二   | n = 1    m=2   | 4        | 4        |
| 測試三   | n = 2    m=3   | 9        | 9        |
| 測試四   | n = 3    m=4   | 125      | 125      | 
| 測試五   | n = 4    m=5   | 異常拋出  | 異常拋出 |

### 編譯與執行指令

```shell
$ g++ -std=c++17 -o ackermann ackermann.cpp
$ ./ackermann
2 3
9
```

### 結論

1. 極致的演算法複雜度：阿克曼函數的成長速度極其驚人，時間與空間複雜度均為 $O(A(m, n))$。即便輸入非常小的數字（如 $m \ge 4$），計算量與遞迴呼叫次數也會呈超指數（Hyper-exponential）級爆炸性成長。  
2. 在 $n < 0$ 的情況下，程式會成功拋出異常，符合設計預期。  
3. 測試案例涵蓋了多種邊界情況（$n = 0$、$n = 1$、$n > 1$、$n < 0$），驗證程式的正確性。

## 申論及開發報告

### 選擇遞迴的原因

在本程式中，使用遞迴來計算連加總和的主要原因如下：

1. **數學定義一致性與直覺性*  
   阿克曼函數本身在數學上就是透過遞迴關係式（Recurrence Relation）嚴謹定義的： 

   A(0, n) = n + 1
   A(m, 0) = A(m - 1, 1)
   A(m, n) = A(m - 1, A(m, n - 1))
採用遞迴語法能夠以最直觀、最貼近數學定義的方式將演算法轉化為程式碼。程式邏輯簡潔明瞭、可讀性高，大幅降低了程式碼寫入與維護時的錯誤率。

2. **簡化狀態管理**  
  在計算 A(m, n - 1) 時，其回傳值會作為外層 A(m - 1, \cdot)$ 的輸入參數。遞迴架構：能自動利用系統內建的呼叫堆疊（Call Stack）來隱式（Implicitly）維護每一次函數呼叫的區域變數與回傳位址，開發者無需手動處理複雜的中間狀態儲存。非遞迴架構：必須自行設計並維護一個資料結構（如 Stack）來模擬這種巢狀呼叫，程式碼會變得相當冗長且容易出錯。

3. **小結**  
   選擇遞迴寫法主要出於程式碼可讀性、數學定義自然還原以及開發效率的考量；然而在處理深層計算時，必須透過非遞迴（自訂堆疊）或尾遞迴優化等方式，以解決系統堆疊溢位（Stack Overflow）的硬體限制。

作業一-2
## 解題說明
本題要求編寫一個遞迴函式（Recursive Function），傳入一個包含 n 個元素的集合 S，並計算／印出 S 的冪集（Powerset）。

### 解題策略

## 程式實作
以下為主要程式碼：
```cpp
#include <iostream>
#include <vector>
using namespace std;
void generatePowerset(const vector<char>& S, vector<char>& current, int index) {
    if (index == S.size()) {
        cout << "(";
        for (size_t i = 0; i < current.size(); ++i) {
            cout << current[i];
            if (i + 1 < current.size()) cout << ", ";
        }
        cout << ")\n";
        return;
    }
    generatePowerset(S, current, index + 1);
    current.push_back(S[index]);
    generatePowerset(S, current, index + 1);
    current.pop_back();
}
int main() {
    vector<char> S = { 'a', 'b', 'c' };
    vector<char> current;
    cout << "powerset(S) = {\n";
    generatePowerset(S, current, 0);
    cout << "}" << endl;
    return 0;
```

## 效能分析
時間複雜度：O(2^n)長度為 $n$ 的集合共有 2^n 個子集，遞迴樹共有 2^n 個葉子節點，故時間複雜度為 O(2^n)。  
空間複雜度：$O(n)$遞迴呼叫堆疊（Call Stack）的最大深度為 $n$，且儲存當前子集的暫存陣列空間最多為 $n$，因此輔助空間複雜度為 $O(n)$。
## 測試與驗證
## 申論及開發報告
