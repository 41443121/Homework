#include <iostream>
#include <cmath>
using namespace std;
class Polynomial; 
class Term //term類
{
    friend class Polynomial; 
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
private:
    float coef; 
    int exp;    
};
class Polynomial //多項類別
{
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& poly);
    friend std::istream& operator>>(std::istream& is, Polynomial& poly);
private: //私有
    Term* termArray; 
    int capacity;    
    int terms;       
    void NewTerm(float c, int e) {
        if (c == 0) return; 
        if (terms == capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            Term* newArray = new Term[capacity];
            for (int i = 0; i < terms; ++i) {
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
    Polynomial(const Polynomial& poly) : capacity(poly.capacity), terms(poly.terms) {
        termArray = new Term[capacity];
        for (int i = 0; i < terms; ++i) {
            termArray[i] = poly.termArray[i];
        }
    }
    ~Polynomial() {
        delete[] termArray;
    }
    Polynomial& operator=(const Polynomial& poly) {
        if (this != &poly) {
            delete[] termArray;
            capacity = poly.capacity;
            terms = poly.terms;
            termArray = new Term[capacity];
            for (int i = 0; i < terms; ++i) {
                termArray[i] = poly.termArray[i];
            }
        }
        return *this;
    }
    Polynomial Add(Polynomial poly) {
        Polynomial c;
        int aPos = 0, bPos = 0;
        while (aPos < terms && bPos < poly.terms) {
            if (termArray[aPos].exp == poly.termArray[bPos].exp) {
                float sum = termArray[aPos].coef + poly.termArray[bPos].coef;
                if (sum != 0) {
                    c.NewTerm(sum, termArray[aPos].exp);
                }
                aPos++;
                bPos++;
            }
            else if (termArray[aPos].exp > poly.termArray[bPos].exp) {
                c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
                aPos++;
            }
            else {
                c.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
                bPos++;
            }
        }
        for (; aPos < terms; aPos++) {
            c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
        }
        for (; bPos < poly.terms; bPos++) {
            c.NewTerm(poly.termArray[bPos].coef, poly.termArray[bPos].exp);
        }
        return c;
    }
    Polynomial Mult(Polynomial poly) {
        Polynomial result;
        for (int i = 0; i < terms; ++i) {
            Polynomial temp;
            for (int j = 0; j < poly.terms; ++j) {
                temp.NewTerm(termArray[i].coef * poly.termArray[j].coef,
                    termArray[i].exp + poly.termArray[j].exp);
            }
            result = result.Add(temp); 
        }
        return result;
    }
    float Eval(float f) {
        float ans = 0.0f;
        for (int i = 0; i < terms; ++i) {
            ans += termArray[i].coef * std::pow(f, termArray[i].exp);
        }
        return ans;
    }
};
inline std::istream& operator>>(std::istream& is, Polynomial& poly) {
    int numTerms;
    is >> numTerms;
    for (int i = 0; i < numTerms; ++i) {
        float c;
        int e;
        is >> c >> e;
        poly.NewTerm(c, e);
    }
    return is;
}
inline std::ostream& operator<<(std::ostream& os, const Polynomial& poly) {
    if (poly.terms == 0) {
        os << "0";
        return os;
    }
    for (int i = 0; i < poly.terms; ++i) {
        float c = poly.termArray[i].coef;
        int e = poly.termArray[i].exp;

        if (i > 0) {
            if (c > 0) os << " + ";
            else { os << " - "; c = -c; }
        }
        else {
            if (c < 0) { os << "-"; c = -c; }
        }

        if (e == 0) {
            os << c;
        }
        else if (e == 1) {
            if (c != 1.0f) os << c;
            os << "x";
        }
        else {
            if (c != 1.0f) os << c;
            os << "x^" << e;
        }
    }
    return os;
}
int main() {
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
