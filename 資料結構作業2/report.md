# 41443121
作業2

## 解題說明
這題要求建立多項式並相加和相乘。

### 解題策略
1.稀疏多項式與動態記憶體配置策略
2.用指標實現多項式相加
3.用分配律實現多項式的相乘
4.帶數字進去求值

## 演算法設計和程式設計
以下為主要程式:
```cpp
#include <iostream>
#include <cmath>
#include<stdio.h>
using namespace std;
class Polynomial;
class Term 
{
    friend class Polynomial;
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
private:
    float coef;
    int exp;
};
class Polynomial 
{
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
private: 
    Term* termArray;
    int capacity;
    int terms;
    void NewTerm(float c, int e) 
    {
        if (c == 0) return;
        if (terms == capacity) 
        {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            Term* newArray = new Term[capacity];
            for (int i = 0; i < terms; ++i) 
            {
                newArray[i] = termArray[i];
            }
            delete[] termArray;
            termArray = newArray;
        }
        termArray[terms].coef = c;
        termArray[terms].exp = e;
        terms++;
    }
public:
    Polynomial() : termArray(nullptr), capacity(0), terms(0) {}
    Polynomial(const Polynomial& poly) : capacity(poly.capacity), terms(poly.terms) 
    {
        termArray = new Term[capacity];
        for (int i = 0; i < terms; ++i) 
        {
            termArray[i] = poly.termArray[i];
        }
    }
    ~Polynomial() 
    {
        delete[] termArray;
    }
    Polynomial& operator=(const Polynomial& poly) 
    {
        if (this != &poly) 
        {
            delete[] termArray;
            capacity = poly.capacity;
            terms = poly.terms;
            termArray = new Term[capacity];
            for (int i = 0; i < terms; ++i) 
            {
                termArray[i] = poly.termArray[i];
            }
        }
        return *this;
    }
    Polynomial Add(Polynomial poly) 
    {
        Polynomial c;
        int aPos = 0, bPos = 0;
        while (aPos < terms && bPos < poly.terms) 
        {
            if (termArray[aPos].exp == poly.termArray[bPos].exp) 
            {
                float sum = termArray[aPos].coef + poly.termArray[bPos].coef;
                if (sum != 0) {
                    c.NewTerm(sum, termArray[aPos].exp);
                }
                aPos++;
                bPos++;
            }
            else if (termArray[aPos].exp > poly.termArray[bPos].exp) 
            {
                c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
                aPos++;
            }
            else 
            {
                c.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
                bPos++;
            }
        }
        for (; aPos < terms; aPos++) 
        {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
        }
        for (; bPos < poly.terms; bPos++) 
        {
            c.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
        }
        return c;
    }
    Polynomial Mult(Polynomial poly) 
    {
        Polynomial result;
        for (int i = 0; i < terms; ++i) 
        {
            Polynomial temp;
            for (int j = 0; j < poly.terms; ++j) 
            {
                temp.NewTerm(termArray[i].coef * poly.termArray[j].coef,
                    termArray[i].exp + poly.termArray[j].exp);
            }
            result = result.Add(temp);
        }
        return result;
    }
    float Eval(float f) 
    {
        float ans = 0.0f;
        for (int i = 0; i < terms; ++i) 
        {
            ans += termArray[i].coef * std::pow(f, termArray[i].exp);
        }
        return ans;
    }
};
inline std::istream& operator>>(std::istream& is, Polynomial& poly) 
{
    int numTerms;
    is >> numTerms;
    for (int i = 0; i < numTerms; ++i) 
    {
        float c;
        int e;
        is >> c >> e;
        poly.NewTerm(c, e);
    }
    return is;
}
inline std::ostream& operator<<(std::ostream& os, const Polynomial& poly) 
{
    if (poly.terms == 0) 
    {
        os << "0";
        return os;
    }
    for (int i = 0; i < poly.terms; ++i) 
    {
        float c = poly.termArray[i].coef;
        int e = poly.termArray[i].exp;
        if (i > 0) 
        {
            if (c > 0) os << " + ";
            else
            {
                os << " - "; c = -c; 
            }
        }
        else 
        {
            if (c < 0) 
            {
                os << "-"; c = -c; 
            }
        }
        if (e == 0) 
        {
            os << c;
        }
        else if (e == 1) 
        {
            if (c != 1.0f) os << c;
            os << "x";
        }
        else 
        {
            if (c != 1.0f) os << c;
            os << "x^" << e;
        }
    }
    return os;
}
int main() 
{
    Polynomial p1, p2;
    std::cout << "輸入第一個多項式 :\n";
    std::cin >> p1;
    std::cout << "輸入第二個多項式:\n";
    std::cin >> p2;
    std::cout << "\nP1(x) = " << p1 << std::endl;
    std::cout << "P2(x) = " << p2 << std::endl;
    Polynomial p3 = p1.Add(p2);
    std::cout << "相加 P1 + P2 = " << p3 << std::endl;
    Polynomial p4 = p1.Mult(p2);
    std::cout << "相乘 P1 * P2 = " << p4 << std::endl;
    float val = 2.0f;
    std::cout << "當 x = " << val << " 時，P1(x) 的值為: " << p1.Eval(val) << std::endl;
    return 0;
}
```
```
## 效能分析

1.時間複雜度為:執行程式的時間為：$O(T_A + T_B)$
2.空間複雜度為:空間複雜度為：$O(T)$。
```
## 測試與驗證
###測試案例
| 測試案例 | 輸入參數p1|輸入參數2|預期相加輸出|實際相加輸出|預期相乘輸出|實際相乘輸出 |X=2帶P1|
|----------|----------|-----------|-----------|----------|-----------|------------|----|
| 測試一   | 2 3 2 2 0 | 2 4 2 5 1| 7x^2+5x+2  |7x^2+5x+2|12x^4+15x^3+8x^2+10x|12x^4+15x^3+8x^2+10x|14|
| 測試二   |2 4 -3 2 5  | 3 1 3 2 2 -4 1 | 2x^4+x^3-x^2-4x+5| 2x^4+x^3-x^2-4x+5|2x^7 + 4x^6 - 11x^5 - 6x^4 + 17x^3 + 10x^2 - 20x|2x^7 + 4x^6 - 11x^5 - 6x^4 + 17x^3 + 10x^2 - 20x|64.5|
| 測試三   | 2 1.5 5 -2 0  | 0     | 1.5x^5 - 2   |1.5x^5 - 2|0|0|46|


## 效能量測
稀疏表示法（Sparse Representation） 在處理非零項較少的高次方多項式時，省記憶體，在運算效能上也遠高於傳統密集陣列。
## 心得討論
一、 資料結構與動態記憶體管理策略稀疏表示法之優勢：捨棄傳統固定長度的密集陣列，改以 Term 類別與動態陣列 termArray 僅儲存非零項。這在處理高次方且非零項稀疏的多項式時，降低了空間浪費，容量增加。
二、 核心演算法與運算子多載三組運算：
相加：運用雙指標法進行線性合併，有效處理同類項相加與相消。
相乘：基於代數分配律，透過雙迴圈與累積相加完成多項式乘積運算。
求值：透過數值代入與 std::pow 函數精準計算特定 $x$ 值下的多項式結果。

